#include <iostream>
#include<fstream>
#include<chrono>
#include<ctime>
#include<string>
#include<Windows.h>

using namespace std;

class CarService {
public:
	void HomePage();
	void CheckIn();
	void CheckOut();
	void Admin();
	void Employee();
	void AlreadyCust();
	void NewCust();
	void Employee_Delete(string);
	string Employee_search(string);
	string IssuesSearch(string);
	void IssuesDelete(string);
	void StatusUpdate(string, string);
	void NewComplain();
	void ServiceHistory(string,string);
	void Submit();
	void Issues(string);
	void Employee_Status_Update(string,string);
	string CustomerSearch(string);
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
	SYSTEMTIME st;
	GetSystemTime(&st);
	string userName, password, buffer, passw;
	int choice;
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
		AdminFile << userName << "|" << password << "$" << endl;
		AdminFile.close();
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
			AdminFile.close();
			cout << "login Successfull" << endl;
			cout << "\n";
			cout << "1. Add Employee" << endl;
			cout << "2. Remove Employee" << endl;
			
			cin >> choice;
			fstream Employee("Employee.txt", ios::app);
			string employee_name, salary, employee_position, joining_date, employee_id, status2, pass, re_enterPass;
			if (choice == 1) {
				cout << "Enter Employee Name" << endl;
				cin >> employee_name;
				cout << "Enter Employee User id" << endl;
				cin >> employee_id;
				int flag = 0;
				while (true) {
					pass.erase();
					re_enterPass.erase();
					cout << "Enter Employee Password" << endl;
					GetConsoleMode(hStdin, &mode);
					SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
					cin.ignore();
					getline(cin, pass);
					cout << "\n";
					SetConsoleMode(hStdin, mode);
					cout << "Re-enter Password" << endl;
					GetConsoleMode(hStdin, &mode);
					SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
					getline(cin, re_enterPass);
					SetConsoleMode(hStdin, mode);
					cout << "\n";
					if (pass == re_enterPass) {
						hash<string> mystdhash;
						pass = mystdhash(pass);
						break;
					}
				}
				cout << "Enter Employee Position" << endl;
				cin >> employee_position;
				cout << "Enter Employee Salary" << endl;
				cin >> salary;
				status2 = "0";
				Employee << st.wDay << "/" << st.wMonth << "/" << st.wYear << "|" << employee_name << "|" << employee_id << "|" << employee_position << "|" << salary << "|" << status2 <<"$"<< endl;
				Employee.close();
				AdminFile.open("Admin.txt", ios::app);
				AdminFile << employee_id << "|" << pass << "$" << endl;
			}
		}
		else {
			cout << "login not successfull" << endl;
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
	cout << password;
	SetConsoleMode(hStdin, mode);
	hash<string> mystdhash;
	password = mystdhash(password);
	buffer.erase();
	int i = 0;
	while (usern_file != userName)
	{
		usern_file.erase();
		buffer.erase();
		if (!getline(AdminFile, buffer))
			break;
		i = 0;
		while (buffer[i] != '|')
			usern_file += buffer[i++];
		i++;

		passw_file.erase();
		while (buffer[i] != '$')
			passw_file += buffer[i++];
		if (AdminFile.eof()) {
			break;
		}
	}

	if (passw_file == password)
	{
		int i = 0;
		fstream IssuesDetails;
		cout << "\n";
		cout << "Login Successfull!!!....\n";
		IssuesDetails.open("IssuesDetails.txt", ios::in);
		while (!IssuesDetails.eof())
		{
			buffer.erase();
			pos = IssuesDetails.tellg();
			i = 0;
			date.erase();
			if (!getline(IssuesDetails, buffer))
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
				cout << date << "|" << time << "|" << VehicleNo << "|" << Issues << "$" << endl;
			}
		}
		cout << "Enter the vehicle number to select the vehicle:";
		cin >> key;
		StatusUpdate(key, "1");
		cout << "status up";
		Employee_Status_Update(userName, "1");
		ServiceHistory(key,userName);
	}
	else
	{
		cout << "login not successfull  ";
		Employee();
	}
	
}

