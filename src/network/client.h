#ifndef HEADER_CLIENT_FACTORY__
#define HEADER_CLIENT_FACTORY__

#include <iostream>
#include <unistd.h>
#include <thread>
#include "client.h"
#include <sys/socket.h>


#define RCV_BUFFER 1024


/***
 * Base Client  
 */
 
enum CLIENT_TYPE
{
  UNKWOWN = 0,
  GENERIC = 1,
  PYTHON = 2,
};

class AbstractClient
{
  public:
    virtual std::string Operation()const=0;
    
    
  private:
    virtual void onMessage()=0;
};

class GenericClient : public AbstractClient
{
    private:
        void onMessage();
        std::thread clientThread;
        int socket;
    public:
        GenericClient();
        std::string Operation() const override;
       
};

class PythonClient : public AbstractClient
{
    private:
        void onMessage();
        std::thread clientThread;
        int socket;

    public:
        PythonClient();
        std::string Operation() const override;

};




class ClientCreator
{
   public:
        virtual ~ClientCreator(){};
        virtual AbstractClient* FactoryMethod() const = 0;

  std::string SomeOperation() const {
    // Call the factory method to create a Product object.
    AbstractClient* product = this->FactoryMethod();
    // Now, use the product.
    std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
    delete product;
    return result;
  }

};

class GenericClientCreator : public ClientCreator {

 public:
    AbstractClient* FactoryMethod() const override;
};

class PythonClientCreator : public ClientCreator 
{
  public:
    AbstractClient* FactoryMethod() const override;
};

void ClientCode(const ClientCreator&);


class ClientCommunicationHandler
{
  public:
    std::thread clientThread;
    int clientSocket;
    AbstractClient* client;

    bool running;
    bool socketOpen;

    char* buffer;

    ClientCommunicationHandler(int socket);
    void start();
    void stop();
    void run();
    int clientInit();
};

#endif