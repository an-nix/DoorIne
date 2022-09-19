#ifndef HEADER_SERVER__
#define HEADER_SERVER__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <thread>
#include <list>

#include "client.h"



class CamServer
{

    private: 
        int socket_fd;
        struct sockaddr_in address;
        std::thread listeningThread;
        std::list<ClientCommunicationHandler*> clientsList;

        //Remove Closed Clients
        void ClientGarbage();

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