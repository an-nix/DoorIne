#ifndef __SERVER_HEADER__
#define __SERVER_HEADER_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <thread>
#include <list>

#include "clientManager.h"
#include "iClient.h"


class CamServer
{

    private: 
        int socket_fd;
        struct sockaddr_in address;
        std::thread listeningThread;

        std::list<IClient*> clientsList;


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