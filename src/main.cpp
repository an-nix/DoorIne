#include <iostream>
#include "network/server.h"
#include <chrono>
#include <thread>


int main(int, char**) {

    std::cout << "Hello, Elena!\n";

    CamServer* cs = new CamServer(1234);
    cs->open();
    cs->print();
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "Hello, Elena!\n";
    }

}
