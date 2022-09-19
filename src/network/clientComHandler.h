#ifndef HEADER_CLIENT_COMMUNICATION__
#define HEADER_CLIENT_COMMUNCIATION__

#include <thread>
#include "client.h"

#include <iostream>
#include <unistd.h>
#include <thread>
#include <sys/socket.h>


#define RCV_BUFFER 1024

class ClientCommunicationHandler
{
  public:
    std::thread clientThread;
    int clientSocket;
    AbstractClient* client;

    bool running; /*!< Is the thread running */
    bool socketOpen; /*!< Is the socket open */

    char* buffer; /*!< Receive buffer */

    ClientCommunicationHandler(int socket);
    void start();
    void stop();
    void run();
    int clientInit();  
};

#endif