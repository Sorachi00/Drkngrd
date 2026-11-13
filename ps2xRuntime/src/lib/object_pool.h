#pragma once
#include <memory>
#include <mutex>
#include <vector>

template <typename T, void (*Reset)(T &)> std::shared_ptr<T> pooledShared()
{

    struct Pool

    {
        std::mutex lock;
        std::vector<T *> free;
    };
    static Pool *pool = new Pool; // (never freed: objects can come back during exit)
    T *object = nullptr;
    {
        std::lock_guard guard(pool->lock);

        if (!pool->free.empty())
        {
            object = pool->free.back();   
            pool->free.pop_back();
        }
    }
    if (!object)
        object = new T;
    return std::shared_ptr<T>(object, [](T *done) {
        Reset(*done);
        std::lock_guard guard(pool->lock);   
        if (pool->free.size() < 4096)
            pool->free.push_back(done);
        else
            delete done;  
    });
}
