/*
 * Servidor2.cpp
 *
 *  Created on: 25 de dez de 2017
 *      Author: tony
 */

#include "stdafx.h"
#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio::ip;

boost::asio::io_service ioService; //We need to create a server object to accept incoming client connections. The io_service object provides I/O services, such as sockets, that the server object will use.
tcp::resolver resolver(ioService);
tcp::acceptor acceptor(ioService);
tcp::socket tcpSocket(ioService);

//método para exibir o callback da requisição
void onAccept(const boost::system::error_code &ec){
	if(ec){
		std::cout << "Erro ao aceitar a conexão com mensagem: " << ec.message() << std::endl;
	}else{
		std::stringstream response;
		response << "HTTP/1.1 200 OK\r\n";
		response << "\r\n";
		response << "<html>\r\n";
		response << "<body><h1><i>Olá, mundo!</i></h1></body>\r\n";
		tcpSocket.send(boost::asio::buffer(response.str()));
		std::cout << response.str() << std::endl;
	}
}

int main(){

	tcp::resolver::query query("127.0.0.1","1333"); //no Unix, as primeiras 1024 portas são reservadas a root users
	tcp::endpoint endpoint = *(resolver.resolve(query));
	acceptor.open(endpoint.protocol());
	acceptor.bind(endpoint);
	acceptor.listen(boost::asio::socket_base::max_connections);


	acceptor.async_accept(tcpSocket,onAccept);

	ioService.run();

}






