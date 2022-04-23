#include <iostream>

#include "SensorController.hpp"
#include "TemperatureSensor.hpp"
#include "HumiditySensor.hpp"
#include "BloodPressureSensor.hpp"
#include "BloodPressureListener.hpp"
#include "GeneralSensorListener.hpp"

using Id = unsigned;
using Frequency = unsigned;
using Interval = unsigned;
using BufferSize = unsigned;

int main(int argc, char** argv)
{
    std::cout << "ApplicationStarts" << std::endl;
    SensorController controller(Interval(1000), BufferSize(3));
    controller.addSensor(std::make_unique<TemperatureSensor>(Id(1), Frequency(4), 25, 30));
    controller.addSensor(std::make_unique<HumiditySensor>(Id(2), Frequency(2)));
    controller.addSensor(std::make_unique<BloodPressureSensor>(Id(15), Frequency(1)));

    auto client1 = BloodPressureListener();
    auto client2 = GeneralSensorListener();
    controller.listenToSensor(15, &client1);
    controller.listenToSensor(1, &client2);
    controller.listenToSensor(2, &client2);
    controller.start();
    controller.waitToExit();
    return 0;
}