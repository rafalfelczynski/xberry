#pragma once
#include <vector>

template<typename T>
class CyclicBuffer
{
public:
    CyclicBuffer(unsigned maxSize)
        : maxSize_(maxSize)
        , nextFreeIndex_(0)
    {
        if (maxSize == 0)
        {
            throw std::invalid_argument("Buffer of size 0 is not allowed");
        }
    }

    template<typename Elem>
    void push(Elem&& elem)
    {
        if (elements_.size() < maxSize_)
        {
            elements_.push_back(std::forward<Elem>(elem));
        }
        else
        {
            elements_[nextFreeIndex_] = std::forward<Elem>(elem);
        }
        nextFreeIndex_ = (nextFreeIndex_ + 1) % maxSize_;
    }

    void clear()
    {
        elements_.clear();
        nextFreeIndex_ = 0;
    }

    auto begin()
    {
        return elements_.begin();
    }

    auto end()
    {
        return elements_.end();
    }

    auto begin() const
    {
        return elements_.begin();
    }

    auto end() const
    {
        return elements_.end();
    }

private:
    unsigned maxSize_;
    unsigned nextFreeIndex_;
    std::vector<T> elements_;
};