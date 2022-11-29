#pragma once
#include "Observer.h"
#include "Ditchr_Data.h"
#include "Server.h"
#include <memory>
#include "Ditchr_Clients.h"

class Session_DB{
public:
    virtual void do_write(const std::string& arg) = 0;

};

class DB_Responce:public Observer{
public:
    DB_Responce(Client_require* cl_mngr, Session_DB* session_server):
    cl_mngr(cl_mngr),session_server(session_server){
        cl_mngr->get_Data_Storage_ptr().get()->addObserver(this);
    }
    void update(const std::string& arg){
        session_server->do_write(arg);
    }

private:
    Client_require* cl_mngr;
    Session_DB* session_server;

    
};