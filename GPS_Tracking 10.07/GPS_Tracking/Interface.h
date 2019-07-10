#pragma once
//юзер умеет регистрироваться в системе
//подключаться к серверу и отключаться от него
//Включать и выключать отправку координат

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

	cout << "Привет, пользователь! Клиент работает. Чего хочешь?" << endl;
	cout << "1. Авторизоваться в системе" << endl;
	cout << "2. Зарегистрироваться в системе" << endl;
	cout << "3. Выйти из программы" << endl;
	cout << "Введи команду" << endl;
	int input;
	cin >> input;
	switch (input) {
	case 1:
	{
		WriteIntoLog("Авторизация пользователя...");
		char Type[2] = "2";
		send(Connection, Type, sizeof(Type), NULL);
		Authorise(newConnection);
		break;
	}
	case 2:
		{
		cout << "Регистрация нового пользователя" << endl;
		WriteIntoLog("Инициализация процедуры регистрации...");
		char Type[2] = "1";
		send(Connection, Type, sizeof(Type), NULL);
		Register(newConnection);
		break;
		}
	case 3: //Выход из программы, да
	{
		char Type[2] = "6";
		send(Connection, Type, sizeof(Type), NULL);
		ExitFlag = 1;
		break;
	}
	default:
		cout << "Введи корректно" << endl;
		WriteIntoLog("Некорректый ввод на этапе входа в систему");
		Login_Screen(newConnection);
		break;
	};
};

void CLIENT_INTERFACE::Register(SOCKET newConnection) {
	

	cout << "Введи логин, нужно 6 символов латиницей" << endl;
	cout << "Логин: ";
	


	char login[6];
	for (int i = 0; i < 6; i++) cin >> login[i];
		
	send(newConnection, login, 6, NULL); //Отослали логин


		char* Smsg1 = new char[1];
		*Smsg1 = '0';
		recv(Connection, Smsg1, sizeof(Smsg1), NULL);
		std::cout << *Smsg1 << std::endl;

		if (*Smsg1 == '1') {
			WriteIntoLog("Сервер получил корректный логин");
			cout << "Теперь введи пароль, нужно 6 цифр" << endl << "Пароль: ";
			char password[6];
			
			for (int i = 0; i < 6; i++) cin >> password[i];
			cout << "Записываем данные на сервер..." << endl;
			int msg_size = sizeof(password);
			//send(Connection, (char*)&msg_size, sizeof(int), NULL);
			send(Connection, password, msg_size, NULL); //Отослали пароль
			
			char* Smsg2 = new char[1];
			*Smsg2 = '0';
			recv(Connection, Smsg2, sizeof(Smsg2), NULL);
			std::cout << Smsg2 << std::endl;
			
			if (*Smsg2 == '1') {
				WriteIntoLog("Данные успешно записаны на сервер");
				cout << "Отлично! Теперь авторизуйся с этими данными" << endl;
				ExitFlag = 1;
				Login_Screen(Connection);
			}
			else {
				WriteIntoLog("Ошибка: данные не были записаны на сервер");
				std::cout << "Что-то снова не так, попробуйте ещё раз" << std::endl;
				Login_Screen(Connection);
			}
		}
		else {
			//std::cout << "Произошла ошибка, давай ещё раз \n";
			WriteIntoLog("Ошибка: сервер не получил корректный логин");
			Login_Screen(Connection);
		}


};

void CLIENT_INTERFACE::Authorise(SOCKET newConnection) {
	cout << "Авторизация в системе:" << endl;
	cout << "Введите логин: ";


	char* login = new char(6);
	for (int i = 0; i < 6; i++) cin >> login[i];

	send(newConnection, login, 6, NULL); //Отослали логин





	cout << "Теперь введите пароль" << endl << "Пароль: ";
	string password;
	cin.ignore();
	getline(cin, password);
	WriteIntoLog("Сервер сверяет введенные данные...");
	//cout << "Получаем данные об авторизации..." << endl;
	int msg_size = password.size();
	send(Connection, (char*)&msg_size, sizeof(int), NULL);
	send(Connection, password.c_str(), msg_size, NULL); //Отослали пароль




	char* Smsg1 = new char[1];
	*Smsg1 = '0';
	recv(Connection, Smsg1, sizeof(Smsg1), NULL);
	std::cout << *Smsg1 << std::endl;

	if (*Smsg1 == '1') {
		WriteIntoLog("Пользователь был успешно авторизован");
		//std::cout << "Пользователь успешно авторизован" << std::endl;
		User_Console(newConnection);
	}
	else {
		WriteIntoLog("Ошибка: не была распознана комбинация логина и пароля");
		std::cout << "Что-то пошло не так, сорри" << std::endl;
		Sleep(1000);
		Login_Screen(Connection);
	}

};



void CLIENT_INTERFACE::StartSending(SOCKET newConnection) {
	SendFlag = 1;
	WriteIntoLog("Начало отправки сообщений...");
	//Вот тут нужно направить сигнал серверу, чтобы он переключился в режим получения файлов
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
	
	cout << "Консоль пользователя, версия 1.0" << endl;
	cout << "Доступные операции: " << endl;
	cout << "1. Включить передачу данных" << endl;
	cout << "2. Отключить передачу данных" << endl;
	cout << "3. Разлогиниться" << endl;
	cout << "Выбирай мудро, юный падаван" << endl;
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
		cout << endl << "Некорректный ввод, давай по новой" << endl;
		WriteIntoLog("Некорректный ввод на этапе работы с клиентом");
		User_Console(newConnection);
		break;
	}
	};
};