string CarService::Employee_search(string key)
{
	int flag = 0, pos = 0, i, choice;
	string date, employee_name, employee_id, position, salary, status, buffer;
	string PhoneNumber;
	ifstream Employee;
	Employee.open("Employee.txt", ios::in);
	while (!Employee.eof())
	{
		buffer.erase();
		if (!getline(Employee, buffer))
			break;
		pos = Employee.tellg();
		i = 0;
		date.erase();

		while (buffer[i] != '|')
			date += buffer[i++];
		employee_name.erase();
		i++;

		while (buffer[i] != '|')
			employee_name += buffer[i++];
		employee_id.erase();
		i++;

		while (buffer[i] != '|')
			employee_id += buffer[i++];
		position.erase();
		i++;

		while (buffer[i] != '|')
			position += buffer[i++];
		salary.erase();
		i++;

		while (buffer[i] != '|')
			salary += buffer[i++];
		status.erase();
		i++;
		while (buffer[i] != '$')
			status += buffer[i++];

		if (employee_id == key)
		{
			Employee.close();
			return buffer;
		}
	}
	Employee.close();
	return "NULL";
}

void CarService::Employee_Delete(string key)
{
	int pos = 0, i = 0;
	string date, employee_name, employee_id, position, salary, status, buffer;
	fstream temp("temp.txt", ios::out);
	buffer = Employee_search(key);
	if (buffer == "NULL") {
		cout << "Vehicle NOT FOUND";
	}
	else {
		fstream Employee;
		Employee.open("Employee.txt", ios::in);
		while (!Employee.eof())
		{
			buffer.erase();
			if (!getline(Employee, buffer))
				break;
			pos = Employee.tellg();
			i = 0;
			date.erase();

			while (buffer[i] != '|')
				date += buffer[i++];
			employee_name.erase();
			i++;

			while (buffer[i] != '|')
				employee_name += buffer[i++];
			employee_id.erase();
			i++;

			while (buffer[i] != '|')
				employee_id += buffer[i++];
			position.erase();
			i++;

			while (buffer[i] != '|')
				position += buffer[i++];
			salary.erase();
			i++;

			while (buffer[i] != '|')
				salary += buffer[i++];
			status.erase();
			i++;
			while (buffer[i] != '$')
				status += buffer[i++];

			if (employee_id == key)
				continue;
			else {
				temp << buffer << endl;
			}
		}
		Employee.close();
		temp.close();
		temp.open("temp.txt", ios::in);
		remove("Employee.txt");
		fstream IssuesDetails1;
		IssuesDetails1.open("Employee.txt", ios::out);
		string text;
		if (IssuesDetails1.is_open()) {
			while (!temp.eof()) {
				buffer.erase();
				if (!getline(temp, buffer))
					break;
				text += buffer + "\n";
			}
			IssuesDetails1 << text;
			IssuesDetails1.close();
			temp.close();
		}
		else {
			cout << "file aint open";
		}
	}
}

void CarService::Employee_Status_Update(string key, string status1)
{
	string buffr, key1;
	int flag = 0, pos = 0, i = 0, choice;
	string date, employee_name, employee_id, position, salary, status, buffer;
	buffer.erase();
	buffer = Employee_search(key);
	if (buffr == "NULL")
	{
		cout << "Employee NOT FOUND \nEnter Employee ID again :";
		cin >> key1;
		Employee_Status_Update(key1, status1);
	}
	else
	{
		Employee_Delete(key);
		date.erase();

		while (buffer[i] != '|')
			date += buffer[i++];
		employee_name.erase();
		i++;

		while (buffer[i] != '|')
			employee_name += buffer[i++];
		employee_id.erase();
		i++;

		while (buffer[i] != '|')
			employee_id += buffer[i++];
		position.erase();
		i++;

		while (buffer[i] != '|')
			position += buffer[i++];
		salary.erase();
		i++;

		while (buffer[i] != '|')
			salary += buffer[i++];
		status.erase();
		i++;
		while (buffer[i] != '$')
			status += buffer[i++];
		status = status1;

		fstream Employee("Employee.txt", ios::app);
		Employee.seekp(0, ios::beg);
		Employee << date << "|" << employee_name << "|" << employee_id << "|" << position << "|" << salary << "|" << status << "$" << endl;
		Employee.close();
	}
}

