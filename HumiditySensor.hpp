#pragma once

#include <random>

#include "Sensor.hpp"

class HumiditySensor : public Sensor
{
    static constexpr auto MIN_HUMIDITY = 30.0;
    static constexpr auto MAX_HUMIDITY = 80.0;
public:
    HumiditySensor(unsigned id, unsigned frequency);
    std::string prepareNextData() override;

private:
    std::random_device randDev_;
    std::mt19937 randEngine_;
    std::uniform_real_distribution<> randDist_;
};
