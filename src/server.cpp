/*
 * Servidor2.cpp
 *
 *  Created on: 25 de dez de 2017
 *      Author: tony
 */

/*
 * GET structure:
	    GET  HTTP/1.1
		Host: 127.0.0.1:2222
		Cache-Control: no-cache
		Postman-Token: 0f953db6-a126-3d44-c1a7-5b2a195e827c
 *
 */

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <pthread.h>
#include <chrono>


using boost::asio::ip::tcp; //utiliza o space tcp

void server(){
	try
	    {
	        boost::asio::io_service io_service; //representa o link do programa para o serviço I/O do sistema

	        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 2222)); //escuta uma nova conexão com o endpoint especificado
	        tcp::socket socket(io_service); //cria um novo socket


	        while(true)
	        {
	            acceptor.accept(socket); //aceita uma nova conexão

	            //reading response
	            boost::asio::streambuf response;
	            read_until(socket, response, "\r\n"); //lendo async response
	            boost::asio::streambuf::const_buffers_type bufs = response.data();
	            int rSize = response.size();
	            std::string resposta(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + rSize);

	            std::cout << resposta << std::endl;


	            //respondendo a uma requisição get
	            const char message[] = "HTTP/1.0 200 OK\r\n\r\n<html><body><i>Hello World HTML Page!</i></body></html>";

	            boost::system::error_code ignored_error;
	            boost::asio::write(socket, boost::asio::buffer(message), ignored_error); //envio da response
	            //socket.send(boost::asio::buffer("HTTP/1.0 200 OK\r\n\r\n<html><body><i>Respondendo!</i></body></html>"));

	            socket.close();


	        }
	    }
	    catch (std::exception& e)
	    {
	        std::cerr << e.what() << std::endl;
	    }
}


int main()
{
    server();

    return 0;
}




/*
 *
 * versão sem loop (aceita apenas uma conexão, depois encerra
 *
//#include "stdafx.h"
#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio::ip;

boost::asio::io_service ioService; //We need to create a server object to accept incoming client connections. The io_service object provides I/O services, such as sockets, that the server object will use.
tcp::resolver resolver(ioService);
tcp::acceptor acceptor(ioService);
tcp::socket tcpSocket(ioService);
int cont=0;

//método para exibir o callback da requisição
void onAccept(const boost::system::error_code &ec){
	if(ec){
		std::cout << "Erro ao aceitar a conexão com mensagem: " << ec.message() << std::endl;
	}else{
		std::stringstream response;
		response << "HTTP/1.1 200 OK\r\n";
		response << "\r\n";
		response << "<html>\r\n";
		response << "<body><h1><i>Ola, mundo!</i></h1></body>\r\n";
		tcpSocket.send(boost::asio::buffer(response.str()));
		std::cout << response.str() << std::endl;
		std::cout << cont << std::endl;
		cont ++;
	}
}

int main(){

	tcp::resolver::query query("127.0.0.1","1333"); //no Unix, as primeiras 1024 portas são reservadas a root users
	tcp::endpoint endpoint = *(resolver.resolve(query)); // ponto de conexão
	acceptor.open(endpoint.protocol()); //assinala se é ipv4 ou ipv6
	acceptor.bind(endpoint); //liga o endpoint com o socket
	acceptor.listen(boost::asio::socket_base::max_connections);

	//while(true)
	acceptor.async_accept(tcpSocket,onAccept);

	//A call to io_service::run() blocks while there are unfinished asynchronous operations, so you would typically call it as soon as you have started your first asynchronous operation.
	ioService.run();

}
*/
