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
    mutable std::mutex m;
    std::condition_variable cv_remove;
    std::condition_variable cv_add;

    std::deque<T> queue;
    size_t max_size;

public:
    ConcurrentQueue(size_t max_size = std::numeric_limits<size_t>::max()) : max_size(max_size)
    {
    }
    ~ConcurrentQueue() = default;
    ConcurrentQueue(const ConcurrentQueue&) = delete;
    ConcurrentQueue(ConcurrentQueue&&) = delete;
    ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;
    ConcurrentQueue& operator=(ConcurrentQueue&&) = delete;

    void push_back(T value)
    {
        std::unique_lock<std::mutex> lock(m);
        cv_add.wait(lock, [&] {
            return max_size != queue.size();
        });

        queue.push_back(std::move(value));
        cv_remove.notify_one();
    }

    T pop_front()
    {
        std::unique_lock<std::mutex> lock(m);
        cv_remove.wait(lock, [&] {
            return !queue.empty();
        });
        T result = queue.front();
        queue.pop_front();
        cv_add.notify_one();
        return result;
    }

    std::optional<T> try_pop_front()
    {
        std::lock_guard<std::mutex> lock(m);

        if (queue.empty()) {
            return std::nullopt;
        }
        std::optional<T> result = queue.front();
        queue.pop_front();
        cv_add.notify_one();
        return result;
    }

    const size_t size() const
    {
        std::lock_guard<std::mutex> lock(m);
        return queue.size();
    }
};

#endif  // CONCURRENT_QUEUE_H