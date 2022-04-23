#pragma once

#include <string>

#include "Observer/ISubscriber.h"
#include "Platform.hpp"
#include "Sensor.hpp"

class SensorController : public Platform, public ISubscriber<unsigned, std::string>
{
public:
    SensorController(unsigned notifInterval, unsigned buffersSize);
    ~SensorController();
    void addSensor(std::unique_ptr<Sensor> sensor);

    // data from any Sensor
    void onDataReceived(const unsigned& sensorId, const std::string& data) override;
    void start();
    void waitToExit();

private:
    unsigned notifInterval_;
    std::unordered_map<unsigned, std::unique_ptr<Sensor>> sensors_;
    bool isWorking_ = true;
    WorkerThread worker_;
};