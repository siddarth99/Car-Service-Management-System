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
	cout << "1.Check In\n2. Check Out\n3. Admin\n4. Employee\n5. Exit" << endl;
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



void CarService::Employee() {
	fstream EmployeeFile;
	EmployeeFile.open("Employee.txt", ios::in);
	string EmployeeID, Password;
	cout << "Enter the Employee ID : ";


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
		int ch = 1, i = 0; 
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

		
		if (VehicleNo ==key )
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
			else{
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

		CustomerFile << name << "|" << phNumber << "|" << vehicleNo <<"$"<< endl;

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
	int status=0;
	string issues,wax_wash,confirm;
	SYSTEMTIME st;
	GetSystemTime(&st);


	ofstream CarIssues("IssuesDetails.txt",ios::app);
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


		CarIssues << st.wDay << "/" << st.wMonth << "/" << st.wYear << " " << st.wHour << ":" << st.wMinute << " " << vehicle_numb << " " << issues <<status<< endl;
		
		CarIssues.close();
	}
	else {
		Issues(vehicle_numb);
	}

}


int main()
{
	CarService cs;
	cs.HomePage();


}