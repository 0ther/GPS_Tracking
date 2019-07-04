#pragma once

#include <string>
#include <Windows.h>
#include <cmath>
#include "Movingman.h"


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
	std::string Generate_GGA();
};

struct GGA {
	string Time, Latitude, Longitude, Date;
	bool LaFlag, LoFlag;
};

std::string GPS_EMULATOR::Generate_GGA() {
	std::string escape = {};

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
	escape += ".";
	Valera.Move();

	//����� ������
	

	double lattemp = abs(Valera.Get_Lat());
	double latsec = lattemp;
	escape += std::to_string(int(lattemp)); //�������� 
	
	lattemp -= int(lattemp); //��� �������� ������� ����� �����
	lattemp *= 100; //��� �������� ������� ����� �� 100, ����� ������ ��� �����
	lattemp = int(lattemp);
	escape += std::to_string(lattemp); //�������� ������
	escape.erase(escape.find_last_not_of('0') + 1, std::string::npos); //������ ������ ����
	
	latsec *= 10000;
	latsec = int(latsec) % 100;
	escape += std::to_string(latsec);
	escape.erase(escape.find_last_not_of('0'), std::string::npos); //������ ������ ����

	if (Valera.Get_Lat() > 0) {
		escape += ",N,";
	}
	else escape += ",S,";


	//����� �������
	double lontemp = abs(Valera.Get_Lon());
	double lonsec = lontemp;
	if (lontemp < 100) escape += "0";
	escape += std::to_string(int(lontemp)); //�������� 

	lontemp -= int(lontemp); //��� �������� ������� ����� �����
	lontemp *= 100; //��� �������� ������� ����� �� 100, ����� ������ ��� �����
	lontemp = int(lontemp);
	escape += std::to_string(lontemp); //�������� ������
	escape.erase(escape.find_last_not_of('0') + 1, std::string::npos); //������ ������ ����

	lonsec *= 10000;
	lonsec = int(lonsec) % 100;
	escape += std::to_string(lonsec);
	escape.erase(escape.find_last_not_of('0'), std::string::npos); //������ ������ ����

	if (Valera.Get_Lat() > 0) {
		escape += ",E,";
	}
	else escape += ",W,";

	escape += "0.x,x.x,";
	if (st.wDay < 10) escape += "0";
	escape += std::to_string(st.wDay);
	if (st.wMonth < 10) escape += "0";
	escape += std::to_string(st.wMonth);
	escape += std::to_string(st.wYear);
	escape.erase(escape.size() - 4, 2);

	escape += ",x.x,a,a*hh<CR><LF>";
	return escape;
};

//��������, ����� ������������ ��������� RMC

/*RMC � ������������� ����������� ����� ������ �� GPS � �������

�����, ����, ���������� � ���� ���������� �����������.

$GPRMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxxxx,x.x,a,a*hh<CR><LF>

������ ������� ����������� ��������:

1.	hhmmss.ss � �����;
2.	A � ������ (A/V);
3.	llll.ll,a � ������, N/S;
4.	yyyyy.yy,a � �������, E/W;
5.	x.x � �������� � �����;
6.	x.x � ���� � ��������;
7.	xxxxxx � ����: dd/mm/yy (����/�����/���);
8.	x.x,a � ��������� ��������� � ��������, E/W;
9.	a � ��������� ������: A = ���������� ����������, D = ���������������� �����, N = ������ ������������.*/