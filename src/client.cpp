/*
 * client.cpp
 *
 *  Created on: 26 de dez de 2017
 *      Author: tony
 */


//g++ client.cpp -o client -lpthread -lboost_system

#include <boost/asio.hpp>
#include <iostream>

struct Client
{
    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::socket socket;

    Client(boost::asio::io_service& svc, std::string const& host, std::string const& port)
        : io_service(svc), socket(io_service)
    {
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::iterator endpoint = resolver.resolve(boost::asio::ip::tcp::resolver::query(host, port));
        boost::asio::connect(this->socket, endpoint);
    };

    void send() {

		std::stringstream request_stream;

		request_stream << "POST HTTP/1.1 \r\n";
		request_stream << "Host:" << "127.0.0.1:2222" << "\r\n";
		request_stream << "User-Agent: C/1.0";
		request_stream << "Content-Type: application/json; charset=utf-8 \r\n";
		request_stream << "" << "\r\n";
		request_stream << "Accept: */*\r\n";
		request_stream << "Connection: close\r\n\r\n";

		std::string const& message = "POST /title/ HTTP/1.1 \r\nHost: 127.0.0.1:2222\r\nUser-Agent: C/1.0Content-Type: application/json; charset=utf-8 \r\n\r\nAlguma coisa de novo";

        socket.send(boost::asio::buffer(message));
    }
};



int main(){

    boost::asio::io_service svc;
    Client client(svc, "127.0.0.1","2222");



    client.send();
    //client.send("bye world\n");
}


//
// sync_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//#include <iostream>
//#include <istream>
//#include <ostream>
//#include <string>
//#include <boost/asio.hpp>
//
//using boost::asio::ip::tcp;
//
//int main(int argc, char* argv[])
//{
//  try
//  {
//
//    if (argc != 3)
//    {
//      std::cout << "Usage: client <server> <path>\n";
//      std::cout << "Example:\n";
//      std::cout << "  sync_client www.boost.org /LICENSE_1_0.txt\n";
//      return 1;
//    }
//
//    boost::asio::io_service io_service;
//
//    // Get a list of endpoints corresponding to the server name.
//    tcp::resolver resolver(io_service);
//    tcp::resolver::query query(argv[1], "http");
//    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
//
//    // Try each endpoint until we successfully establish a connection.
//    tcp::socket socket(io_service);
//    boost::asio::connect(socket, endpoint_iterator);
//
//    // Form the request. We specify the "Connection: close" header so that the
//    // server will close the socket after transmitting the response. This will
//    // allow us to treat all data up until the EOF as the content.
//    boost::asio::streambuf request;
//    std::ostream request_stream(&request);
//    request_stream << "GET " << argv[2] << " HTTP/1.0\r\n";
//    request_stream << "Host: " << argv[1] << "\r\n";
//    request_stream << "Accept: */*\r\n";
//    request_stream << "Connection: close\r\n\r\n";
//
//    // Send the request.
//    boost::asio::write(socket, request);
//
//    // Read the response status line. The response streambuf will automatically
//    // grow to accommodate the entire line. The growth may be limited by passing
//    // a maximum size to the streambuf constructor.
//    boost::asio::streambuf response;
//    boost::asio::read_until(socket, response, "\r\n");
//
//    // Check that response is OK.
//    std::istream response_stream(&response);
//    std::string http_version;
//    response_stream >> http_version;
//    unsigned int status_code;
//    response_stream >> status_code;
//    std::string status_message;
//    std::getline(response_stream, status_message);
//    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
//    {
//      std::cout << "Invalid response\n";
//      return 1;
//    }
//    if (status_code != 200)
//    {
//      std::cout << "Response returned with status code " << status_code << "\n";
//      return 1;
//    }
//
//    // Read the response headers, which are terminated by a blank line.
//    boost::asio::read_until(socket, response, "\r\n\r\n");
//
//    // Process the response headers.
//    std::string header;
//    while (std::getline(response_stream, header) && header != "\r")
//      std::cout << header << "\n";
//    std::cout << "\n";
//
//    // Write whatever content we already have to output.
//    if (response.size() > 0)
//      std::cout << &response;
//
//    // Read until EOF, writing data to output as we go.
//    boost::system::error_code error;
//    while (boost::asio::read(socket, response,
//          boost::asio::transfer_at_least(1), error))
//      std::cout << &response;
//    if (error != boost::asio::error::eof)
//      throw boost::system::system_error(error);
//  }
//  catch (std::exception& e)
//  {
//    std::cout << "Exception: " << e.what() << "\n";
//  }
//
//  return 0;
//}
