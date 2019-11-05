#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include<vector>
#include<queue>
#include<memory>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<future>
#include<functional>
#include<stdexcept>
#include<iostream>

/**
 * This object will be treated as another thread, with the amount of workers
 **/
class ThreadPool{
    public:
        ThreadPool(int);
        template<class F, class... Args>
        auto enqueue(F&& f,Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
        void run();
        ~ThreadPool();
    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> queueTasks;
        std::mutex mutex;
        std::condition_variable condition;
        bool stop;
        int  size;
};


template<class F, class... Args>
        auto ThreadPool::enqueue(F&& f,Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>{
            /**
             * get the type will be return to the user
             **/
            using get_type = typename std::result_of<F(Args...)>::type;
            auto task = std::make_shared<std::packaged_task<get_type()>>(
                std::bind(std::forward<F>(f),std::forward<Args>(args)...) 
            );

            std::future<get_type> response = task->get_future();
            std::unique_lock<std::mutex> lock(this->mutex);
            queueTasks.emplace([task](){
                (*task)();
            });
            condition.notify_one();
            return response;
        }
#endif


