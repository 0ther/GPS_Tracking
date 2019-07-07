#pragma once
//юзер умеет регистрироваться в системе
//подключаться к серверу и отключаться от него
//Включать и выключать отправку координат

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

	//bool IsLogin(SOCKET newConnection, int size, char* values); //проверяет наличие логина в базе
	//bool IsValid() { return 1; }; //проверяет соответствие логина и пароля


	bool Get_ExitFlag() { return ExitFlag; };
	void User_Console(SOCKET newConnection);
	void Login_Screen(SOCKET newConnection);
};


void CLIENT_INTERFACE::Login_Screen(SOCKET newConnection) {
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
		const char* Type = "2";
		send(Connection, Type, sizeof(Type), NULL);
		Authorise(newConnection);
		break;
	}
	case 2:
		{
		cout << "Регистрация нового пользователя" << endl;
		const char* Type = "1";
		send(Connection, Type, sizeof(Type), NULL);
		Register(newConnection);
		break;
		}
	case 3:
		ExitFlag = 1;
		break;
	default:
		cout << "Введи корректно, по-братски " << endl;
		break;
	};
};

void CLIENT_INTERFACE::Register(SOCKET newConnection) {
	

	cout << "Введи логин, нужно 6 символов латиницей" << endl;
	cout << "Логин: ";
	


	char* login = new char(6);
	for (int i = 0; i < 6; i++) cin >> login[i];
		
	send(newConnection, login, 6, NULL); //Отослали логин


		char* Smsg1 = new char[1];
		*Smsg1 = '0';
		recv(Connection, Smsg1, sizeof(Smsg1), NULL);
		std::cout << *Smsg1 << std::endl;

		if (*Smsg1 == '1') {
			cout << "Теперь введи пароль, нужно 6 цифр" << endl << "Пароль: ";
			string password;
			cin.ignore();
			getline(cin, password);
			cout << "Записываем данные на сервер..." << endl;
			int msg_size = password.size();
			send(Connection, (char*)&msg_size, sizeof(int), NULL);
			send(Connection, password.c_str(), msg_size, NULL); //Отослали пароль
			
			char* Smsg2 = new char[1];
			*Smsg2 = '0';
			recv(Connection, Smsg2, sizeof(Smsg2), NULL);
			std::cout << Smsg2 << std::endl;
			
			if (*Smsg2 == '1') {

				cout << "Отлично! Теперь авторизуйся с этими данными" << endl;
				ExitFlag = 1;
				Authorise(Connection);
			}
			else {
				std::cout << "Что-то снова не так, попробуйте ещё раз" << std::endl;
				Login_Screen(Connection);
			}
		}
		else {
			std::cout << "Произошла ошибка, давай ещё раз \n";
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
	cout << "Получаем данные об авторизации..." << endl;
	int msg_size = password.size();
	send(Connection, (char*)&msg_size, sizeof(int), NULL);
	send(Connection, password.c_str(), msg_size, NULL); //Отослали пароль




	char* Smsg1 = new char[1];
	*Smsg1 = '0';
	recv(Connection, Smsg1, sizeof(Smsg1), NULL);
	std::cout << *Smsg1 << std::endl;

	if (*Smsg1 == '1') {
		std::cout << "Пользователь успешно авторизован" << std::endl;
		User_Console(newConnection);
	}
	else {
		std::cout << "Что-то пошло не так, сорри" << std::endl;

	}

};

void CLIENT_INTERFACE::User_Console(SOCKET newConnection) {
	cout << "Консоль пользователя, версия 1.0" << endl;
	cout << "Доступные операции: " << endl;
	cout << "1. Соединиться с сервером" << endl;
	cout << "2. Отсоединиться от сервера" << endl;
	cout << "3. Включить передачу данных" << endl;
	cout << "4. Отключить передачу данных" << endl;
	cout << "5. Разлогиниться" << endl;
	cout << "Выбирай мудро, юный падаван" << endl;
	int input;
	cin >> input;
	switch (input) {
	case 1:
		//Функция соединения с сервером
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
		cout << endl << "Некорректный ввод, давай по новой" << endl;
		User_Console(newConnection);
		break;
	};
};

