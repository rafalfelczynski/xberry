#pragma once

#include <iostream>
#include "ISensorListener.hpp"

class GeneralSensorListener : public ISensorListener
{
    void onDataReceived(const unsigned& sensorId, const std::vector<std::string>& messages) override
    {
        std::cout << "Last messages from sensor: " << std::to_string(sensorId) << std::endl;
        for(const auto& msg : messages)
        {
            std::cout << msg << " ";
        }
        std::cout << std::endl;
    }
};

