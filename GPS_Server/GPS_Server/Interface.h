#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;



class SIMPLEUSER {
private:
	enum status {USER, ADMIN};


public:


};




enum COMMA {REGISTER, LOGIN, DELETE, GETREPORT};

class INTERFACE {
private:
	bool Exitflag = 0;


public:
	INTERFACE() {};
	void Register();
	void Login();
	bool GetExitFlag() { return Exitflag; };

	void Processing();
	void BeginPanel();
};


void INTERFACE::Processing() {
	
};

void INTERFACE::BeginPanel() {
	cout << "���������� �������� GPS-��������" << endl;
	cout << "�����: ������� �������" << endl;
	cout << "���� �������?" << endl;
	cout << "1. �������������� � �������" << endl;
	cout << "2. ������������������ � �������" << endl;
	cout << "3. ����� �� ���������" << endl;
	int input;
	cin >> input;
	switch (input) {
	case 1:
		Login();
		break;
	case 2:
		Register();
		break;
	case 3:
		Exitflag = 1;
		break;
	default:
		cout << "Enter correct input" << endl;
		break;
	};
};

void INTERFACE::Login() {
	string login, password;
	cout << "������� ����� � ������." << endl << "�����: ";
	getline(cin, login);
	cout << "������: ";
	getline(cin, password);

	//����� ���� ��������� ������ ������ � ����� � �������� � ��������
	fstream fin("auth.txt");
	if (fin)
	{
		const int N = 6;
		string search = "login=";
		string str;
		vector <string> v;
		while (getline(fin, login))
		{
			size_t i = 0;
			while (true)
			{
				i = str.find(search, i);
				if (i != string::npos)
				{
					i += search.size();
					string temp;
					temp.append(str, i, N);
					v.push_back(temp);
					i += N;
				}
				else
					break;
			}
		}
		if (v.size()) {
			cout << "������������ � ����� ������ ��� ����������. ���������� ���." << endl;
			Register();
		}

	}
	else
	{
		cout << "�������, ������ ���������� ������" << endl;
		cout << "������: ";
		string password;
		getline(cin, password);
		//��� ����� �������� ����� � ������ � ����

		ofstream out("auth.txt");
		out << "login=" << login << " " << "pass=" << password << "\n";
		out.close();

		cout << "������������ ���������������, �������!" << endl;
		BeginPanel();
	}


};


void INTERFACE::Register() {
	cout << "����, ������ �� ��� ��������������" << endl;
	cout << "���������� �����. 6 �������� �� ��������" << endl;
	
	cout << "�����: ";
	string login;
	getline(cin, login);
	cout << endl << "����� ��������, ������ ���������, ���� �� ����� " << endl;
	
	
	
	
	
	
	
	
	
	std::string needString, string;
	std::getline(std::cin, needString);
	bool isHave = 0;
	std::ifstream ifstream("filename");
	while (std::getline(ifstream, string))
		if (string == needString) {
			isHave = 1;
			break;
		}
	ifstream.close();
	if (isHave)
		std::cout << "���� �����\n";
	else {
		std::ofstream ofstream("filename");
		ofstream << needString << '\n';
		ofstream.close();
	}
	
	
	
	
	
	
	
	
	
	//���������, ���� �� � ����� ����� �����
	fstream fin("auth.txt");
	if (fin)
	{
		const int N = 6;
		string search = "login=";
		string str;
		vector <string> v;
		while (getline(fin, login))
		{
			size_t i = 0;
			while (true)
			{
				i = str.find(search, i);
				if (i != string::npos)
				{
					i += search.size();
					string temp;
					temp.append(str, i, N);
					v.push_back(temp);
					i += N;
				}
				else
					break;
			}
		}
		if (v.size()) {
			cout << "������������ � ����� ������ ��� ����������. ���������� ���." << endl;
			Register();
		}

	}
	else
	{
		cout << "�������, ������ ���������� ������, 6 �������" << endl;
		cout << "������: ";
		string password;
		getline(cin, password);
		//��� ����� �������� ����� � ������ � ����

		ofstream out("auth.txt");
		out << "login=" << login << " " << "pass=" << password << "\n";
		out.close();

		cout << "������������ ���������������, �������!" << endl;
		BeginPanel();
	}

};




/*
 cout<<"Enter roll number"<<endl;
	cin>>roll;
	cout<<"Enter your name"<<endl;
	cin>>studentName;
	cout<<"Enter password"<<endl;
	cin>>studentPassword;


	filename = roll + ".txt";
	write.open(filename.c_str(), ios::out | ios::binary);

	write.put(ch);
	write.seekp(3, ios::beg);

	write.write((char *)&studentPassword, sizeof(std::string));
	write.close();`



	std::string input;
	std::cin >> input;
	std::ofstream out("output.txt");
	out << input;
	out.close();
	return 0;



	std::string needString, string;
std::getline( std::cin, needString);
bool isHave = 0;
std::ifstream ifstream("filename");
while( std::getline( ifstream, string ) )
  if( string == needString ){
	isHave = 1;
	break;
  }
ifstream.close();
if( isHave )
  std::cout << "���� �����\n";
else {
  std::ofstream ofstream("filename" );
  ofstream << needString << '\n';
  ofstream.close();
}
*/