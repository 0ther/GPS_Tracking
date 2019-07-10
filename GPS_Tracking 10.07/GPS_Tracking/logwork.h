#pragma once

std::ofstream logfile("client.log");


void WriteIntoLog(std::string Message) {
	logfile.open("client.log", std::ios::app);
	logfile << Message << std::endl;
	logfile.close();
}

void ClearLog() {
	logfile.clear();
}