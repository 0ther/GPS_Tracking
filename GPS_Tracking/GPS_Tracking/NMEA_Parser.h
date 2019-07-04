#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "NMEA_Emulator.h"


GPS_EMULATOR EMU1 = GPS_EMULATOR();

void JSON_Maker(string A) {
	ofstream fout("temp.json");
	fout << "{\n	\"Time\" : \" \" \n";
	fout.close();

};

