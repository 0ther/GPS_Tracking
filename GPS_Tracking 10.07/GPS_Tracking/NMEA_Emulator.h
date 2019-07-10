#pragma once

#include <string>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <iostream>
#include "Movingman.h"

using namespace std;

MOVINGMAN Valera = MOVINGMAN(55.21357, 42.23185);

std::string WORD_To_String(unsigned short int A) {
	std::string escape;
	while (A > 0) {
		char buf = A % 10;
		A %= 10;
		escape += buf;
	};
	return escape;
};



class GPS_EMULATOR {
private:

public:
	GPS_EMULATOR() {};
	std::string Generate_RMC(bool&);
};

struct RMC {
	string Time, Latitude, Longitude, Date, LaFlag, LoFlag, Sec1, Sec2;
};

void JSON_Maker(RMC A) {
	ofstream fout("temp.json");
	fout << "{\n	\"Time\" : \"" << A.Time << "\", \n";
	fout << "	\"Latitude\" : \"" << A.Latitude << "\", \n";
	fout << "	\"Latitude Flag\" : \"" << A.LaFlag << "\", \n";
	fout << "	\"Longitude\" : \"" << A.Longitude << "\", \n";
	fout << "	\"Longitude Flag\" : \"" << A.LoFlag << "\", \n";
	fout << "	\"Date\" : \"" << A.Date << "\" \n";
	fout << "}";
	fout.close();

};


std::string GPS_EMULATOR::Generate_RMC(bool& EscapeFlag) {
	
	


		std::string escape = {};

		RMC ToJSON;

		SYSTEMTIME st;
		GetLocalTime(&st);

		escape += "$GPRMC,";
		if (st.wHour < 10) escape += "0";
		escape += std::to_string(st.wHour);
		if (st.wMinute < 10) escape += "0";
		escape += std::to_string(st.wMinute);
		if (st.wSecond < 10) escape += "0";
		escape += std::to_string(st.wSecond);
		escape += ".";
		if (st.wMilliseconds < 10) escape += "0";
		escape += std::to_string(st.wMilliseconds);
		escape.pop_back();

		ToJSON.Time = escape;
		ToJSON.Time.erase(ToJSON.Time.find_first_of("$"), ToJSON.Time.find_last_of(",") + 1);

		escape += ",A,";
		Valera.Move();


		//ѕишем широту


		double lattemp = abs(Valera.Get_Lat());
		double latsec = lattemp;
		escape += std::to_string(int(lattemp)); //«аписали 

		lattemp -= int(lattemp); //“ут выделили дробную часть числа
		lattemp *= 100; //“ут умножили дробную часть на 100, чтобы отсечь два знака
		lattemp = int(lattemp);
		escape += std::to_string(lattemp); //«аписали минуты
		escape.erase(escape.find_last_not_of('0'), std::string::npos); //”брали лишние нули
		escape += ".";

		latsec *= 10000;
		latsec = int(latsec) % 100;
		escape += std::to_string(latsec);
		escape.erase(escape.find_last_not_of('0'), std::string::npos); //”брали лишние нули

		ToJSON.Latitude = escape;
		ToJSON.Latitude.erase(ToJSON.Latitude.find_first_of("$"), ToJSON.Latitude.find_last_of(",") + 1);


		if (Valera.Get_Lat() > 0) {
			escape += ",N,";
			ToJSON.LaFlag = "N";
		}
		else {
			escape += ",S,";
			ToJSON.LaFlag = "S";
		}


		//ѕишем долготу
		double lontemp = abs(Valera.Get_Lon());
		double lonsec = lontemp;
		if (lontemp < 100) escape += "0";
		escape += std::to_string(int(lontemp)); //«аписали 

		lontemp -= int(lontemp); //“ут выделили дробную часть числа
		lontemp *= 100; //“ут умножили дробную часть на 100, чтобы отсечь два знака
		lontemp = int(lontemp);
		escape += std::to_string(lontemp); //«аписали минуты
		escape.erase(escape.find_last_not_of('0'), std::string::npos); //”брали лишние нули
		escape += ".";

		lonsec *= 10000;
		lonsec = int(lonsec) % 100;
		escape += std::to_string(lonsec);
		escape.erase(escape.find_last_not_of('0'), std::string::npos); //”брали лишние нули

		ToJSON.Longitude = escape;
		ToJSON.Longitude.erase(ToJSON.Longitude.find_first_of("$"), ToJSON.Longitude.find_last_of(",") + 1);


		if (Valera.Get_Lat() > 0) {
			escape += ",E,";
			ToJSON.LoFlag = "E";
		}
		else {
			escape += ",W,";
			ToJSON.LoFlag = "W";
		}

		escape += "0.x,x.x,";
		ToJSON.Sec1 = "0.x,x.x,";
		if (st.wDay < 10) escape += "0";
		escape += std::to_string(st.wDay);
		if (st.wMonth < 10) escape += "0";
		escape += std::to_string(st.wMonth);
		escape += std::to_string(st.wYear);
		escape.erase(escape.size() - 4, 2);

		ToJSON.Date = escape;
		ToJSON.Date.erase(ToJSON.Date.find_first_of("$"), ToJSON.Date.find_last_of(",") + 1);


		escape += ",x.x,a,a*hh<CR><LF>";
		ToJSON.Sec2 = ",x.x,a,a*hh<CR><LF>";



		JSON_Maker(ToJSON);
		return escape;

	
};


//ѕосле срабатывани€ функции в папке проекта будет создан JSON с данными и возвращена строка со сгенерированным RMC-сообщением


//Ќаверное, лучше использовать сообщени€ RMC

/*RMC Ц –екомендуемый минимальный набор данных по GPS и √ЋќЌј——

¬рем€, дата, координаты и курс счисл€емые аппаратурой.

$GPRMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxxxx,x.x,a,a*hh<CR><LF>

ѕол€ми данного предложени€ €вл€ютс€:

1.	hhmmss.ss Ц врем€;
2.	A Ц статус (A/V);
3.	llll.ll,a Ц широта, N/S;
4.	yyyyy.yy,a Ц долгота, E/W;
5.	x.x Ц скорость в узлах;
6.	x.x Ц курс в градусах;
7.	xxxxxx Ц дата: dd/mm/yy (день/мес€ц/год);
8.	x.x,a Ц магнитное склонение в градусах, E/W;
9.	a Ц индикатор режима: A = автономна€ обсерваци€, D = дифференциальный режим, N = данные недостоверны.*/