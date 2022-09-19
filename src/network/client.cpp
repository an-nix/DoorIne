#include "client.h"


void ClientCode(const ClientCreator& creator) {

  std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
            << creator.SomeOperation() << std::endl;
}

AbstractClient* GenericClientCreator::FactoryMethod() const
{
    return new GenericClient();    
}

AbstractClient* PythonClientCreator::FactoryMethod() const 
{
    return new PythonClient();
}


GenericClient::GenericClient()
{
    
}

void GenericClient::onMessage()
{

};

std::string GenericClient::Operation() const{
            return "{Result of the ConcreteProduct1}";
}



PythonClient::PythonClient()
{
    
}

void PythonClient::onMessage()
{

};

std::string PythonClient::Operation() const{
            return "{Result of the ConcreteProduct2}";
}
