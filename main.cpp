#include "ThreadPool.hpp"
#include <iostream>
#include <chrono>
int main(){
    int workers;
    std::cin>>workers;
    ThreadPool pool(workers);
    std::vector<std::future<int>> results;

    std::cout<<"Hello"<<std::endl;
    for(int i = 0; i < 20; i++) {
        results.emplace_back(
            pool.enqueue(
                [i] {
                    std::cout<<"Hello from task # "<< i <<std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    return i*i;
                }
            )   
        );
    }
    for(auto && result:results){
        std::cout<<result.get()<<std::endl;
    }
    std::cout<<"Hello world"<<std::endl;
}
