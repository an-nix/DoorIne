#ifndef HEADER_SERVER__
#define HEADER_SERVER__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <thread>
#include <list>
#include "client.h"
#include "clientComHandler.h"

class CamServer
{

    private: 
        int socket_fd;
        struct sockaddr_in address;
        std::thread listeningThread;

        std::list<ClientCommunicationHandler*> clientsList;
        std::thread deletionThread;

        //Remove Closed Clients
        void clientsDeletion();

    public:
        //Constructor
        CamServer(int);
        //Destructor
        ~CamServer();
                
        void open();
        void stop();
        void waitConnect();
};


#endif