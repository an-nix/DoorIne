#include "clientManager.h"


ClientManager::ClientManager()
{
    
}

ClientManager::~ClientManager()
{
    
}

void ClientManager::onMessage()
{


// MessageType  Client Type
// bbbb         bbbb


}


void ClientManager::fctInit(char* data)
{

    //get Client Type   
    this->type = (CLIENT_TYPE)data[0];

    //get Cilent Version 
    this->version = (int)data[1];

    this->width = ((int)data[3] >> 8) + (int)data[2];
    this->height = ((int)data[5] >> 8) + (int)data[4];

    //xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
    //type     version  width             height

    //0xCT 0xCV 0xWIDT 0xHEIGHT
    
    // client type
    // coupling version
    // width
    // height
    


}