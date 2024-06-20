#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <future>

#ifndef THREADPOOL_H
#define THREADPOOL_H

class ThreadPool {
public:
    ThreadPool(size_t num_threads);
    ~ThreadPool();
    std::future<double> enqueueJob(const std::function<double(void)>& job);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> jobs;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;
};

ThreadPool::ThreadPool(size_t num_threads) {
    for (size_t i = 0; i < num_threads; ++i) {
        workers.emplace_back([this] {
            while (true) {
                std::function<void()> job;
                {
                    std::unique_lock<std::mutex> lock(this->mtx);
                    this->cv.wait(lock, [this] { return this->stop || !this->jobs.empty(); });
                    if (this->stop && this->jobs.empty()) return;
                    job = std::move(this->jobs.front());
                    this->jobs.pop();
                }
                job();
            }
        });
    }
}

std::future<double> ThreadPool::enqueueJob(const std::function<double(void)>& job) {
    auto future = std::make_shared<std::promise<double>>();
    {
        std::unique_lock<std::mutex> lock(mtx);
        if (stop) throw std::runtime_error("enqueue on stopped ThreadPool");
        jobs.emplace([job, future]() {
            double result = job();
            future->set_value(result);
        });
    }
    cv.notify_one();
    return future->get_future();
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();
    for (std::thread &worker : workers) worker.join();
}


#endif //THREADPOOL_H
