#include "clientComHandler.h"


ClientCommunicationHandler::ClientCommunicationHandler(int socket)
{
    this->running = true;
    this->socketOpen = true;
    this->buffer = (char*)malloc(RCV_BUFFER*sizeof(char));
    this->clientSocket = socket;
}

void ClientCommunicationHandler::run()
{
    // initiate communication
    int init = clientInit();
    //nominal communication
    while(this->running & this->socketOpen)
    {
        std::cout << "Communication init\n";
        int valRcv = recv(this->clientSocket,this->buffer,1024,0);
        if(valRcv == 0)
        {
            this->socketOpen = false;
            std::cout << "Communication closed \n";
            //return -1;
        }
    }
    std::cout << "Quit Communication Handler \n";
}

// Wait for initialisation message
int ClientCommunicationHandler::clientInit()
{
    std::cout << "Waiting Init Data" << "\n";
    int valRcv = recv(this->clientSocket,this->buffer,1024,0);
    if(valRcv == 0)
    {
        this->socketOpen = false;
        std::cout << "Communication closed \n";
        return -1;
    }
    std::cout << "Received " << valRcv << "\n";

    int couplingType = (buffer[0] & 0xF0) >> 4;

    switch(couplingType)
    {
        case CLIENT_TYPE::GENERIC:
            break;

        case CLIENT_TYPE::PYTHON:
            break;

        default:
            break;
    }

    int couplingVersion = (buffer[0] & 0x0F);
    std::cout << "Coupling Type " << couplingType << "\n";
    std::cout << "Coupling Version " << couplingVersion << "\n";

    return 0;
}

void ClientCommunicationHandler::start()
{
    this->clientThread = std::thread{&ClientCommunicationHandler::run,this};
}

void ClientCommunicationHandler::stop()
{
    std::cout<< "Wait thread to stop \n";
    this->clientThread.join();
    std::cout<< "Thread stoped \n";
}
