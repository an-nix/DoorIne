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

        
        this->deletionThread = std::thread{&CamServer::clientsDeletion,this};
        
    }

    CamServer::~CamServer()
    {
        this->stop();
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
            std::cout << "Push to list!\n";
            this->clientsList.push_back(cch);
            std::cout << "Start!\n";
            cch->start();
            std::cout << "Started!\n";
        }
         std::cout << "Thread Stop!\n";
    }

    // Delete Closed ClientCommunicationHandler
    void CamServer::clientsDeletion()
    {
        std::cout << "Start Deletion Thread \n";
        while(true)
        {
            std::list<ClientCommunicationHandler*>::iterator i = this->clientsList.begin();
            while (i != this->clientsList.end())
            {
                bool isActive = (*i)->socketOpen;
                if (!isActive)
                {
                    //call thread stop
                    (*i)->stop();
                    //dispose object
                    delete(*i);
                    //remove object from list
                    this->clientsList.erase(i++);  // alternatively, i = items.erase(i);
                    std::cout << "Client disposed \n";
                }
                else
                {
                    ++i;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        }
    }

    void CamServer::stop()
    {
        // closing the listening socket
        //Wait for listening thread Close
        this->listeningThread.join();
        this->deletionThread.join();
        /*for (auto &i : this->clientsList) 
        {
            i.Thread.join();
        }*/
        shutdown(this->socket_fd, SHUT_RDWR);
    }

