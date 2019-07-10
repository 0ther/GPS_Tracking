#pragma once
//���� ����� ���������������� � �������
//������������ � ������� � ����������� �� ����
//�������� � ��������� �������� ���������

#include <iostream>
#include <string>
#include <conio.h>

#include "NMEA_Emulator.h"
#include "Socket.h"
#include "logwork.h"

using namespace std;



class CLIENT_INTERFACE {
private:
	bool ExitFlag = 0;
	bool SendFlag = 0;

public:
	CLIENT_INTERFACE() {};
	void Register(SOCKET newConnection);
	void Authorise(SOCKET newConnection);

	void StartSending(SOCKET newConnection);
	void StopSending(SOCKET newConnection);

	bool Get_ExitFlag() { return ExitFlag; };
	void User_Console(SOCKET newConnection);
	void Login_Screen(SOCKET newConnection);
};


void CLIENT_INTERFACE::Login_Screen(SOCKET newConnection) {
	system("cls");

	cout << "������, ������������! ������ ��������. ���� ������?" << endl;
	cout << "1. �������������� � �������" << endl;
	cout << "2. ������������������ � �������" << endl;
	cout << "3. ����� �� ���������" << endl;
	cout << "����� �������" << endl;
	int input;
	cin >> input;
	switch (input) {
	case 1:
	{
		WriteIntoLog("����������� ������������...");
		char Type[2] = "2";
		send(Connection, Type, sizeof(Type), NULL);
		Authorise(newConnection);
		break;
	}
	case 2:
		{
		cout << "����������� ������ ������������" << endl;
		WriteIntoLog("������������� ��������� �����������...");
		char Type[2] = "1";
		send(Connection, Type, sizeof(Type), NULL);
		Register(newConnection);
		break;
		}
	case 3: //����� �� ���������, ��
	{
		char Type[2] = "6";
		send(Connection, Type, sizeof(Type), NULL);
		ExitFlag = 1;
		break;
	}
	default:
		cout << "����� ���������" << endl;
		WriteIntoLog("����������� ���� �� ����� ����� � �������");
		Login_Screen(newConnection);
		break;
	};
};

void CLIENT_INTERFACE::Register(SOCKET newConnection) {
	

	cout << "����� �����, ����� 6 �������� ���������" << endl;
	cout << "�����: ";
	


	char login[6];
	for (int i = 0; i < 6; i++) cin >> login[i];
		
	send(newConnection, login, 6, NULL); //�������� �����


		char* Smsg1 = new char[1];
		*Smsg1 = '0';
		recv(Connection, Smsg1, sizeof(Smsg1), NULL);
		std::cout << *Smsg1 << std::endl;

		if (*Smsg1 == '1') {
			WriteIntoLog("������ ������� ���������� �����");
			cout << "������ ����� ������, ����� 6 ����" << endl << "������: ";
			char password[6];
			
			for (int i = 0; i < 6; i++) cin >> password[i];
			cout << "���������� ������ �� ������..." << endl;
			int msg_size = sizeof(password);
			//send(Connection, (char*)&msg_size, sizeof(int), NULL);
			send(Connection, password, msg_size, NULL); //�������� ������
			
			char* Smsg2 = new char[1];
			*Smsg2 = '0';
			recv(Connection, Smsg2, sizeof(Smsg2), NULL);
			std::cout << Smsg2 << std::endl;
			
			if (*Smsg2 == '1') {
				WriteIntoLog("������ ������� �������� �� ������");
				cout << "�������! ������ ����������� � ����� �������" << endl;
				ExitFlag = 1;
				Login_Screen(Connection);
			}
			else {
				WriteIntoLog("������: ������ �� ���� �������� �� ������");
				std::cout << "���-�� ����� �� ���, ���������� ��� ���" << std::endl;
				Login_Screen(Connection);
			}
		}
		else {
			//std::cout << "��������� ������, ����� ��� ��� \n";
			WriteIntoLog("������: ������ �� ������� ���������� �����");
			Login_Screen(Connection);
		}


};

void CLIENT_INTERFACE::Authorise(SOCKET newConnection) {
	cout << "����������� � �������:" << endl;
	cout << "������� �����: ";


	char* login = new char(6);
	for (int i = 0; i < 6; i++) cin >> login[i];

	send(newConnection, login, 6, NULL); //�������� �����





	cout << "������ ������� ������" << endl << "������: ";
	string password;
	cin.ignore();
	getline(cin, password);
	WriteIntoLog("������ ������� ��������� ������...");
	//cout << "�������� ������ �� �����������..." << endl;
	int msg_size = password.size();
	send(Connection, (char*)&msg_size, sizeof(int), NULL);
	send(Connection, password.c_str(), msg_size, NULL); //�������� ������




	char* Smsg1 = new char[1];
	*Smsg1 = '0';
	recv(Connection, Smsg1, sizeof(Smsg1), NULL);
	std::cout << *Smsg1 << std::endl;

	if (*Smsg1 == '1') {
		WriteIntoLog("������������ ��� ������� �����������");
		//std::cout << "������������ ������� �����������" << std::endl;
		User_Console(newConnection);
	}
	else {
		WriteIntoLog("������: �� ���� ���������� ���������� ������ � ������");
		std::cout << "���-�� ����� �� ���, �����" << std::endl;
		Sleep(1000);
		Login_Screen(Connection);
	}

};



void CLIENT_INTERFACE::StartSending(SOCKET newConnection) {
	SendFlag = 1;
	WriteIntoLog("������ �������� ���������...");
	//��� ��� ����� ��������� ������ �������, ����� �� ������������ � ����� ��������� ������
	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendingHandler, (LPVOID)&SendFlag, NULL, NULL);
	while (SendFlag) {
		SendingHandler();
		//User_Console(newConnection);
	}
	
};




void CLIENT_INTERFACE::StopSending(SOCKET newConnection) {
	SendFlag = 0;
	User_Console(newConnection);
};










void CLIENT_INTERFACE::User_Console(SOCKET newConnection) {
	system("cls");
	
	cout << "������� ������������, ������ 1.0" << endl;
	cout << "��������� ��������: " << endl;
	cout << "1. �������� �������� ������" << endl;
	cout << "2. ��������� �������� ������" << endl;
	cout << "3. �������������" << endl;
	cout << "������� �����, ���� �������" << endl;
	int input;
	cin >> input;
	switch (input) {
	case 1:
	{
		char Type[] = "3";
		send(Connection, Type, sizeof(Type), NULL);
		StartSending(newConnection);
		break;
	}
	case 2:
	{
		char Type[] = "4";
		send(Connection, Type, sizeof(Type), NULL);
		StopSending(newConnection);
		break;
	}
	case 3:
	{
		char Type[] = "9";
		send(Connection, Type, sizeof(Type), NULL);
		Login_Screen(newConnection);
		break;
	}
	default:
	{
		cout << endl << "������������ ����, ����� �� �����" << endl;
		WriteIntoLog("������������ ���� �� ����� ������ � ��������");
		User_Console(newConnection);
		break;
	}
	};
};

