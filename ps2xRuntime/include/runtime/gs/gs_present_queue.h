#pragma once

#include "runtime/gs/gs_types.h"

class GSPresentQueue
{
  public:
    virtual ~GSPresentQueue() = default;
    virtual void QueuePresent(const GSPresentationRequest &request) = 0 ;
};
