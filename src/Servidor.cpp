//============================================================================
// Name        : Servidor.cpp
// Author      : Tony
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>

using boost::asio::ip::tcp;
boost::asio::io_service io_service;


int main()
{
    try
    {


        	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 22));

        for (;;)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            const char message[] = "HTTP/1.0 200 OK\r\n\r\n<html><body><i>Hello, world</i></body></html>";

            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
