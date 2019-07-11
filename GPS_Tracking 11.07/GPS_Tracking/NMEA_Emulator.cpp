#pragma once
#include "pch.h"
#include "NMEA_Emulator.h"


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


bool GPS_EMULATOR::Gen_Flag = 0;


void JSON_Maker(RMC A) {
  std::ofstream fout("temp.json");
  fout << "{\n	\"Time\" : \"" << A.Time << "\", \n";
  fout << "	\"Latitude\" : \"" << A.Latitude << "\", \n";
  fout << "	\"Latitude Flag\" : \"" << A.LaFlag << "\", \n";
  fout << "	\"Longitude\" : \"" << A.Longitude << "\", \n";
  fout << "	\"Longitude Flag\" : \"" << A.LoFlag << "\", \n";
  fout << "	\"Date\" : \"" << A.Date << "\" \n";
  fout << "}";
  fout.close();
};


void GPS_EMULATOR::StartGenerating() {
  Gen_Flag = 1;
  CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Generate_RMC, &Gen_Flag, NULL, NULL); //��� ��� �������� ����� ��������� ��������� � �� �������������� � JSON
};


void GPS_EMULATOR::StopGenerating() {
  Gen_Flag = 0;
};


void GPS_EMULATOR::Generate_RMC(bool& EscapeFlag) { //��� ��� ����� �������� ��������
  while (EscapeFlag) {
    RMC ToJSON;

    SYSTEMTIME st;
    GetLocalTime(&st);

    std::string escape = "$GPRMC,";
    ToJSON.Preamble = escape;
    if (st.wHour < 10) escape += "0";
    escape += std::to_string(st.wHour);
    if (st.wMinute < 10) escape += "0";
    escape += std::to_string(st.wMinute);
    if (st.wSecond < 10) escape += "0";
    escape += std::to_string(st.wSecond);
    escape += ".";
    if (st.wMilliseconds < 100 && st.wMilliseconds >= 10) escape += "0";
    if (st.wMilliseconds < 10 && st.wMilliseconds >= 0) escape += "00";
    if (st.wMilliseconds == 0) escape += "000";
    escape += std::to_string(st.wMilliseconds);
    escape.pop_back();

    ToJSON.Time = escape;
    ToJSON.Time.erase(ToJSON.Time.find_first_of("$"), ToJSON.Time.find_last_of(",") + 1);

    escape += ",A,";
    Valera.Move();

    //����� ������
    double lattemp = abs(Valera.Get_Lat());
    double latsec = lattemp;
    escape += std::to_string(int(lattemp)); //��������

    lattemp -= int(lattemp); //��� �������� ������� ����� �����
    lattemp *= 100; //��� �������� ������� ����� �� 100, ����� ������ ��� �����
    lattemp = int(lattemp);
    escape += std::to_string(lattemp); //�������� ������
    escape.erase(escape.find_last_not_of('0'), std::string::npos); //������ ������ ����
    escape += ".";

    latsec *= 10000;
    latsec = int(latsec) % 100;
    escape += std::to_string(latsec);
    escape.erase(escape.find_last_not_of('0'), std::string::npos); //������ ������ ����

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

    //����� �������
    double lontemp = abs(Valera.Get_Lon());
    double lonsec = lontemp;
    if (lontemp < 100) escape += "0";
    escape += std::to_string(int(lontemp)); //��������

    lontemp -= int(lontemp); //��� �������� ������� ����� �����
    lontemp *= 100; //��� �������� ������� ����� �� 100, ����� ������ ��� �����
    lontemp = int(lontemp);
    escape += std::to_string(lontemp); //�������� ������
    escape.erase(escape.find_last_not_of('0'), std::string::npos); //������ ������ ����
    escape += ".";

    lonsec *= 10000;
    lonsec = int(lonsec) % 100;
    escape += std::to_string(lonsec);
    escape.erase(escape.find_last_not_of('0'), std::string::npos); //������ ������ ����

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
    Sleep(1000);
  }
};