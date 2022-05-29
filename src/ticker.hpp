#ifndef TICKER_HPP
#define TICKER_HPP

#include <memory>
#include <functional>
#include <thread>
#include <vector>
#include <algorithm>

#include "easyloggingpp/easylogging++.h"

class Ticker{
private:
    std::thread ticker;
    std::function<void()> alertFunc = []{LOG(INFO) << "alertFunc not set";};
    bool isRunning = true;
    std::vector<std::shared_ptr<size_t>> counters;
    void ticker_func(){
        while (isRunning) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(0.05s);
            for(auto& i : counters){
                (*i)++;
            }
            alertFunc();
        }
    }
public:
    Ticker():
        ticker{}
    {
        ticker = std::thread{&Ticker::ticker_func, this};
    }
    void setFunc(std::function<void()> f){
        alertFunc = f;
    }
    std::shared_ptr<size_t> registerCounter(){
        counters.push_back(std::make_shared<size_t>(0));
        return *counters.crbegin();
    }
    void ignoreCounter(size_t* counter){
        auto it = std::find_if(counters.begin(), counters.end(),
            [&](const auto& p){return p.get() == counter;});
        counters.erase(it);
    }
    void stop(){
        isRunning = false;
    }
    void join(){
        ticker.join();
    }
};

#endif
