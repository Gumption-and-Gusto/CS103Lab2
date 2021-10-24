#include <iostream>
#include <string>
using namespace std;

//Structure
struct Employee {
	string id;
	string fName;
	string mName;
	string lName;
	string address;
	string suburb;
	string city;
	int postcode;
	string phone;//For this and several other fields that are typically only numbers, I use strings in case people include spaces and/or punctuation marks to ensure the program can gather and display the data
	string email;
	string IRD;
	string taxCode;
	float hours;
	float wage;
	float gross;
	float taxRate;
	float taxDeducted;
	float net;

	//Constructor
	Employee(string iD = "", string fn = "", string mn = "", string ln = "", string addr = "", string burb = "", string cty = "", int pcode = 0, string ph = "", string em = "", string ir = "", string tc = "", float hrs = 0, float wg = 0, float gr = 0, float tr = 0, float td = 0, float nt = 0) {
		id = iD;
		fName = fn;
		mName = mn;
		lName = ln;
		address = addr;
		suburb = burb;
		city = cty;
		postcode = pcode;
		phone = ph;
		email = em;
		IRD = ir;
		taxCode = tc;
		hours = hrs;
		wage = wg;
		gross = gr;
		taxRate = tr;
		taxDeducted = td;
		net = nt;
	}
};

//Function Prototype
void drawLine();

int main()
{
	//Get week dates
	cout << "Welcome to the StarStaff Payroll system!\n\nEnter Week Start Date : ";
	string startDate;
	getline(cin, startDate);
	cout << "Enter Week End Date : ";
	string endDate;
	getline(cin, endDate);

	//Take Employee Details
	Employee details[5];
	for (int worker = 0; worker < 5; worker++) {
		cout << "\n\n";
		drawLine();
		cout << "\n\nEnter information for Employee #" << worker + 1 << "\n\n";
		drawLine();
		cout << "\nEnter Employee ID : ";
		cin.ignore();
		getline(cin, details[worker].id);
		cout << "Enter First Name : ";
		getline(cin, details[worker].fName);
		cout << "Enter Middle Name(s) : ";
		getline(cin, details[worker].mName);
		cout << "Enter Employee Last Name : ";
		getline(cin, details[worker].lName);
		cout << "Enter Street Address : ";
		getline(cin, details[worker].address);
		cout << "Enter Suburb : ";
		getline(cin, details[worker].suburb);
		cout << "Enter City : ";
		getline(cin, details[worker].city);
		cout << "Enter Postcode : ";
		cin >> details[worker].postcode;
		cout << "Enter Contact Number : ";
		cin.ignore();
		getline(cin, details[worker].phone);
		cout << "Enter Email Address : ";
		getline(cin, details[worker].email);
		cout << "Enter IRD Number : ";
		getline(cin, details[worker].IRD);
		cout << "Enter Tax Code : ";
		getline(cin, details[worker].taxCode);
		cout << "Enter Hours Worked : ";
		cin >> details[worker].hours;
		while (details[worker].hours > 49 || details[worker].hours < 1) {//While loops make sure the inputs are within the specified parameters
			cout << "Hours worked must be between 1 and 49 inclusive. Try again : ";
			cin >> details[worker].hours;
		}
		cout << "Enter Hourly Rate : ";
		cin >> details[worker].wage;
		while (details[worker].wage > 50 || details[worker].wage < 20) {
			cout << "Hourly rate must be between 20 and 50 inclusive. Try again : ";
			cin >> details[worker].wage;
		}
		cout << "Enter Tax Rate : ";//Incidentally the brief fundamentally misunderstands the tax system in Aotearoa - your income is taxed at different rates beyond certain points; a single tax rate is not used based on total income. A tax rate of 39% is impossible as the first 179,999.99 will be taxed lower. I have created the system per the brief rather than per the real tax system. It is possible to be taxed at any rate from 10.5% to an infintiely small amount less than 39% so I will accept anything in that range including 39% itself to account for rounding.
		cin >> details[worker].taxRate;
		while (details[worker].taxRate < 10.5 || details[worker].taxRate > 39) {
			cout << "Tax rate must be between 10.5 and 39 inclusive. Try again : ";
			cin >> details[worker].taxRate;
		}
	}

	//Payslip Divider
	cout << "\n";
	drawLine();
	cout << "\n\nPayslip for week starting on " << startDate << " and ending on " << endDate << "\n\n";
	drawLine();

	//Payslip Generation
	for (int worker = 0; worker < 5; worker++) {
		cout << "\n\nEmployee ID \t: " << details[worker].id;//I split this section across lines for readability, but you could have all the definitions at the top and the rest as one long cout line
		cout << "\nFull Name \t: " << details[worker].fName << " " << details[worker].mName << " " << details[worker].lName;
		cout << "\nAddress \t: " << details[worker].address << " " << details[worker].suburb << " " << details[worker].city << " " << details[worker].postcode;
		cout << "\nContact Number \t: " << details[worker].phone;
		cout << "\nEmail Address \t: " << details[worker].email;
		cout << "\nIRD Number \t: " << details[worker].IRD;
		cout << "\nTax Code \t: " << details[worker].taxCode;
		cout << "\nHours Worked \t: " << details[worker].hours;
		cout << "\nHourly Rate \t: " << details[worker].wage;
		cout << "\nTax Rate \t: " << details[worker].taxRate;
		float overtime = 0;
		if (details[worker].hours > 40) {//This if statement calculates overtime pay
			overtime = details[worker].hours - 40;//Calculates hours worked over 40
		}
		details[worker].gross = details[worker].wage * (details[worker].hours + (overtime / 2));//Adds half overtime hours to the gross calculation
		cout << "\nGross Pay \t: " << details[worker].gross;
		details[worker].taxDeducted = details[worker].gross * details[worker].taxRate / 100;
		cout << "\nTax Deducted \t: " << details[worker].taxDeducted;
		details[worker].net = details[worker].gross - details[worker].taxDeducted;
		cout << "\nNet Pay \t: " << details[worker].net << "\n\n";
		drawLine();
	}

	//Report Divider
	cout << "\n\n Weekly statistics for week starting on " << startDate << " and ending on " << endDate << "\n\n";
	drawLine();

	//Report
	float totalGross = 0;
	for (int worker = 0; worker < 5; worker++) {
		totalGross = totalGross + details[worker].gross;
	}
	cout << "\nTotal amount paid in gross pay : " << totalGross;
	float totalTax = 0;
	for (int worker = 0; worker < 5; worker++) {
		totalTax = totalTax + details[worker].taxDeducted;
	}
	cout << "\n\nTotal amount deducted for tax : " << totalTax;
	float totalNet = totalGross - totalTax;
	cout << "\n\nTotal amount paid in net pay : " << totalNet << "\n\n";
	drawLine();
}

//Function Defintion
void drawLine() {
	for (int loops = 0; loops < 50; loops++) {
		cout << "*";
	}
}