#include <iostream>
#include<fstream>
#include<chrono>
#include<ctime>
#include<string>
#include<Windows.h>


using namespace std;

class CarService {
public:
	void CheckIn();
	//void CheckOut();
	//void Admin();
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
	
	CustomerFile << name << " " << phNumber << " " << vehicleNo << endl;
	CustomerFile.close();
	Issues(vehicleNo);

}
void CarService::Issues(string vehicle_numb) {
	string issus;
	SYSTEMTIME st;
	GetSystemTime(&st);


	ofstream CarIssues("IssuesDetails.txt");
	cout << "Enter the Issues in your Vehicle:";
	cin.ignore();
	getline(cin, issus);
	CarIssues <<st.wDay << "/"<<st.wMonth<<"/"<<st.wYear<<" "<<st.wHour<<":"<<st.wMinute <<" "<< vehicle_numb << " " << issus << endl;
	CarIssues.close();


}


		int main()
		{
			CarService cs;
			cs.CheckIn();
		

		}