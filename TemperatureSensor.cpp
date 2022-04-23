#include "TemperatureSensor.hpp"

#include <string>

TemperatureSensor::TemperatureSensor(unsigned id, unsigned frequency, int tempMin, int tempMax)
    : Sensor(id, frequency)
    , randDev_{}
    , randEngine_{randDev_()}
    , randDist_{tempMin, tempMax}
{
}

std::string TemperatureSensor::prepareNextData()
{
    return std::to_string(randDist_(randEngine_));
}
