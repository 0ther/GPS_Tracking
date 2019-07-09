


#include "pch.h"


#include <iostream>
#include "NMEA_Emulator.h"
#include "Interface.h"
#include "Socket.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	
	CLIENT_INTERFACE INT1 = CLIENT_INTERFACE();
	

	
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";

	
	
	while (!INT1.Get_ExitFlag()) { 
		INT1.Login_Screen(Connection); 
	}




	//char Type;
	//cin >> Type;
	//send(Connection, Type, sizeof(Type), NULL);






	/*

	bool RecFlag = true;



	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendingHandler, &RecFlag, NULL, NULL);
	
	INT1.Login_Screen(Connection);


	GPS_EMULATOR EM1 = GPS_EMULATOR();
	
	for (int i = 50; i > 0; i--) {
		std::cout << "RMC message on " << i << " position" << std::endl;
		std::cout << EM1.Generate_RMC() << std::endl;
		Sleep(1000);
		std::cout << std::endl;
	};

	*/


	system("pause");
	return 0;
}

