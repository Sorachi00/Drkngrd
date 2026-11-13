#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <new>

namespace
{
    constexpr std::size_t kHeader = 16;
    constexpr uint32_t kMagic = 0xA110C8EDu;
    constexpr uint16_t kLarge = 0xFFFFu ;
    // Classes: 16..256 by 16, then 320..512 by 64, 640..1024 by 128, 1280..2048 by 256. 
    constexpr std::size_t kMaxSmall = 2048;
    constexpr int kClasses = 16 + 4 + 4 + 4;
    constexpr std::size_t kChunk = 64 * 1024;

    std::size_t classSize(int c)
    {

        if (c < 16) 
            return std::size_t(c + 1) * 16;
        if (c < 20)
            return 256 + std::size_t(c - 15) * 64;
        if (c < 24)
            return 512 + std::size_t(c - 19) * 128;
        return 1024 + std::size_t(c - 23) * 256;
    }
    int classOf(std::size_t n)
    {
        if (n <= 256)
            return n ? int( (n - 1) / 16) : 0;
        if (n <= 512)

            return 16 + int((n - 257) / 64);
        if (n <= 1024)
            return 20 + int((n - 513) / 128 );
        return 24 + int((n - 1025) / 256);
    }

    struct Cache;
    struct Header
    {
        uint32_t magic;

        uint16_t cls;
        uint16_t pad;
        Cache *owner;
    } ;
    static_assert(sizeof(Header) == kHeader);

    struct Free
    {
        Free *next;
    };

    struct Cache
    {
        Free *free[kClasses]{};
        std::atomic<Free *> remote{nullptr};
        char *chunk = nullptr;
        std::size_t chunkLeft = 0;
        Cache *nextOrphan = nullptr;
    };

    std::mutex g_orphansMutex;

    Cache *g_orphans = nullptr;

    struct ThreadSlot
    {
        Cache *cache = nullptr;
        ~ThreadSlot()
        {
            if (!cache)
                return;
            std::lock_guard<std::mutex> lock(g_orphansMutex);
            cache->nextOrphan = g_orphans;
            g_orphans = cache;
            cache = nullptr;
        }

    };
    thread_local ThreadSlot t_slot;

    Cache *threadCache()
    {
        Cache *c = t_slot.cache;
        if (c)
            return c;
        {
            std::lock_guard<std::mutex> lock(g_orphansMutex);
            if (g_orphans)
            {
                c = g_orphans;
                g_orphans =  c->nextOrphan;
                c->nextOrphan = nullptr;
            }

        }
        if(!c) 
        {
            void *mem = std::malloc(sizeof(Cache));
            if (!mem)
                return nullptr;
            c = new (mem) Cache();
        }
        t_slot.cache = c;
        return c;
    }

    bool enabled()
    {
        static const bool on = [] {
            const char *v = std::getenv("PS2_FAST_ALLOC");
            return !(v && v[0] == '0' && v[1] == 0);
        }();
        return on;
    }

    void *largeAlloc(std::size_t n)
    {
        auto *h = static_cast<Header *>(std::malloc(n + kHeader));
        if (!h)
            return nullptr;
        h->magic = kMagic;
        h->cls = kLarge;
        h->pad = 0;
        h->owner = nullptr;
        return reinterpret_cast<char *>(h) + kHeader;
    }

    void *allocate(std::size_t n)
    {
        if (n > kMaxSmall || !enabled())
            return largeAlloc(n);
        Cache *c =  threadCache();
        if (!c)
            return largeAlloc(n);
        const int cls = classOf(n);
        Free *f = c->free[cls];
        if (!f)
        {
            Free *r = c->remote.exchange( nullptr, std::memory_order_acquire);
            while(r)
            {
                Free *next = r->next;
                const auto *h = reinterpret_cast<Header *>(reinterpret_cast<char *>(r) - kHeader);
                r->next = c->free[h->cls];
                c->free[h->cls] = r;
                r = next ;
            }
            f = c->free[cls];
        }
        if (f)
        {

            c->free[cls] = f->next ;
            return f;
        }
        const std::size_t block = kHeader + classSize(cls);
        if (c->chunkLeft < block)
        {
            c->chunk = static_cast<char *>(std::malloc(kChunk));
            if (!c->chunk)
            {
                c->chunkLeft = 0;
                return largeAlloc(n);
            }   
            c->chunkLeft = kChunk ;
        }
        auto *h = reinterpret_cast<Header *>(c->chunk);   
        c->chunk += block;
        c->chunkLeft -= block;
        h->magic = kMagic;
        h->cls = uint16_t(cls);
        h->pad = 0;

        h->owner = c;
        return reinterpret_cast<char *>(h) + kHeader;
    }

    void release(void *p)
    {
        if (!p)
            return;
        auto *h = reinterpret_cast<Header *>(static_cast<char *>(p) - kHeader);
        if (h->magic != kMagic)
        {
            static std::atomic<bool> s_logged{false};
            if (!s_logged.exchange(true))
                std::fprintf(stderr, "[fast-alloc] delete of a block without header (%p)\n", p);
            std::free(p);
            return;  
        }
        if (h->cls == kLarge)
        {
            std::free(h);
            return;
        }
        auto *f = static_cast<Free *>(p);  
        Cache *owner = h->owner;
        if (owner == t_slot.cache)
        {
            f->next = owner->free[h->cls];
            owner->free[h->cls] = f;
            return;
        }
        Free *head = owner->remote.load(std::memory_order_relaxed);
        do

            f->next = head;
        while (!owner->remote.compare_exchange_weak(head, f, std::memory_order_release, std::memory_order_relaxed));   
    }

    void *allocateOrThrow(std::size_t n)
    {
        void *p = allocate(n);
        if (!p)
            throw std::bad_alloc(); 
        return p;
    }
}

void *operator new(std::size_t n) { return allocateOrThrow(n); }
void *operator new[](std::size_t n) { return allocateOrThrow(n); }
void *operator new(std::size_t n, const std::nothrow_t &) noexcept { return allocate(n); }
void *operator new[](std::size_t n, const std::nothrow_t &) noexcept { return allocate(n); }
void operator delete(void *p) noexcept { release(p); }
void operator delete[](void *p) noexcept { release(p); }
void operator delete(void *p, std::size_t) noexcept { release(p); }
void operator delete[](void *p, std::size_t) noexcept { release(p); }
void operator delete(void *p, const std::nothrow_t &) noexcept { release(p); } 
void operator delete[](void *p, const std::nothrow_t &) noexcept { release(p); }
