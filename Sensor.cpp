#include "Sensor.hpp"

Sensor::Sensor(unsigned id, unsigned frequency)
    : id_{id}
    , frequency_(frequency)
{
}

Sensor::~Sensor()
{
    isWorking_ = false;
    worker_.finish();
}

unsigned Sensor::getId() const
{
    return id_;
}

void Sensor::run()
{
    auto job = [this]() {
        while (isWorking_)
        {
            publish(getId(), prepareNextData());
            std::this_thread::sleep_for(std::chrono::duration(std::chrono::milliseconds(1000 / frequency_)));
        }
    };
    worker_.acceptJob(std::move(job));
}