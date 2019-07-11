#pragma once


#include "pch.h"

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#pragma warning(disable: 4996)


class SOCKET_CONNECTION {
private:
	static SOCKET Sock;
	static std::string login;
	std::string password;
	static bool Sending_Flag;

public:
	SOCKET_CONNECTION() {};
	SOCKET_CONNECTION(SOCKET S) { Sock = S; }
	void Connect();
	void Sorting();
	void catch_reg();
	void catch_aut();
	void catch_files();
	static void ClientHandler(bool&);
	void WaitingForABreak();
};


