#pragma once
#include <windows.h>


class MOVINGMAN {
private:
	float Latitude;
	float Longitude;
public:
	MOVINGMAN() {};
	MOVINGMAN(float A, float B) {
		Latitude = A;
		Longitude = B;
	};
	void Move() {

			SYSTEMTIME st;
			GetLocalTime(&st);
			if ((st.wMinute*st.wSecond) % 3 == 0) Latitude += 0.0001;
			else Longitude += 0.0001;

	};
	float Get_Lat() { return Latitude; };
	float Get_Lon() { return Longitude; };
};