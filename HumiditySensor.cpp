#include "HumiditySensor.hpp"

#include <string>

HumiditySensor::HumiditySensor(unsigned id, unsigned frequency)
    : Sensor(id, frequency)
    , randDev_{}
    , randEngine_{randDev_()}
    , randDist_{MIN_HUMIDITY, MAX_HUMIDITY}
{
}

std::string HumiditySensor::prepareNextData()
{
    return std::to_string(randDist_(randEngine_));
}
