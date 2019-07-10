#pragma once

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
#include <iostream>
#include <fstream>
#include <string>

#include "logwork.h"

#pragma warning(disable: 4996)

SOCKET Connection;



void SendingHandler() {

		Sleep(860);

		std::string msg1;
		char buff[60];


		std::ifstream fin("temp.json");

		if (!fin.is_open()) { // если файл не открыт
			std::cout << "Файл не может быть открыт!\n"; // сообщить об этом
			WriteIntoLog("Ошибка открытия файла с координатами");
		}
		else {
			
			while (true) {

				fin.getline(buff, 60);
				msg1 = buff;
				int msg_size = msg1.size();
				//send(Connection, (char*)&msg_size, sizeof(int), NULL);
				std::cout << msg1 << std::endl;

				send(Connection, msg1.c_str(), msg_size, NULL);

				Sleep(20);
				if (msg_size == 0) break;


			}
			std::cout << "Файл отправлен!" << std::endl;
		}

		fin.close();
		

	

}

