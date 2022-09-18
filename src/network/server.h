#ifndef __SERVER_HEADER__
#define __SERVER_HEADER_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <thread>


class CamServer
{

    private: 
        int socket_fd;
        struct sockaddr_in address;
        std::thread listeningThread;

    public:
        //Constructor
        CamServer(int);
        //Destructor
        ~CamServer();
        // Test
        void print();
        
        void open();
        void stop();
        void waitConnect();
};


#endif