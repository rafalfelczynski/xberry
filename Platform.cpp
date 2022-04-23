#include "Platform.hpp"

Platform::Platform(unsigned bufferSize)
    : buffersSize_(bufferSize)
{
}

void Platform::listenToSensor(unsigned sensorId, ISensorListener* client)
{
    std::lock_guard lg(mutex_);
    listenersPerSensor_[sensorId].emplace(client);
}

void Platform::finishListening(unsigned sensorId, ISensorListener* client)
{
    std::lock_guard lg(mutex_);
    listenersPerSensor_[sensorId].erase(client);
}

void Platform::addNewMsg(unsigned sensorId, const std::string& data)
{
    std::lock_guard lg(mutex_);
    if (!msgsPerSensor_.count(sensorId))
    {
        msgsPerSensor_.emplace(sensorId, CyclicBuffer<std::string>(buffersSize_));
    }
    msgsPerSensor_.at(sensorId).push(data);
}

void Platform::publishAvailableMsgs()
{
    std::lock_guard lg(mutex_);
    for (const auto& [sensorId, listeners] : listenersPerSensor_)
    {
        if (msgsPerSensor_.count(sensorId))
        {
            auto& sensorMsgs = msgsPerSensor_.at(sensorId);
            std::vector<std::string> sensorMsgsVec(sensorMsgs.begin(), sensorMsgs.end());
            for (auto& listener : listeners)
            {
                listener->onDataReceived(sensorId, sensorMsgsVec);
            }
            sensorMsgs.clear();
        }
    }
}
