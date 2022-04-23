#pragma once

#include <unordered_map>
#include <set>
#include <mutex>
#include "CyclicBuffer.hpp"
#include "ISensorListener.hpp"

struct Platform
{
    Platform(unsigned bufferSize);
    virtual ~Platform() = default;
    virtual void listenToSensor(unsigned sensorId, ISensorListener* client);
    virtual void finishListening(unsigned sensorId, ISensorListener* client);
    virtual void addNewMsg(unsigned sensorId, const std::string& data);
    virtual void publishAvailableMsgs();

protected:
    unsigned buffersSize_;
    std::mutex mutex_;
    std::unordered_map<unsigned, std::set<ISensorListener*>> listenersPerSensor_;
    std::unordered_map<unsigned, CyclicBuffer<std::string>> msgsPerSensor_;
};
