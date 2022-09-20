#include <iostream>
#include "network/server.h"
#include <chrono>
#include <thread>

#include <opencv2/opencv.hpp>
#include <curl/curl.h>

#include "network/client.h"

#include "lib/test/math.h"
#include "lib/live555/liveMedia/include/liveMedia.hh"
//#include <liveMedia/liveMedia.h>

int main(int, char**) {

    engine::math::add(1,2);

    std::cout << "Server Start\n";

    std::cout << "App: Launched with the ConcreteCreator1.\n";
    ClientCreator* creator = new GenericClientCreator();
    ClientCode(*creator);
    std::cout << std::endl;
    std::cout << "App: Launched with the ConcreteCreator2.\n";
    ClientCreator* creator2 = new PythonClientCreator();
    ClientCode(*creator2);


    CamServer* cs = new CamServer(1234);
    cs->open();
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        //std::cout << "I'm waiting!\n";
    }

}
