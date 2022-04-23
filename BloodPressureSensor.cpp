#pragma once

#include "BloodPressureSensor.hpp"

const std::uniform_int_distribution<int>::param_type BloodPressureSensor::SYSTOLIC_MIN_MAX =
    std::uniform_int_distribution<int>::param_type(100, 200);
const std::uniform_int_distribution<int>::param_type BloodPressureSensor::DIASTOLIC_MIN_MAX =
    std::uniform_int_distribution<int>::param_type(40, 100);
const std::uniform_int_distribution<int>::param_type BloodPressureSensor::PULSE_MIN_MAX =
    std::uniform_int_distribution<int>::param_type(50, 150);

BloodPressureSensor::BloodPressureSensor(unsigned id, unsigned frequency)
    : Sensor(id, frequency)
    , randDev_{}
    , randEngine_{randDev_()}
    , randDist_{0, 250}
{
}

std::string BloodPressureSensor::prepareNextData()
{
    return toString(prepareBloodPressureData());
}

BloodPressure BloodPressureSensor::prepareBloodPressureData()
{
    BloodPressure bp;
    randDist_.param(DIASTOLIC_MIN_MAX);
    bp.diastolic = randDist_(randEngine_);

    randDist_.param(SYSTOLIC_MIN_MAX);
    bp.systolic = randDist_(randEngine_);

    randDist_.param(PULSE_MIN_MAX);
    bp.pulse = randDist_(randEngine_);
    return bp;
}