void CarService::AlreadyCust() {
	int flag = 0, pos = 0, choice;
	string VehicleNo, name, key, confirm, buffer;
	string PhoneNumber;
	cout << "Enter your Vehicle Number: " << endl;
	cin >> key;
	ifstream CustomerDetails;
	CustomerDetails.open("CustomerDetails.txt", ios::in);
	while (!CustomerDetails.eof())
	{
		buffer.erase();
		pos = CustomerDetails.tellg();
		if (!getline(CustomerDetails, buffer))
			break;
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
				//case 2: View_ServiceHistory();
					//break;
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
void CarService::ServiceHistory(string key,string employee_ID) 
{
	string buffer, date, time, customerName, VehicleNo, Issues, status, amount, payment;
	int pos = 0, i = 0;
	fstream ServiceHistory("ServiceHistory.txt",ios::app);
	fstream CustomerDetails;
	CustomerDetails.open("CustomerDetails.txt", ios::in);
	fstream IssuesDetails("IssueDetails.txt", ios::in);
	buffer = IssuesSearch(key);
	customerName = CustomerSearch(key);
	if (buffer == "NULL" ||customerName=="NULL") {
		cout << "not found" << endl;
	}
	else {
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
		payment = "0";
		ServiceHistory << date << "|" << time << "|" << VehicleNo << "|" << customerName << "|" << Issues <<"|"<<employee_ID <<"|" << status << "|" << payment << "$" << endl;
	}
	

}

string CarService::CustomerSearch(string key)
{
	int flag = 0, pos = 0, choice;
	string VehicleNo, name, confirm, buffer;
	string PhoneNumber;
	ifstream CustomerDetails;
	CustomerDetails.open("CustomerDetails.txt", ios::in);
	while (!CustomerDetails.eof())
	{
		buffer.erase();
		pos = CustomerDetails.tellg();
		if (!getline(CustomerDetails, buffer))
			break;
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
			return name;
		}
	}
	return "NULL";
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
	string date, time, VehicleNo, Issues, status, buffer;
	string PhoneNumber;
	ifstream IssuesDetails;
	IssuesDetails.open("IssuesDetails.txt", ios::in);
	while (!IssuesDetails.eof())
	{
		buffer.erase();
		pos = IssuesDetails.tellg();
		i = 0;
		date.erase();
		if (!getline(IssuesDetails, buffer))
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
		{
			IssuesDetails.close();
			return buffer;
		}
	}
	IssuesDetails.close();
	return "NULL";
}

void CarService::StatusUpdate(string key, string status1) {

	string buffr, key1;
	int flag = 0, pos = 0, i = 0, choice;
	string date, time, VehicleNo, Issues, status;
	buffr.erase();
	buffr = IssuesSearch(key);
	if (buffr == "NULL")
	{
		cout << "Vehicle NOT FOUND \nEnter Vehicle Number again :";
		cin >> key1;
		StatusUpdate(key1, status1);
	}
	else
	{
		IssuesDelete(key);
		while (buffr[i] != '|')
			date += buffr[i++];
		time.erase();
		i++;
		while (buffr[i] != '|')
			time += buffr[i++];
		VehicleNo.erase();
		i++;
		while (buffr[i] != '|')
			VehicleNo += buffr[i++];
		Issues.erase();
		i++;
		while (buffr[i] != '|')
			Issues += buffr[i++];
		status.erase();
		i++;
		while (buffr[i] != '$')
			status += buffr[i++];
		status.erase();
		status = status1;

		fstream IssuesDetails("IssuesDetails.txt", ios::app);
		IssuesDetails.seekp(0, ios::beg);
		IssuesDetails << date << "|" << time << "|" << VehicleNo << "|" << Issues << "|" << status << "$" << endl;
		IssuesDetails.close();
	}
}



void CarService::IssuesDelete(string key) {

	int pos = 0, i = 0;
	string date, time, VehicleNo, Issues, status, buffer;
	fstream temp("temp.txt", ios::out);
	buffer = IssuesSearch(key);
	if (buffer == "NULL") {
		cout << "Vehicle NOT FOUND";
	}
	else {
		fstream IssuesDetails;
		IssuesDetails.open("IssuesDetails.txt", ios::in);
		while (!IssuesDetails.eof())
		{
			buffer.erase();
			if (!getline(IssuesDetails, buffer))
				break;
			pos = IssuesDetails.tellg();
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
			}
		}
		IssuesDetails.close();
		temp.close();
		temp.open("temp.txt", ios::in);
		remove("IssuesDetails.txt");
		fstream IssuesDetails1;
		IssuesDetails1.open("IssuesDetails.txt", ios::out);
		string text;
		if (IssuesDetails1.is_open()) {
			while (!temp.eof()) {
				buffer.erase();
				if (!getline(temp, buffer))
					break;
				text += buffer + "\n";
			}
			IssuesDetails1 << text;
			IssuesDetails1.close();
			temp.close();
		}
		else {
			cout << "file aint open";
		}
	}
}


int main()
{
	CarService cs;
	cs.HomePage();
	//cs.IssuesDelete("ka19");
	//cout<<cs.IssuesSearch("ka19");
	//cs.StatusUpdate("ka19", "1");
	//cs.Employee_Status_Update("tejus11", "1");
}