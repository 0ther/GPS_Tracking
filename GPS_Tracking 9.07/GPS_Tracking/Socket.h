#pragma once

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
#include <iostream>
#include <fstream>
#include <string>
#pragma warning(disable: 4996)

SOCKET Connection;



void SendingHandler(bool &ReceivingFlag) {

	while (ReceivingFlag) { //������: ��� ����������� �������� ����� ������ �������?

		std::string msg1;
		char buff[60];


		std::ifstream fin("temp.json");

		if (!fin.is_open()) // ���� ���� �� ������
			std::cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
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
			std::cout << "���� ���������!" << std::endl;
		}

		fin.close();
		Sleep(930);

	}

}

