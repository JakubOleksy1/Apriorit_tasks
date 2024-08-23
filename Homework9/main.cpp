#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <future>
#include <condition_variable>
#include <mutex>

class SimpleThreadPool {
public:
    explicit SimpleThreadPool(std::size_t threadCount);
    ~SimpleThreadPool();

    SimpleThreadPool(const SimpleThreadPool&) = delete;
    SimpleThreadPool& operator=(const SimpleThreadPool&) = delete;

    template <typename Fnc_T>
    auto Post(Fnc_T task) -> std::future<decltype(task())>;

    void WorkOn();
    void Destroy();
    
    std::mutex cout_mutex; // Mutex for synchronizing cout

private:
    void Worker();

    size_t m_threadCount;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::condition_variable condition;
    std::mutex mut;
    bool stop;
};

SimpleThreadPool::SimpleThreadPool(std::size_t threadCount)
    : m_threadCount(threadCount), stop(false) {
    WorkOn();
}

SimpleThreadPool::~SimpleThreadPool() {
    Destroy();
}

template <typename Fnc_T>
auto SimpleThreadPool::Post(Fnc_T task) -> std::future<decltype(task())> {
    auto packaged_task = std::make_shared<std::packaged_task<decltype(task())()>>(task);
    std::future<decltype(task())> result = packaged_task->get_future();

    {
        std::unique_lock<std::mutex> lock(mut);
        tasks.emplace([packaged_task]() { (*packaged_task)(); });
    }

    condition.notify_one();
    return result;
}

void SimpleThreadPool::WorkOn() {
    for (size_t i = 0; i < m_threadCount; ++i) {
        threads.emplace_back(&SimpleThreadPool::Worker, this);
    }
}

void SimpleThreadPool::Destroy() {
    {
        std::unique_lock<std::mutex> lock(mut);
        stop = true;
    }

    condition.notify_all();
    for (std::thread &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void SimpleThreadPool::Worker() {
    while (true) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(mut);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });

            if (stop && tasks.empty()) {
                return;
            }

            task = std::move(tasks.front());
            tasks.pop();
        }

        task();
    }
}

int main() {
    SimpleThreadPool pool(4);

    auto future1 = pool.Post([&]() {
        {
            std::lock_guard<std::mutex> lock(pool.cout_mutex);
            std::cout << "Task 1 is running" << std::endl;
        }
        return 1;
    });

    auto future2 = pool.Post([&]() {
        {
            std::lock_guard<std::mutex> lock(pool.cout_mutex);
            std::cout << "Task 2 is running" << std::endl;
        }
        return 2;
    });

    std::cout << "Result from Task 1: " << future1.get() << std::endl;
    std::cout << "Result from Task 2: " << future2.get() << std::endl;

    pool.Destroy();

    return 0;
}