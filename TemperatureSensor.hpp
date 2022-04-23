#pragma once

#include <random>

#include "Sensor.hpp"

class TemperatureSensor : public Sensor
{
public:
    TemperatureSensor(unsigned id, unsigned frequency, int tempMin, int tempMax);
    std::string prepareNextData() override;

private:
    std::random_device randDev_;
    std::mt19937 randEngine_;
    std::uniform_int_distribution<> randDist_;
};
