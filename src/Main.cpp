#include<iostream>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

int main(){
	int client, server;
	int portNum=12345;
	bool isExit = false;
	int bufSize = 1024;
	char buffer[bufSize];

	struct sockaddr_in server_addr;
	socklen_t size;

	//início do socket

	client = socket(AF_INET, SOCK_STREAM,0);

	if (client < 0){
		cout << "Erro ao estabelecer conexão" << endl;
		exit(1);
	}

	cout << "Conseguiu estabelecer conexão com o servidor" << endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(portNum);

	//binding socket

	if(bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr)) < 0){
		cout << "Error Binding socket" << endl;
		exit(1);
	}

	size = sizeof(server_addr);
	cout << "Buscando por clientes..." << endl;

	//escutando socket
	listen(client,1);

	//aceitando cliente

	server = accept(client,(struct sockaddr*)&server_addr,&size);

	if (server < 0){
		cout << "erro ao aceitar cliente" << endl;
		exit(1);

	}

	while (server > 0){
		strcpy(buffer,"servidor conectado");
		send(server,buffer,bufSize,0);

		cout << "conectado com o cliente" << endl;
		cout << "digite # para encerrar a conexao" << endl;

		cout << "cliente:" << endl;
		do{
			recv(server, buffer,bufSize,0);
			cout << "buffer" << endl;

			if(*buffer == '#'){
				*buffer = '*';
				isExit = true;
			}
		}while(*buffer != '#');
	do{
		do{
			cout << "servidor:" << endl;

			cin >> buffer;

			send(server,buffer,bufSize,0);

			if(*buffer == '#'){
				send(server,buffer,bufSize,0);
				buffer = '*';
				isExit = true;

			}
		}while(*buffer != '*');

		cout << "Client: " << endl;
		do {
			recv(server,buffer,bufSize,0);
			cout << buffer << " ";
			if(*buffer == '#'){
				buffer = '*';
				isExit = true;

			}
		}while(*buffer != '*');
	}while(!isExit);


	cout << "conexão encerrada" << endl;
	exit(1);

	}

	close(client);

	//TODO: fazer o código do servidor para testar
	//https://www.youtube.com/watch?v=IydkqseK6oQ

}

