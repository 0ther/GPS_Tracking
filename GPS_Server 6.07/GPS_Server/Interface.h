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
	cout << "Управляшка сервером GPS-трекинга" << endl;
	cout << "Автор: Валерий Кунавин" << endl;
	cout << "Чего желаете?" << endl;
	cout << "1. Авторизоваться в системе" << endl;
	cout << "2. Зарегистрироваться в системе" << endl;
	cout << "3. Выйти из программы" << endl;
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
	cout << "Введите логин и пароль." << endl << "Логин: ";
	getline(cin, login);
	cout << "Пароль: ";
	getline(cin, password);

	//Далее идет процедура поиска строки в файле с логинами и паролями
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
			cout << "Пользователь с таким именем уже существует. Попробуйте ещё." << endl;
			Register();
		}

	}
	else
	{
		cout << "Отлично, теперь придумайте пароль" << endl;
		cout << "Пароль: ";
		string password;
		getline(cin, password);
		//Тут нужно записать логин и пароль в файл

		ofstream out("auth.txt");
		out << "login=" << login << " " << "pass=" << password << "\n";
		out.close();

		cout << "Пользователь зарегистрирован, спасибо!" << endl;
		BeginPanel();
	}


};


void INTERFACE::Register() {
	cout << "Такс, сейчас мы вас зарегистрируем" << endl;
	cout << "Придумайте логин. 6 символов на латинице" << endl;
	
	cout << "Логин: ";
	string login;
	getline(cin, login);
	cout << endl << "Логин записали, теперь посмотрим, есть ли такие " << endl;
	
	
	
	
	
	
	
	
	
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
		std::cout << "Есть такое\n";
	else {
		std::ofstream ofstream("filename");
		ofstream << needString << '\n';
		ofstream.close();
	}
	
	
	
	
	
	
	
	
	
	//Посмотрим, есть ли в файле такой логин
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
			cout << "Пользователь с таким именем уже существует. Попробуйте ещё." << endl;
			Register();
		}

	}
	else
	{
		cout << "Отлично, теперь придумайте пароль, 6 циферок" << endl;
		cout << "Пароль: ";
		string password;
		getline(cin, password);
		//Тут нужно записать логин и пароль в файл

		ofstream out("auth.txt");
		out << "login=" << login << " " << "pass=" << password << "\n";
		out.close();

		cout << "Пользователь зарегистрирован, спасибо!" << endl;
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
  std::cout << "Есть такое\n";
else {
  std::ofstream ofstream("filename" );
  ofstream << needString << '\n';
  ofstream.close();
}
*/