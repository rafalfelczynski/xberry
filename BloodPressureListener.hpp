#pragma once

#include <iostream>
#include "Observer/ISubscriber.h"

class BloodPressureListener : public ISubscriber<unsigned, std::vector<std::string>>
{
public:
    void onDataReceived(const unsigned& sensorId, const std::vector<std::string>& messages) override
    {
        std::cout << "Last messages from blood pressure sensor #" << std::to_string(sensorId) << std::endl;
        for(const auto& msg : messages)
        {
            std::cout << msg << " ";
        }
        std::cout << std::endl;
    }
};

