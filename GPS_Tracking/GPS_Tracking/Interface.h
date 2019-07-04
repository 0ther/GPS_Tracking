#pragma once
//���� ����� ���������������� � �������
//������������ � ������� � ����������� �� ����
//�������� � ��������� �������� ���������

#include <iostream>
#include <string>

#include "NMEA_Emulator.h"

using namespace std;

class CLIENT_INTERFACE {
private:
	bool ExitFlag = 0;


public:
	CLIENT_INTERFACE() {};
	void Register();
	void Authorise();

	bool IsLogin() { return 1; }; //��������� ������� ������ � ����
	bool IsValid() { return 1; }; //��������� ������������ ������ � ������


	bool Get_ExitFlag() { return ExitFlag; };
	void User_Console();
	void Login_Screen();
};


void CLIENT_INTERFACE::Login_Screen() {
	cout << "������, ������������! ������ ��������. ���� ������?" << endl;
	cout << "1. �������������� � �������" << endl;
	cout << "2. ������������������ � �������" << endl;
	cout << "3. ����� �� ���������" << endl;
	cout << "����� �������" << endl;
	int input;
	cin >> input;
	switch (input) {
	case 1:
		Authorise();
		break;
	case 2:
		Register();
		break;
	case 3:
		ExitFlag = 1;
		break;
	default:
		cout << "����� ���������, ��-������� " << endl;
		break;
	};
};

void CLIENT_INTERFACE::Register() {
	cout << "����������� ������ ������������" << endl;
	//� ���� ����� ��������� ����������� � ��������
	cout << "����� �����, ����� 6 �������� ���������" << endl;
	cout << "�����: ";
	string login;
	getline(cin, login);
	//� ���� ����� ��������� ���������� � �������, ����� ������ � ������� ������ ������
	if (IsLogin()) {
		cout << "������������ � ����� ������� ��� ����, ������� ���" << endl;
		Register();
	}
	else {
		cout << "������ ����� ������, ����� 6 ����" << endl << "������: ";
		string password;
		getline(cin, password);
		cout << "���������� ������ �� ������..." << endl;
		//��� ������ ������������ �� ������
		cout << "�������! ������ ����������� � ����� �������" << endl;
		Authorise();
	};

};

void CLIENT_INTERFACE::Authorise() {
	cout << "����������� � �������:" << endl;
	cout << "������� �����: ";
	string login;
	getline(cin, login);
	//� ���� ����� ��������� ���������� � �������, ����� ������ � ������� ������ ������
	if (IsLogin()) {
		cout << "������� ������: ";
		string password;
		getline(cin, password);
		//� ���� ����� ��������� ���������� � �������, ����� ��������� ���������� ������ � ������
		if (IsValid()) {
			cout << "����������� ������ �������" << endl;
			User_Console();
		}
	}
};

void CLIENT_INTERFACE::User_Console() {
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
		Login_Screen();
		break;
	default:
		cout << endl << "������������ ����, ����� �� �����" << endl;
		User_Console();
		break;
	};
};


