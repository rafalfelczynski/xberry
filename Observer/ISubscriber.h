#pragma once

#include <map>
#include <memory>

template<typename... DataType>
struct ISubscriber
{
    virtual ~ISubscriber() = default;
    virtual void onDataReceived(const DataType&... data) = 0;
};
