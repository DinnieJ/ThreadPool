#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int numberofworkers)
          : stop(false),
            size(numberofworkers)
{
    run();
}
void ThreadPool::run(){
    for(int i = 0;i<size;++i){
        /**
         *Give task for the worker
         The task will working as a queue, with workers work "lần lượt" till the queue is empty
         **/
        workers.emplace_back([this,i]{
            while(1){
                std::cout<<"Worker #"<< i <<" is working"<<std::endl;
                std::function<void()> task;
                std::unique_lock<std::mutex> lock(this->mutex);
                this->condition.wait(lock,[this]{
                    return this->stop || !this->queueTasks.empty();
                });
                if(this->stop && this->queueTasks.empty()){
                    return;
                }
                task = std::move(this->queueTasks.front());
                this->queueTasks.pop();
                task();
            }
        });
    }
}


// template<class F, class... Args>
// auto ThreadPool::enqueue(F && f,Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type>
// {
    
// }


ThreadPool::~ThreadPool(){
    std::unique_lock<std::mutex> lock(this->mutex);
    this->stop = true;
    this->condition.notify_all();
    for(std::thread &thread: workers){
        thread.join();
    }
    
}


