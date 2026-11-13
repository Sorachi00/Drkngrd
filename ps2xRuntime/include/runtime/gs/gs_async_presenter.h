#pragma once

#include "runtime/gs/gs_types.h"

class GSAsyncPresenter
{
  public:
    virtual ~GSAsyncPresenter() = default;
    virtual bool PresentBegin(const GSPresentationRequest &request) = 0;
    virtual bool PresentPoll(PresentationFrame &out) = 0;
};
