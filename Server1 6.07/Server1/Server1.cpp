#include "pch.h"

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#pragma warning(disable: 4996)

SOCKET Connections[10];
int Counter = 0;



std::string JSONtoSTRING(std::ifstream& input) {
	std::string Ranswer, answer;

	while (getline(input, answer))
	{
		std::cout << answer << std::endl;
		answer.erase(0,1);
		if (answer.size() == 0) continue;
		for (int i = 0; i < 3; i++)	answer.erase(0, answer.find_first_of("\"") + 1);
		answer.erase(answer.find_first_of("\""), answer.npos);
		std::cout << answer << std::endl;
		Ranswer += answer;
		Ranswer += " ";
	}

	return Ranswer;
}

void WriteIntoDatabase(std::string login, std::string value) {
	std::string filename = login + ".txt";
	
	std::ofstream out(filename);
	out << value;

}



void ClientHandler(int index) {

	



	int msg_size;
	int i = 8;
	std::ofstream Database_1("temp.json");

	std::cout << "Получаем файл от " << index << "-го клиента..." << std::endl;
	while (i > 0) {

		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		//if (msg_size < 2) break;
		char *msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		Database_1 << msg << std::endl; //Вот тут записали строчку в файл
		delete[] msg;
		i--;
	}
	std::cout << "Файл получен!" << std::endl;
	std::ifstream Database_2("temp.json");
	std::string Aw = JSONtoSTRING(Database_2);

	WriteIntoDatabase("csdvge", Aw);
	
	
}





bool find_word(const std::string filename, const std::string word) //Бинарничек для нахождения слова
{
	std::ifstream file(filename);
	std::string tmp;
	while (file >> tmp)
	{
		if (word == tmp)
			return true;
	}
	return false;
}











int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "Russian");

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

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;

	std::cout << "Ожидаем подключений..." << std::endl;

	for (int i = 0; i < 10; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client Connected!\n";
			
			
			



			Connections[i] = newConnection;
			
			
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}


	for (int i = 0; i < 10; i++) {
		shutdown(Connections[i], SD_BOTH);
		closesocket(Connections[i]);
	}

	system("pause");
	return 0;
}