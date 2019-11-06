#include "ThreadPool.hpp"
#include <iostream>
#include <chrono>
int main(){
    std::cout<<"Enter number of worker:";
    int workers;
    std::cin>>workers;
    ThreadPool pool(workers);
    ThreadPool addJob(workers);
    pool.run();
    std::vector<std::future<int>> results;
    for(int i = 0; i < 10000000; i++) {
        results.emplace_back(
            pool.enqueue(
                [i] {
                    std::cout<<"Hello from task # "<< i <<std::endl;
                    //std::this_thread::sleep_for(std::chrono::seconds(1));
                    return i*i;
                }
            )   
        );
    }

    std::cout<<"Get all result:"<<std::endl;
    for(auto && result:results){
        std::cout<<result.get()<<std::endl;
    }
    std::cout<<"Hello world"<<std::endl;
    //delete pool;
    return 0;
}
