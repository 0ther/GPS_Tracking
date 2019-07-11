#pragma once
#include "pch.h"
#include "Interface.h"
//#include "logwork.h"


SOCKET CLIENT_INTERFACE::Sock = NULL;


void CLIENT_INTERFACE::SetSock(SOCKET Connection) {
  Sock = Connection;
};


void CLIENT_INTERFACE::SendingHandler(bool& EscapeFlag) {
  while(EscapeFlag) {
    Sleep(790);
    std::string msg1;
    char buff[60];
    std::ifstream fin("temp.json");

    if (!fin.is_open()) { // ���� ���� �� ������
      //std::cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
      WriteIntoLog("������ �������� ����� � ������������");
    }
    else {
      while (true) {

        fin.getline(buff, 60);
        msg1 = buff;
        int msg_size = msg1.size();
        //send(Connection, (char*)&msg_size, sizeof(int), NULL);
        //std::cout << msg1 << std::endl;
        send(Sock, msg1.c_str(), msg_size, NULL);

        Sleep(30);
        if (msg_size == 0) break;
      };
      //std::cout << "���� ���������!" << std::endl;
    };
    fin.close();
  };
}


void CLIENT_INTERFACE::Login_Screen() {
  system("cls");
  std::cout << "������, ������������! ������ ��������. ���� ������?" << std::endl;
  std::cout << "1. �������������� � �������" << std::endl;
  std::cout << "2. ������������������ � �������" << std::endl;
  std::cout << "3. ����� �� ���������" << std::endl;
  std::cout << "����� �������" << std::endl;
  int input;
  std::cin >> input;
  switch (input) {
  case 1:
  {
    WriteIntoLog("����������� ������������...");
    char Type[2] = "2";
    send(Sock, Type, sizeof(Type), NULL);
    Authorise();
    break;
  }
  case 2:
  {
    std::cout << "����������� ������ ������������" << std::endl;
    WriteIntoLog("������������� ��������� �����������...");
    char Type[2] = "1";
    send(Sock, Type, sizeof(Type), NULL);
    Register();
    break;
  }
  case 3: //����� �� ���������, ��
  {
    char Type[2] = "6";
    send(Sock, Type, sizeof(Type), NULL);
    ExitFlag = 1;
    break;
  }
  default:
    std::cout << "����� ���������" << std::endl;
    WriteIntoLog("����������� ���� �� ����� ����� � �������");
    Login_Screen();
    break;
  };
};


void CLIENT_INTERFACE::Register() {
  std::cout << "����� �����, ����� 6 �������� ���������" << std::endl;
  std::cout << "�����: ";

  char login[6];
  for (int i = 0; i < 6; i++) std::cin >> login[i];

  send(Sock, login, 6, NULL); //�������� �����

  char* Smsg1 = new char[1];
  *Smsg1 = '0';
  recv(Sock, Smsg1, sizeof(Smsg1), NULL);
  //std::cout << *Smsg1 << std::endl;

  if (*Smsg1 == '1') {
    WriteIntoLog("������ ������� ���������� �����");
    std::cout << "������ ����� ������, ����� 6 ����" << std::endl << "������: ";
    char password[6];
    for (int i = 0; i < 6; i++) std::cin >> password[i];
    std::cout << "���������� ������ �� ������..." << std::endl;
    int msg_size = sizeof(password);
    //send(Connection, (char*)&msg_size, sizeof(int), NULL);
    send(Sock, password, msg_size, NULL); //�������� ������

    char* Smsg2 = new char[1];
    *Smsg2 = '0';
    recv(Sock, Smsg2, sizeof(Smsg2), NULL);
    std::cout << Smsg2 << std::endl;

    if (*Smsg2 == '1') {
      WriteIntoLog("������ ������� �������� �� ������");
      std::cout << "�������! ������ ����������� � ����� �������" << std::endl;
      ExitFlag = 1;
      Login_Screen();
    }
    else {
      WriteIntoLog("������: ������ �� ���� �������� �� ������");
      std::cout << "���-�� ����� �� ���, ���������� ��� ���" << std::endl;
      Login_Screen();
    }
  }
  else {
    //std::cout << "��������� ������, ����� ��� ��� \n";
    WriteIntoLog("������: ������ �� ������� ���������� �����");
    Login_Screen();
  }
};


void CLIENT_INTERFACE::Authorise() {
  std::cout << "����������� � �������:" << std::endl;
  std::cout << "������� �����: ";
  char* login = new char(6);
  for (int i = 0; i < 6; i++) std::cin >> login[i];

  send(Sock, login, 6, NULL); //�������� �����

  std::cout << "������ ������� ������" << std::endl << "������: ";
  std::string password;
  std::cin.ignore();
  getline(std::cin, password);
  WriteIntoLog("������ ������� ��������� ������...");
  //cout << "�������� ������ �� �����������..." << endl;
  int msg_size = password.size();
  send(Sock, (char*)&msg_size, sizeof(int), NULL);
  send(Sock, password.c_str(), msg_size, NULL); //�������� ������

  char* Smsg1 = new char[1];
  *Smsg1 = '0';
  recv(Sock, Smsg1, sizeof(Smsg1), NULL);
  std::cout << *Smsg1 << std::endl;

  if (*Smsg1 == '1') {
    WriteIntoLog("������������ ��� ������� �����������");
    //std::cout << "������������ ������� �����������" << std::endl;
    User_Console();
  }
  else {
    WriteIntoLog("������: �� ���� ���������� ���������� ������ � ������");
    std::cout << "���-�� ����� �� ���, �����" << std::endl;
    Sleep(1000);
	Login_Screen();
  }
};


void CLIENT_INTERFACE::StartSending() {
  SendFlag = 1;
  WriteIntoLog("������ �������� ���������...");
  //��� ��� ����� ��������� ������ �������, ����� �� ������������ � ����� ��������� ������
  CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendingHandler, &SendFlag, NULL, NULL);
  User_Console();
};


void CLIENT_INTERFACE::StopSending() {
  SendFlag = 0;
  User_Console();
};


void CLIENT_INTERFACE::User_Console() {
  system("cls");
  std::cout << "������� ������������, ������ 1.0" << std::endl;
  std::cout << "��������� ��������: " << std::endl;
  std::cout << "1. �������� �������� ������" << std::endl;
  std::cout << "2. ��������� �������� ������" << std::endl;
  std::cout << "3. �������������" << std::endl;
  std::cout << "������� �����, ���� �������" << std::endl;
  int input;
  std::cin >> input;
  switch (input) {
  case 1:
  {
    char Type[] = "3";
    send(Sock, Type, sizeof(Type), NULL);
	StartSending();
	break;
  }
  case 2:
  {
    char Type[] = "4";
    send(Sock, Type, sizeof(Type), NULL);
    StopSending();
    break;
  }
  case 3:
  {
    char Type[] = "9";
    send(Sock, Type, sizeof(Type), NULL);
    Login_Screen();
    break;
  }
  default:
  {
    std::cout << std::endl << "������������ ����, ����� �� �����" << std::endl;
    WriteIntoLog("������������ ���� �� ����� ������ � ��������");
    User_Console();
    break;
  }
  };
};


