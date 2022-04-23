#pragma once

#include <unordered_set>
#include <memory>

#include "ISubscriber.h"


template<typename... DataType>
struct IPublisher
{
    virtual ~IPublisher() = default;
    virtual void addObserver(ISubscriber<DataType...>* obs)
    {
        observers_.insert(obs);
    }

    virtual void removeObserver(ISubscriber<DataType...>* obs)
    {
        observers_.erase(obs);
    }

    virtual void publish(const DataType&... data)
    {
        for (auto* observer : observers_)
        {
            observer->onDataReceived(data...);
        }
    }

protected:
    std::unordered_set<ISubscriber<DataType...>*> observers_;
};
