#include "server.h"
#include <iostream>

    CamServer::CamServer(int port)
    {
       
        int opt = 1;

        // Creating socket file descriptor
        if ((this->socket_fd = socket(AF_INET, SOCK_STREAM, 0))== 0) 
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        this->address.sin_family=AF_INET;     // TCP/IP
        this->address.sin_addr.s_addr=INADDR_ANY;     // server addr--permit all connection
        this->address.sin_port=htons(port);       // server port
    }

    CamServer::~CamServer()
    {
        this->stop();
    }


    void CamServer::print()
    {
        std::cout << "Hello, From Class!\n";
    }

    void CamServer::open()
    {

         // Forcefully attaching socket to the port 8080
        if (bind(this->socket_fd, (struct sockaddr*)&this->address,sizeof(this->address))< 0) 
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        if (listen(this->socket_fd, 3) < 0) 
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        // Open Waiting Thread
        this->listeningThread = std::thread{&CamServer::waitConnect,this};
    }

    void CamServer::waitConnect()
    {
         std::cout << "Thread Start!\n";
        int addrlen = sizeof(this->address);
        
        int new_socket;

        while(true)
        {
            if ((new_socket = accept(this->socket_fd, (struct sockaddr*)&this->address, (socklen_t*)&addrlen)) < 0) 
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            std::cout << "New Client\n";
            ClientCommunicationHandler* cch = new ClientCommunicationHandler(new_socket);
            
            this->clientsList.push_back(cch);
            cch->start();
        }
         std::cout << "Thread Stop!\n";
    }

    void CamServer::ClientGarbage()
    {
        std::list<ClientCommunicationHandler*>::iterator i = this->clientsList.begin();
        while (i != this->clientsList.end())
        {
            bool isActive = (*i)->socketOpen;
            if (!isActive)
            {
                (*i)->stop();
                delete(*i);
                this->clientsList.erase(i++);  // alternatively, i = items.erase(i);
            }
            else
            {
                //other_code_involving(*i);
                ++i;
            }
}
    }

    void CamServer::stop()
    {
        // closing the listening socket
        //Wait for listening thread Close
        this->listeningThread.join();
        /*for (auto &i : this->clientsList) 
        {
            i.Thread.join();
        }*/
        shutdown(this->socket_fd, SHUT_RDWR);
    }

