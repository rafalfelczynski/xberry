#pragma once

#include "Observer/IPublisher.h"

#include "ThreadPool.h"

class Sensor : public IPublisher<unsigned, std::string>
{
public:
    Sensor(unsigned id, unsigned frequency);
    ~Sensor();
    virtual std::string prepareNextData() = 0;
    unsigned getId() const;
    void run();

private:
    unsigned id_;
    unsigned frequency_;
    bool isWorking_ = true;
    WorkerThread worker_;
};
