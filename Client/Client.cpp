
#include <boost/asio.hpp>

#include <array>
#include <iostream>
#include <string>
#include <thread>

namespace ba = boost::asio;

class AsyncClient {
public:
    AsyncClient(ba::io_context& io_context)
        : m_tcp_socket{io_context}{

    }

    void start(){
        ba::ip::tcp::endpoint ep(
            ba::ip::address::from_string(
                "127.0.0.1"
            ),
           9000
        );

        m_tcp_socket.async_connect(
            ep,
            [&](const boost::system::error_code &ec) {
                this->connectHandler(ec);
            }
        );
    }
    // Active object? :)

private:

    void connectHandler(const boost::system::error_code &ec) {
        if (ec) {
            std::cout << "connectHandler - failed! err = " << ec.message() << std::endl;
            return;
        }

        const std::string request = "INSERT A 1 Lean\n";

        ba::write(m_tcp_socket, ba::buffer(request));

        m_tcp_socket.async_read_some(
            ba::buffer(m_buffer),
            [&](const boost::system::error_code &ec, std::size_t bytes_transferred) {
                this->readHandler(ec, bytes_transferred);
            }
        );
    }

    void readHandler(const boost::system::error_code &ec, std::size_t bytes_transferred) {
        
        if (ec) {
            std::cout << "readHandler - failed! err = " << ec.message() << std::endl;
            return;
        }

        if (!bytes_transferred) {
            std::cout << "readHandler - no more data!" << std::endl;
            return;
        }

        std::cout.write(m_buffer.data(), bytes_transferred);
        m_tcp_socket.async_read_some(
            ba::buffer(m_buffer),
            [&](const boost::system::error_code &ec, std::size_t bytes_transferred) {
                readHandler(ec, bytes_transferred);
            }
        );
    }

    ba::ip::tcp::socket m_tcp_socket;
    std::array<char, 4096> m_buffer;

};

int main() {

    ba::io_context io_context;

    AsyncClient client{ io_context };

    client.start();

    io_context.run();

    std::cout << "After the io_context.run() " << std::endl;

    return 0;
}