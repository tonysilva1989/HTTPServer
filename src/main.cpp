/*
 * main.cpp
 *
 *  Created on: 28 de dez de 2017
 *      Author: iginochaves
 */

#include <iostream>
#include "server.cpp"
#include "client.cpp"
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <pthread.h>
#include <chrono>


using namespace std;

int main(){

	Client client(service,"127.0.0.1","2222");

}
