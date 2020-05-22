#include <iostream>
#include<fstream>
#include<chrono>
#include<ctime>
#include<string>
#include<Windows.h>


using namespace std;

class CarService {
public:
	string buffer;
	void HomePage();
	void CheckIn();
	void CheckOut();
	void Admin();
	void Employee();
	void AlreadyCust();
	void NewCust();
	string IssuesSearch(string);
	void IssuesDelete(string);
	void Pack();
	void Unpack();
	void StatusUpdate(string, int);
	void NewComplain();
	void ServiceHistory();
	void Submit();
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
	case 3: HomePage();
		break;
	}
}


void CarService::HomePage() {
	int choice;
	cout << "1. Check In\n2. Check Out\n3. Admin\n4. Employee\n5. Exit" << endl;
	cout << "Enter your choice" << endl;
	cin >> choice;
	switch (choice) {
	case 1:CheckIn();
		break;
	case 2:CheckOut();
		break;
	case 3:Admin();
		break;
	case 4:Employee();
		break;
	case 5: exit;
	}

}

void CarService::CheckOut() {

}

void CarService::Admin() {
	fstream AdminFile;
	AdminFile.open("Admin.txt", ios::in);
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
		AdminFile << userName << "|" << password << "|" << "1" << "$";

	}
	else {
		buffer.erase();
		int i = 0;
		getline(AdminFile, buffer);
		while (buffer[i] != '|')
			userName += buffer[i++];
		i++;
		while (buffer[i] != '|')
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



void CarService::Employee() {
	int pos = 0;
	string date, time, VehicleNo, Issues, status1, key;
	fstream AdminFile;
	AdminFile.open("Admin.txt", ios::in);
	string userName, usern_file, password, buffer, passw_file, status;
	usern_file = "null";
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
	buffer.erase();
	int i = 0;
	getline(AdminFile, buffer);

	while (usern_file != userName)
	{
		usern_file.erase();
		while (buffer[i] != '|')
			usern_file += buffer[i++];
		i++;
		cout << usern_file;
		passw_file.erase();
		while (buffer[i] != '|')
			passw_file += buffer[i++];
		i++;
		status1.erase();
		while (buffer[i] != '$')
			status1 += buffer[i++];
		if (AdminFile.eof()) {
			break;
		}
	}
	if (passw_file == password)
	{
		int i = 0;
		fstream IssuesDetails;
		cout << "login Successfull\n";
		IssuesDetails.open("IssuesDetails.txt", ios::in||ios::out);
		while (!IssuesDetails.eof())
		{
		
			buffer.erase();
			pos = IssuesDetails.tellg();
			getline(IssuesDetails, buffer);
			
			
			i = 0;
			date.erase();
			if (IssuesDetails.eof())
				break;

			while (buffer[i] != '|')
				date += buffer[i++];
			time.erase();
			i++;
			while (buffer[i] != '|')
				time += buffer[i++];
			VehicleNo.erase();
			i++;
			while (buffer[i] != '|')
				VehicleNo += buffer[i++];
			Issues.erase();
			i++;
			while (buffer[i] != '|')
				Issues += buffer[i++];
			status.erase();
			i++;
			while (buffer[i] != '$')
				status += buffer[i++];
			if (status == "0")
			{
				cout << date << "|" << time << "|" << VehicleNo << "|" << Issues << "$"<<endl;
			}
		}

	}
	else
	{
		cout << "login not successfull  ";
		Employee();
	}
	cout << "Enter the vehicle number to select the vehicle:";
	cin >> key;
	int pos1;
	ifstream IssuesDetails;
	IssuesDetails.open("IssuesDetails.txt", ios::in);
	while (!IssuesDetails.eof())
	{
		buffer.erase();
		pos1 = IssuesDetails.tellg();
		getline(IssuesDetails, buffer);
		int j = 0;
		date.erase();
		if (IssuesDetails.eof())
			break;

		while (buffer[j] != '|')
			date += buffer[j++];
		time.erase();
		j++;
		while (buffer[j] != '|')
			time += buffer[j++];
		VehicleNo.erase();
		j++;
		while (buffer[j] != '|')
			VehicleNo += buffer[j++];
		Issues.erase();
		j++;
		while (buffer[j] != '|')
			Issues += buffer[j++];
		status.erase();
		j++;
		while (buffer[j] != '$')
			status += buffer[j++];
	}


}

void CarService::AlreadyCust() {
	int flag = 0, pos = 0, choice;
	string VehicleNo, name, key, confirm;
	string PhoneNumber;
	cout << "Enter your Vehicle Number: " << endl;
	cin >> key;
	ifstream CustomerDetails;
	CustomerDetails.open("CustomerDetails.txt", ios::in);
	while (!CustomerDetails.eof())
	{
		buffer.erase();
		pos = CustomerDetails.tellg();
		getline(CustomerDetails, buffer);
		int i = 0;
		name.erase();
		while (buffer[i] != '|')
			name += buffer[i++];

		PhoneNumber.erase();
		i++;
		while (buffer[i] != '|')
			PhoneNumber += buffer[i++];
		VehicleNo.erase();
		i++;
		while (buffer[i] != '$')
			VehicleNo += buffer[i++];


		if (VehicleNo == key)
		{
			cout << "\nFound the Vehicle Number.\n" << buffer;
			flag = 1;
			cout << "Confirm the vehicle details.(Y/N)" << endl;
			cin >> confirm;
			if (confirm == "y" || "Y") {
				cout << "1. New Complain\n2. View Service History\n3. Previous Page\n";
				cout << "Enter your choice: ";
				cin >> choice;
				switch (choice) {
				case 1: Issues(VehicleNo);
					break;
				case 2: ServiceHistory();
					break;
				case 3: AlreadyCust();
					break;

				}

			}
			else {
				AlreadyCust();
			}

		}
		else {
			cout << "\nVehicle NOT FOUND";
			CheckIn();
		}

	}

}
void CarService::NewCust() {
	string confirm;
	ofstream CustomerFile("CustomerDetails.txt", ios::app);
	string name;
	string phNumber;
	string vehicleNo;
	cout << "Enter your name: ";
	cin >> name;
	cout << "Enter your Phone Number: ";
	cin >> phNumber;
	cout << "Enter your Vehicle Number: ";
	cin >> vehicleNo;
	cout << name << " " << phNumber << " " << vehicleNo << endl;
	cout << "Do you want to Confirm?(Y/N)";
	cin >> confirm;

	if (confirm == "y" || "Y") {

		CustomerFile << name << "|" << phNumber << "|" << vehicleNo << "$" << endl;

		CustomerFile.close();

		Issues(vehicleNo);
	}
	else {
		NewCust();
	}
}
void CarService::ServiceHistory() {

}
void CarService::Issues(string vehicle_numb) {
	string status = "0";
	string issues, wax_wash, confirm;
	SYSTEMTIME st;
	GetSystemTime(&st);


	ofstream CarIssues("IssuesDetails.txt", ios::app);
	cout << "Enter the Issues in your Vehicle:";
	cin.ignore();
	getline(cin, issues);
	cout << "Do you want to add wax and wash to your service?(Y/N)" << endl;
	cin >> wax_wash;
	if (wax_wash == "y" || "Y") {
		issues += " wax and wash";
	}
	cout << issues << endl;
	cout << "Confirm complains entered?(Y/N)";
	cin >> confirm;
	if (confirm == "y" || "Y") {

		CarIssues << st.wDay << "/" << st.wMonth << "/" << st.wYear << "|" << st.wHour << ":" << st.wMinute << "|" << vehicle_numb << "|" << issues << "|" << status << "$" << endl;

	CarIssues.close();
	}
	else {
		Issues(vehicle_numb);
	}

}

string CarService::IssuesSearch(string key) {
	int flag = 0, pos = 0, i, choice;
	string date, time, VehicleNo, Issues, status;
	string PhoneNumber;
	ifstream IssuesDetails;
	IssuesDetails.open("IssuesDetails.txt", ios::in);
	while (!IssuesDetails.eof())
	{
		buffer.erase();
		pos = IssuesDetails.tellg();
		getline(IssuesDetails, buffer);
		i = 0;
		date.erase();
		if (IssuesDetails.eof())
			break;

		while (buffer[i] != '|')
			date += buffer[i++];
		time.erase();
		i++;
		while (buffer[i] != '|')
			time += buffer[i++];
		VehicleNo.erase();
		i++;
		while (buffer[i] != '|')
			VehicleNo += buffer[i++];
		Issues.erase();
		i++;
		while (buffer[i] != '|')
			Issues += buffer[i++];
		status.erase();
		i++;
		while (buffer[i] != '$')
			status += buffer[i++];

		if (VehicleNo == key)
			IssuesDetails.close();
			return buffer;
	}
	IssuesDetails.close();
	return "NULL";
}

void CarService::IssuesDelete(string key) {
	string buff;
	int pos = 0,i=0;
	string date, time, VehicleNo, Issues, status;
	fstream temp("temp.txt", ios::out);
	buff = IssuesSearch(key);
	if (buff == "NULL") {
		cout << "Vehicle NOT FOUND";
	}
	
	else {

		fstream IssuesDetails;
		IssuesDetails.open("IssuesDetails.txt", ios::in);
		while (!IssuesDetails.eof())
		{
			buffer.erase();
			pos = IssuesDetails.tellg();
			getline(IssuesDetails, buffer);
			i = 0;
			date.erase();
		

			while (buffer[i] != '|')
				date += buffer[i++];
			time.erase();
			i++;
			while (buffer[i] != '|')
				time += buffer[i++];
			VehicleNo.erase();
			i++;
			while (buffer[i] != '|')
				VehicleNo += buffer[i++];
			Issues.erase();
			i++;
			while (buffer[i] != '|')
				Issues += buffer[i++];
			status.erase();
			i++;
			while (buffer[i] != '$')
				status += buffer[i++];

			if (VehicleNo == key)
				continue;
			else {
				temp << buffer << endl;
				cout << buffer;
			}
		}
		IssuesDetails.close();
		temp.close();
		temp.open("temp.txt");
		remove("IssuesDetails.txt");
		fstream IssuesDetails1;
		IssuesDetails1.open("IssuesDetails.txt",ios::app);
		if (IssuesDetails1.is_open()) {
			while (!temp.eof()) {
				buffer.erase();
				getline(temp, buffer);
				cout << buffer;
				IssuesDetails1 << buffer << endl;

			}
			IssuesDetails1.close();

			temp.close();
			remove("temp.txt");
		}
		else {
			cout << "file ainr open";
		}
		
	}
	
}

int main()
{
	
	CarService cs;
	//cs.HomePage();
	cs.IssuesDelete("ka30303");

}