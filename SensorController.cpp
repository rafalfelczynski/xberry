
#include "SensorController.hpp"

#include "ThirdParty/Timer.hpp"

#include "BloodPressureSensor.hpp"
#include "CyclicBuffer.hpp"

SensorController::SensorController(unsigned notifInterval, unsigned buffersSize)
    : Platform(buffersSize), notifInterval_(notifInterval)
{
}

SensorController::~SensorController()
{
    for (const auto& [sensorId, clients] : listenersPerSensor_)
    {
        for (const auto& client : clients)
        {
            finishListening(sensorId, client);
        }
    }
}

void SensorController::addSensor(std::unique_ptr<Sensor> sensor)
{
    auto sensorId = sensor->getId();
    sensor->addObserver(this);
    sensor->run();
    sensors_.emplace(sensorId, std::move(sensor));
}

// data from any Sensor
void SensorController::onDataReceived(const unsigned& sensorId, const std::string& data)
{
    addNewMsg(sensorId, data);
}

void SensorController::start()
{
    auto job = [this]() {
        while (isWorking_)
        {
            publishAvailableMsgs();
            std::this_thread::sleep_for(std::chrono::duration(std::chrono::milliseconds(notifInterval_)));
        }
    };
    worker_.acceptJob(std::move(job));
}

void SensorController::waitToExit()
{
    timer::SingleShotTimer::call(10000, [this]() {
        isWorking_ = false;
        worker_.finish();
    });
    worker_.join();
}
