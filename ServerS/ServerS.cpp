#include <iostream>
#pragma comment(lib, "ws2_32.lib") // обеспечивает доступ к некоторым функциям
#include <winsock2.h>
#include <string>

#pragma warning(disable: 4996)

const int numConnections = 100;

SOCKET connections[numConnections];
int counter;

void clientHandler(int index) {
	char msg[256];
	while (true) {
		recv(connections[index], msg, sizeof(msg), NULL);
		for (int i = 0; i < numConnections; i++) {
			if (i == index) {
				continue;
			} else { 
				send(connections[i], msg, sizeof(msg), NULL);
			}
		}
	}
}

int main() {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	//std::cout << "No er in WSAData" << std::endl;
	//структура для хранения адреса
	SOCKADDR_IN addr;  // for internet protocol are used sockaddr_in
	int sizeOfAddr = sizeof(addr);
	addr.sin_family = AF_INET; 
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // collect ip address
	addr.sin_port = htons(1234);

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); // 
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //connection
	//start listening
	listen(sListen, SOMAXCONN); // descr of sock | max num of requests


	SOCKET newConnection;
	for (int i = 0; i < numConnections; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeOfAddr); // after this func addr will contain inform about user
		if (newConnection == 0) {
			std::cout << "Error connection";
			exit(1);
		}
		else {
			std::cout << "Client connected" << std::endl;
			//std::string str = "BIG BROTHER looking for u " + (std::to_string(i));
			char msg[256] = "BIG BROTHER looking for u ";
			send(newConnection, msg, sizeof(msg), NULL);
		}

		connections[i] = newConnection;
		counter++;

		// create threand to polithreads conversation
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)clientHandler, (LPVOID)(i), NULL, NULL);

	}

	system("pause");

	return 0;
}