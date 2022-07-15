#include <iostream>
#pragma comment(lib, "ws2_32.lib") // обеспечивает доступ к некоторым функциям
#include <winsock2.h>
#include <string>

#pragma warning(disable: 4996)

SOCKET Connection;

void clientHandler() { // func to get serv message
	//char msg[256];
	int msgSize;
	while (true) {
		
		recv(Connection, (char*)&msgSize, sizeof(int), NULL);
		char* msg = new char[msgSize + 1];
		msg[msgSize] = '\0';
		recv(Connection, msg, msgSize, NULL);
		std::cout << msg << std::endl;
		delete[] msg;
	}
}

int main() {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	//структура для хранения адреса
	SOCKADDR_IN addr;  // for internet protocol are used sockaddr_in
	int sizeOfAddr = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // collect ip address
	addr.sin_port = htons(1234);


	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error connect";
		return 1;
	} 
	
	std::cout << "Connected" << std::endl;
	
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)clientHandler, NULL, NULL, NULL);
	
	std::string msgClient;
	while (true) {
		std::getline(std::cin, msgClient);
		int lenMsgClient = msgClient.size();
		send(Connection, (char*)&lenMsgClient, sizeof(int), NULL);
		send(Connection, msgClient.c_str(), lenMsgClient, NULL);
		Sleep(100);
	}


	system("pause");
	return 0;
}
