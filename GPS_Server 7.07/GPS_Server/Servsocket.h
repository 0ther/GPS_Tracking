#pragma once


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



std::string JSONtoSTRING(std::ifstream& input) { //Вот эта функция работает супер круто
	std::string Ranswer, answer;

	while (getline(input, answer))
	{
		//std::cout << answer << std::endl;
		answer.erase(0, 1);
		if (answer.size() == 0) continue;
		for (int i = 0; i < 3; i++)	answer.erase(0, answer.find_first_of("\"") + 1);
		answer.erase(answer.find_first_of("\""), answer.npos);
		//std::cout << answer << std::endl;
		Ranswer += answer;
		Ranswer += " ";
	}

	return Ranswer;
}

void WriteIntoDatabase(std::string login, std::string value) { 
	std::string filename = login + ".txt";

	std::ofstream out;
	out.open("logusers.txt", std::ios::app);
	out << value << std::endl;

}



void ClientHandler(SOCKET Sock, int index, std::string login) {


	while (true) {


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

	WriteIntoDatabase(login, Aw);
	
	
	}

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


std::string TOString(char *ptr, int length)
{
	std::string answer = {};
	for (int i = 0; i < length; i++) {
		answer += ptr[i];

	}

	return answer;
}











std::string FormId() {
	char *str = new char[1024];
	int i = 0;
	std::ifstream base("logusers.txt");
	while (!base.eof())
	{
		base.getline(str, 1024, '\n');
		i++;
	}
	base.close();
	delete str;
	std::string answer = {};
	if (i < 10) answer += "0";
	answer += std::to_string(i);
	return answer;
}


void AddNewUser(std::string id, std::string login, std::string pass) {
	std::ofstream out;
	out.open("logusers.txt", std::ios::app);
	out << "id=" << id << " login=" << login << " pass=" << pass << "\n";
	out.close();


}





bool IsRegistered(std::string login, std::string pass, std::string filename) {
	std::string example1 = {};
	std::string example2 = {};
	example1 += "login=";
	example1 += login;
	example2 += "pass=";
	example2 += pass;

	std::cout << "Строка выглядит так: " << example1 << " " << example2 << std::endl;

	if (find_word(filename, example1) && find_word(filename, example2)) return true;
	else return false;
}

void catch_aut(SOCKET Sock) {
	char login[6] = {};
	recv(Sock, login, sizeof(login), NULL);
	recv(Sock, login, sizeof(login), NULL);
	//std::cout << login << std::endl;

	char* now = new char[6];
	std::string Looogin;
	for (int i = 0; i < 6; i++) {
		now[i] = login[i];
		Looogin += now[i];
	}

	std::cout << Looogin << std::endl;

	char pass[6] = {};
	recv(Sock, pass, sizeof(pass), NULL);
	recv(Sock, pass, sizeof(pass), NULL);
	//std::cout << pass << std::endl;

	char* noow = new char[6];
	std::string Paass;
	for (int i = 0; i < 6; i++) {
		noow[i] = pass[i];
		Paass += noow[i];
	}

	std::cout << Paass << std::endl;


	if (IsRegistered(Looogin, Paass, "logusers.txt")) {

		std::cout << "Такой пользователь зарегистрирован" << std::endl;
		const char msg2[] = "1";
		send(Sock, msg2, sizeof(msg2), NULL);
		std::cout << "Прошел проверку" << std::endl;
	}
	else {
		const char errmsg4[] = "Сервер: Не удалось авторизоваться\n";
		send(Sock, errmsg4, sizeof(errmsg4), NULL);
		std::cout << "ne Прошел проверку" << std::endl;
	}
}







void catch_reg(SOCKET Sock) {

	char login[6] = {};
	recv(Sock, login, sizeof(login), NULL);
	recv(Sock, login, sizeof(login), NULL);
	//std::cout << login << std::endl;

	char* now = new char[6];
	std::string Looogin;
	for (int i = 0; i < 6; i++) {
		now[i] = login[i];
		Looogin += now[i];
	}

	//std::cout << Looogin << std::endl;
	

	
	if (find_word("logusers.txt", Looogin)) {
		const char errmsg1[] = "Сервер: Пользователь с таким логином уже есть, давай по-новой\n";
		send(Sock, errmsg1, sizeof(errmsg1), NULL);
		catch_reg(Sock);
	}
	else {
		const char msg2[] = "1";
		send(Sock, msg2, sizeof(msg2), NULL);

		char pass[6] = {};
		recv(Sock, pass, sizeof(pass), NULL);
		recv(Sock, pass, sizeof(pass), NULL);
		//std::cout << pass << std::endl;

		char* noow = new char[6];
		std::string Paass;
		for (int i = 0; i < 6; i++) {
			noow[i] = pass[i];
			Paass += noow[i];
		}




		AddNewUser(FormId(), Looogin, Paass);

		std::string alittlebitlonger = "login=";
		alittlebitlonger += Looogin;


		if (find_word("logusers.txt", alittlebitlonger)) {
			const char msg3[] = "1";
			send(Sock, msg3, sizeof(msg3), NULL);
			


			catch_aut(Sock);

		}
		else {
			const char errmsg2[] = "Сервер: Не записались данные\n";
			send(Sock, errmsg2, sizeof(errmsg2), NULL);
		}

	}

	
}








void catch_files(SOCKET Sock, int index) {
	char msg1[256] = "Сервер: Давай сюда свой логин\n";
	send(Sock, msg1, sizeof(msg1), NULL);

	char login[256];
	recv(Sock, login, sizeof(login), NULL);
	std::cout << login << std::endl;

	ClientHandler(Sock, index, login);

}








void Sorting(SOCKET Sock, int type, int index) {
	switch (type) {
	case 1: //Сообщения этого типа передаются при регистрации
		catch_reg(Sock);
		break;
	case 2: //Сообщения этого типа передаются при автризации
		catch_aut(Sock);
		break;
	case 3: //Сообщения этого типа передаются при подготовке к передаче данных
		catch_files(Sock, index);
		break;
	case 4: //Резерв, пока что. Пускай тут будет сброс

		break;
	default: //Для всего остального
		std::cout << "Фигню передал какую-то" << std::endl;
		break;
	}
}


void Connect() {



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


	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	if (newConnection == 0) {
		std::cout << "Error #2\n";
	}
	else {
		std::cout << "Client Connected!\n";
		//Вот тут надо принять сообщение о типе взаимодействия
		char* msg = new char[1];
		recv(newConnection, msg, 1, NULL);
		int choice = *msg - '0';
		Sorting(newConnection, choice, 0);


		//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
	}


}
