#include <iostream>
#include<fstream>
#include<chrono>
#include<ctime>
#include<string>
#include<Windows.h>
#include<functional>

using namespace std;

class CarService {
public:
	void CheckIn();
	//void CheckOut();
	void Admin();
	//void Employee();
	void AlreadyCust();
	void NewCust();
	//void RTHP();
	//void NewComplain();
	//void ServiceHistory();
	//void Submit();
	void Issues(string);

};
void CarService::CheckIn() {

	cout << "1. Already Customer\n2. New Customer\n3. Return to Home Page\n";
	cout << "Enter your choice: ";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1: AlreadyCust();
		break;
	case 2: NewCust();
		break;
	//case 3: RTHP();
		//break;
	}
}
void CarService::AlreadyCust() {

}
void CarService::NewCust() {
	ofstream CustomerFile("CustomerDetails.txt",ios::app);
	string name;
	long phNumber;
	string vehicleNo;
	cout << "Enter your name: ";
	cin >> name;
	cout << "Enter your Phone Number: ";
	cin >> phNumber;
	cout << "Enter your Vehicle Number: ";
	cin >> vehicleNo;
	
	CustomerFile << name << " " << phNumber <<" "<< vehicleNo << endl;
	CustomerFile.close();
	Issues(vehicleNo);


}
void CarService::Issues(string vehicle_numb) {
	string issues;
	SYSTEMTIME st;
	GetSystemTime(&st);


	ofstream CarIssues("IssuesDetails.txt");
	cout << "Enter the Issues in your Vehicle:";
	cin.ignore();
	getline(cin, issues);
	CarIssues <<st.wDay << "/"<<st.wMonth<<"/"<<st.wYear<<" "<<st.wHour<<":"<<st.wMinute <<" "<< vehicle_numb << " " << issues << endl;
	CarIssues.close();


}
void CarService::Admin() {
	fstream AdminFile;
	AdminFile.open("Admin.txt",ios::in);
	string userName, password, buffer, passw;
	cout << "Enter Username: ";
	cin >> userName;
	cout << "Enter Password: ";
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	cin.ignore();
	getline(cin, password);
	SetConsoleMode(hStdin, mode);
	hash<string> mystdhash;
	password = mystdhash(password);
	if (!AdminFile.is_open()) {
		AdminFile.open("Admin.txt", ios::out);
		AdminFile << userName << "|" << password << "$";
		cout << userName << password;

	}
	else {

		buffer.erase();
		int i = 0;
		getline(AdminFile, buffer);
		while (buffer[i] != '|')
			userName += buffer[i++];
		i++;
		while (buffer[i] != '$')
			passw += buffer[i++];
		if (passw == password)
		{
			cout << "login Successfull";
		}
		else {
			cout << "login not successfull";
			Admin();
		}
	}
}

		int main()
		{
			CarService cs;
			cs.Admin();
		

		}