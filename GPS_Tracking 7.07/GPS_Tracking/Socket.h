#pragma once

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
#include <iostream>
#include <fstream>
#include <string>
#pragma warning(disable: 4996)

SOCKET Connection;

void ClientHandler() {
	int msg_size;
	while (true) {
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		char *msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		std::cout << msg << std::endl;
		delete[] msg;
	}
}

extern bool RecFlag = 1;

void SendingHandler(bool* ReceivingFlag) {

	while (*ReceivingFlag) { //Вопрос: как реализовать отправку файла каждую секунду?

		std::string msg1;
		char buff[60];


		std::ifstream fin("temp.json");

		if (!fin.is_open()) // если файл не открыт
			std::cout << "Файл не может быть открыт!\n"; // сообщить об этом
		else {
			
			while (true) {

				fin.getline(buff, 100);
				msg1 = buff;
				int msg_size = msg1.size();
				send(Connection, (char*)&msg_size, sizeof(int), NULL);
				send(Connection, msg1.c_str(), msg_size, NULL);

				Sleep(10);
				if (msg_size == 0) break;


			}

		}

		fin.close();
		Sleep(930);

	}

}

/*

SOCKET Connect() {

	

	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return;
	}
	std::cout << "Connected!\n";


	

	bool RecFlag = true;



	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendingHandler, &RecFlag, NULL, NULL);



	
	//bool flag;
	//std::cout << "Хотите остановить поток отправки? Введите 0!" << std::endl;
	//std::cin >> flag;
	//if (!flag) {
	//	RecFlag = 0;
	//}



	//shutdown(Connection, SD_BOTH);
	//closesocket(Connection);

	return Connection;
}

*/