#pragma once
//���� ����� ���������������� � �������
//������������ � ������� � ����������� �� ����
//�������� � ��������� �������� ���������

#include <iostream>
#include <string>

#include "NMEA_Emulator.h"
#include "Socket.h"

using namespace std;



class CLIENT_INTERFACE {
private:
	bool ExitFlag = 0;


public:
	CLIENT_INTERFACE() {};
	void Register(SOCKET newConnection);
	void Authorise(SOCKET newConnection);

	//bool IsLogin(SOCKET newConnection, int size, char* values); //��������� ������� ������ � ����
	//bool IsValid() { return 1; }; //��������� ������������ ������ � ������


	bool Get_ExitFlag() { return ExitFlag; };
	void User_Console(SOCKET newConnection);
	void Login_Screen(SOCKET newConnection);
};


void CLIENT_INTERFACE::Login_Screen(SOCKET newConnection) {
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
		const char* Type = "2";
		send(Connection, Type, sizeof(Type), NULL);
		Authorise(newConnection);
		break;
	}
	case 2:
		{
		cout << "����������� ������ ������������" << endl;
		const char* Type = "1";
		send(Connection, Type, sizeof(Type), NULL);
		Register(newConnection);
		break;
		}
	case 3:
		ExitFlag = 1;
		break;
	default:
		cout << "����� ���������, ��-������� " << endl;
		break;
	};
};

void CLIENT_INTERFACE::Register(SOCKET newConnection) {
	

	cout << "����� �����, ����� 6 �������� ���������" << endl;
	cout << "�����: ";
	


	char* login = new char(6);
	for (int i = 0; i < 6; i++) cin >> login[i];
		
	send(newConnection, login, 6, NULL); //�������� �����


		char* Smsg1 = new char[1];
		*Smsg1 = '0';
		recv(Connection, Smsg1, sizeof(Smsg1), NULL);
		std::cout << *Smsg1 << std::endl;

		if (*Smsg1 == '1') {
			cout << "������ ����� ������, ����� 6 ����" << endl << "������: ";
			string password;
			cin.ignore();
			getline(cin, password);
			cout << "���������� ������ �� ������..." << endl;
			int msg_size = password.size();
			send(Connection, (char*)&msg_size, sizeof(int), NULL);
			send(Connection, password.c_str(), msg_size, NULL); //�������� ������
			
			char* Smsg2 = new char[1];
			*Smsg2 = '0';
			recv(Connection, Smsg2, sizeof(Smsg2), NULL);
			std::cout << Smsg2 << std::endl;
			
			if (*Smsg2 == '1') {

				cout << "�������! ������ ����������� � ����� �������" << endl;
				ExitFlag = 1;
				Authorise(Connection);
			}
			else {
				std::cout << "���-�� ����� �� ���, ���������� ��� ���" << std::endl;
				Login_Screen(Connection);
			}
		}
		else {
			std::cout << "��������� ������, ����� ��� ��� \n";
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
	cout << "�������� ������ �� �����������..." << endl;
	int msg_size = password.size();
	send(Connection, (char*)&msg_size, sizeof(int), NULL);
	send(Connection, password.c_str(), msg_size, NULL); //�������� ������




	char* Smsg1 = new char[1];
	*Smsg1 = '0';
	recv(Connection, Smsg1, sizeof(Smsg1), NULL);
	std::cout << *Smsg1 << std::endl;

	if (*Smsg1 == '1') {
		std::cout << "������������ ������� �����������" << std::endl;
		User_Console(newConnection);
	}
	else {
		std::cout << "���-�� ����� �� ���, �����" << std::endl;

	}

};

void CLIENT_INTERFACE::User_Console(SOCKET newConnection) {
	cout << "������� ������������, ������ 1.0" << endl;
	cout << "��������� ��������: " << endl;
	cout << "1. ����������� � ��������" << endl;
	cout << "2. ������������� �� �������" << endl;
	cout << "3. �������� �������� ������" << endl;
	cout << "4. ��������� �������� ������" << endl;
	cout << "5. �������������" << endl;
	cout << "������� �����, ���� �������" << endl;
	int input;
	cin >> input;
	switch (input) {
	case 1:
		//������� ���������� � ��������
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:
		Login_Screen(newConnection);
		break;
	default:
		cout << endl << "������������ ����, ����� �� �����" << endl;
		User_Console(newConnection);
		break;
	};
};

