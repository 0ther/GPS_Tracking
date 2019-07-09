#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Servsocket.h"

using namespace std;
/*




class SERVER_INTERFACE {
private:
	bool Exitflag = 0;


public:
	SERVER_INTERFACE() {};
	bool GetExitFlag() { return Exitflag; };

	void Processing();
	void BeginPanel();
};


void SERVER_INTERFACE::Processing() {
	
};

void SERVER_INTERFACE::BeginPanel() { //Активная часть
	cout << "Управляшка сервером GPS-трекинга" << endl;
	cout << "Автор: Валерий Кунавин" << endl;
	cout << "Чего желаете?" << endl;
	cout << "1. Авторизоваться в системе" << endl;
	cout << "2. Зарегистрироваться в системе" << endl;
	cout << "3. Выйти из программы" << endl;
	int input;
	cin >> input;
	switch (input) {
	case 1:
		Login();
		break;
	case 2:
		Register();
		break;
	case 3:
		Exitflag = 1;
		break;
	default:
		cout << "Enter correct input" << endl;
		break;
	};
};

*/