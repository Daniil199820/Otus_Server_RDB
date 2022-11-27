#include "Observer.h"
#include "Ditchr_Data.h"
#include "Server.h"
#include <memory>
class DB_Responce:public Observer{

    DB_Responce(std::shared_ptr<Data_storage> data_store, std::shared_ptr<session> session_server):data_store(data_store),
    session_server(session_server){
        data_store.get()->addObserver(this);
    }

    void update(const std::string& arg){
        session_server->do_write(arg);
    }

private:
    std::shared_ptr<Data_storage> data_store;
    std::shared_ptr<session> session_server;
    
};