#pragma once 

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "Ditchr_Clients.h"

using boost::asio::ip::tcp;

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket,std::shared_ptr<Client_require> client_mngr)
    : socket_(std::move(socket)),client_mngr(client_mngr)
  {
    
  }

  void start(){
    do_read();
  }

  void do_read()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, 1),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            if(data_[0]=='\n'){
              client_mngr->make_request(request);
              request.clear();
            }
            else{
              request+=(data_[0]);
            }
          }
        });
  }

  void do_write(const std::string& data_string)
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_string),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            do_read();
          }
        });
  }

private:
  tcp::socket socket_;
  std::shared_ptr<Client_require> client_mngr; 
  char data_[1];
  std::string request;
};

class server
{
public:
  server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    client_mngr = std::make_shared<Client_require>();
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket),client_mngr)->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  std::shared_ptr<Client_require> client_mngr;
};

/*int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    server server(io_context, std::atoi(argv[1]));

    io_context.run();
  }
  catch (const std::exception& ex)
  {
    std::cerr << "Exception: " << ex.what() << "\n";
  }

  return 0;
}
*/