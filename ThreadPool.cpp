#include "ThreadPool.h"

#include <iostream>

#include "ThirdParty/Timer.hpp"


WorkerThread::WorkerThread()
    : isRunning_{true}, isExecutingJob_{false}, thread_(std::make_unique<std::thread>([this]() { run(); }))
{
}

void WorkerThread::acceptJob(std::unique_ptr<IJob> job)
{
    if (isRunning())
    {
        jobs_.enqueue(std::move(job));
        wakeUp();
    }
}

void WorkerThread::acceptJob(std::function<void()> job)
{
    struct AnonymousJob : public IJob
    {
        std::function<void()> functor_;
        inline void execute() override
        {
            functor_();
        }
        inline AnonymousJob(std::function<void()>&& functor)
            : functor_(std::move(functor))
        {
        }
    };
    if (isRunning())
    {
        jobs_.enqueue(std::make_unique<AnonymousJob>(std::move(job)));
        wakeUp();
    }
}

void WorkerThread::run()
{
    while (isRunning_)
    {
        state = State::Running;
        doJobs();
        goToSleep();
    }
    state = State::Stopped;
}

void WorkerThread::wakeUp()
{
    monitor_.notify_all();
}

void WorkerThread::kill()
{
    setRunning(false);
    jobs_.clear();
    wakeUp();
    if (thread_->joinable())
    {
        thread_->detach();
    }
}

bool WorkerThread::isRunning()
{
    std::unique_lock lock(mutex_);
    return isRunning_;
}

bool WorkerThread::hasPendingJobs()
{
    return !jobs_.empty();
}

void WorkerThread::join()
{
    if (thread_->joinable())
    {
        thread_->join();
    }
}

void WorkerThread::finish()
{
    setRunning(false);
    jobs_.clear();
    wakeUp();
}

unsigned WorkerThread::getNumOfPendingJobs() const
{
    const auto numOfJobs = static_cast<unsigned>(jobs_.size());
    return isExecutingJob_ ? numOfJobs+1 : numOfJobs;
}

void WorkerThread::setRunning(bool isRunning)
{
    std::unique_lock lock(mutex_);
    isRunning_ = isRunning;
}

void WorkerThread::goToSleep()
{
    std::unique_lock lock(mutex_);
    state = State::Idle;
    if (isRunning_)
    {
        monitor_.wait(lock);
    }
}

void WorkerThread::doJobs()
{
    while (!jobs_.empty())
    {
        doOneJob();
    }
}

void WorkerThread::doOneJob()
{
    auto job = jobs_.dequeue();
    if (job)
    {
        isExecutingJob_ = true;
        (*job)->execute();
    }
    isExecutingJob_ = false;
}

void WorkerThread::ensureCanFinish()
{
    doJobs();
}
