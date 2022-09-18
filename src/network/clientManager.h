#ifndef __CLIENTS_MANAGER_HEADER__
#define __CLIENTS_MANAGER_HEADER_


enum CLIENT_TYPE
{
    Generic = 0,

};

enum MESSAGE_TYPE
{
    INIT = 0,


};



class ClientManager
{

    private:

        CLIENT_TYPE type;
        int version;
        int width;
        int height;


        void onMessage();
        void onStart();
        void onClose();

        void fctInit(char*);


    public:
        ClientManager();
        ~ClientManager();


};



#endif
