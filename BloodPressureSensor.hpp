#pragma once

#include <random>
#include <string>

#include "Sensor.hpp"

struct BloodPressure
{
    int diastolic;
    int systolic;
    int pulse;
};

inline std::string toString(const BloodPressure& bp)
{
    return "Diastolic: " + std::to_string(bp.diastolic) + " Systolic: " + std::to_string(bp.systolic)
           + " Pulse: " + std::to_string(bp.pulse);
}

class BloodPressureSensor : public Sensor
{
    static const std::uniform_int_distribution<int>::param_type DIASTOLIC_MIN_MAX;
    static const std::uniform_int_distribution<int>::param_type SYSTOLIC_MIN_MAX;
    static const std::uniform_int_distribution<int>::param_type PULSE_MIN_MAX;

public:
    BloodPressureSensor(unsigned id, unsigned frequency);
    std::string prepareNextData() override;

private:
    BloodPressure prepareBloodPressureData();

    std::random_device randDev_;
    std::mt19937 randEngine_;
    std::uniform_int_distribution<> randDist_;
};
