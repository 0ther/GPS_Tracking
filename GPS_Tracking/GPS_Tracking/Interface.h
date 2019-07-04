#pragma once
//юзер умеет регистрироваться в системе
//подключаться к серверу и отключаться от него
//Включать и выключать отправку координат

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

	bool IsLogin() { return 1; }; //проверяет наличие логина в базе
	bool IsValid() { return 1; }; //проверяет соответствие логина и пароля


	bool Get_ExitFlag() { return ExitFlag; };
	void User_Console();
	void Login_Screen();
};


void CLIENT_INTERFACE::Login_Screen() {
	cout << "Привет, пользователь! Клиент работает. Чего хочешь?" << endl;
	cout << "1. Авторизоваться в системе" << endl;
	cout << "2. Зарегистрироваться в системе" << endl;
	cout << "3. Выйти из программы" << endl;
	cout << "Введи команду" << endl;
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
		cout << "Введи корректно, по-братски " << endl;
		break;
	};
};

void CLIENT_INTERFACE::Register() {
	cout << "Регистрация нового пользователя" << endl;
	//В этом месте программа соединяется с сервером
	cout << "Введи логин, нужно 6 символов латиницей" << endl;
	cout << "Логин: ";
	string login;
	getline(cin, login);
	//В этом месте программа обращается к серверу, чтобы узнать о наличии такого логина
	if (IsLogin()) {
		cout << "Пользователь с таким логином уже есть, подумай ещё" << endl;
		Register();
	}
	else {
		cout << "Теперь введи пароль, нужно 6 цифр" << endl << "Пароль: ";
		string password;
		getline(cin, password);
		cout << "Записываем данные на сервер..." << endl;
		//Тут данные записываются на сервер
		cout << "Отлично! Теперь авторизуйся с этими данными" << endl;
		Authorise();
	};

};

void CLIENT_INTERFACE::Authorise() {
	cout << "Авторизация в системе:" << endl;
	cout << "Введите логин: ";
	string login;
	getline(cin, login);
	//В этом месте программа обращается к серверу, чтобы узнать о наличии такого логина
	if (IsLogin()) {
		cout << "Введите пароль: ";
		string password;
		getline(cin, password);
		//В этом месте программа обращается к серверу, чтобы проверить комбинацию логина и пароля
		if (IsValid()) {
			cout << "Авторизация прошла успешно" << endl;
			User_Console();
		}
	}
};

void CLIENT_INTERFACE::User_Console() {
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
		Login_Screen();
		break;
	default:
		cout << endl << "Некорректный ввод, давай по новой" << endl;
		User_Console();
		break;
	};
};


