// GPS_Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


//Сервер умеет
//Управлять списком пользователей
//Работать с базой данных перемещений
//Визуализировать данные в Google Maps
//Логировать события в системе
//И всё это максимально независимо по ресурсам


#include "pch.h"


#include <iostream>

#include "Servsocket.h"


using namespace std;


int main() {
	
	
	setlocale(LC_ALL, "Russian");
    
	SOCKET_CONNECTION CON1 = SOCKET_CONNECTION();
	
	CON1.Connect();
	


	system("pause");

	return 0;
}

