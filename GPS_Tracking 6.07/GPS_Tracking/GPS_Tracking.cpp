


#include "pch.h"


#include <iostream>
#include "NMEA_Emulator.h"
#include "Interface.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	
	CLIENT_INTERFACE INT1 = CLIENT_INTERFACE();
	INT1.Login_Screen();


	GPS_EMULATOR EM1 = GPS_EMULATOR();
	
	for (int i = 50; i > 0; i--) {
		std::cout << "RMC message on " << i << " position" << std::endl;
		std::cout << EM1.Generate_RMC() << std::endl;
		Sleep(1000);
		std::cout << std::endl;
	};




	system("pause");
	return 0;
}

