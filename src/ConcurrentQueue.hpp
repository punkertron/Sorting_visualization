#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <condition_variable>
#include <deque>
#include <mutex>
#include <optional>
#include <utility>

template <typename T>
struct ConcurrentQueue {
private:
    mutable std::mutex m_;
    std::condition_variable cvRemove_;
    std::condition_variable cvAdd_;

    std::deque<T> queue_;
    size_t maxSize_;

public:
    ConcurrentQueue(size_t maxSize = std::numeric_limits<size_t>::max()) : maxSize_(maxSize)
    {
    }
    ~ConcurrentQueue() = default;
    ConcurrentQueue(const ConcurrentQueue&) = delete;
    ConcurrentQueue(ConcurrentQueue&&) = delete;
    ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;
    ConcurrentQueue& operator=(ConcurrentQueue&&) = delete;

    void push_back(T value)
    {
        std::unique_lock<std::mutex> lock(m_);
        cvAdd_.wait(lock, [&] {
            return maxSize_ != queue_.size();
        });

        queue_.push_back(std::move(value));
        cvRemove_.notify_one();
    }

    T pop_front()
    {
        std::unique_lock<std::mutex> lock(m_);
        cvRemove_.wait(lock, [&] {
            return !queue_.empty();
        });
        T result = queue_.front();
        queue_.pop_front();
        cvAdd_.notify_one();
        return result;
    }

    std::optional<T> try_pop_front()
    {
        std::lock_guard<std::mutex> lock(m_);

        if (queue_.empty()) {
            return std::nullopt;
        }
        std::optional<T> result = queue_.front();
        queue_.pop_front();
        cvAdd_.notify_one();
        return result;
    }

    const size_t size() const
    {
        std::lock_guard<std::mutex> lock(m_);
        return queue_.size();
    }
};

#endif  // CONCURRENT_QUEUE_H