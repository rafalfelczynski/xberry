#pragma once

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <functional>

#include "Observer/IPublisher.h"
#include "SafeQueue/SafeQueue.h"


struct IJob
{
    virtual ~IJob() = default;
    virtual void execute() = 0;
};

class WorkerThread
{
    enum class State
    {
        Idle,
        Running,
        Stopped
    };

public:
    WorkerThread();
    void acceptJob(std::unique_ptr<IJob> job);
    void acceptJob(std::function<void()> job);

    void run();
    void wakeUp();
    void kill();
    bool isRunning();
    bool hasPendingJobs();
    void join();
    void finish();
    unsigned getNumOfPendingJobs() const;

private:
    void setRunning(bool isRunning);
    void goToSleep();
    void doJobs();
    void doOneJob();
    void ensureCanFinish();

    bool isRunning_;
    bool isExecutingJob_;
    std::unique_ptr<std::thread> thread_;
    State state = State::Idle;
    collections::SafeQueue<std::unique_ptr<IJob>> jobs_;
    std::condition_variable monitor_;
    std::mutex mutex_;
};
