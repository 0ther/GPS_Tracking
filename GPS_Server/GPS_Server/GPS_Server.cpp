// GPS_Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


//Сервер умеет
//Управлять списком пользователей
//Работать с базой данных перемещений
//Визуализировать данные в Google Maps
//Логировать события в системе
//И всё это максимально независимо по ресурсам

//То есть, что нужно сделать
//Базу данных с пользователями и их перемещениями - ниет


#include "pch.h"


#include <iostream>


#include "Interface.h"

int main()
{
	setlocale(LC_ALL, "Russian");
    std::cout << "Hello World!\n"; 
	INTERFACE INT1 = INTERFACE();
	while (!INT1.GetExitFlag()) INT1.BeginPanel();


	system("pause");

	return 0;
}

