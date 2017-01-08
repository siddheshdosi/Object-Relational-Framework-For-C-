#include"Session.h"
#include<string>
//class Employee;
#include"employee.h"
//class Session;

using namespace std;
class EmployeeDetails : public Session 
{
  
public:
	int id;
	string street;
	string city;
	string state;
	string country;
	Employee *employee;

	//function declaration
	//EmployeeDetails(int,string,string,string,string);
	EmployeeDetails(string,string,string,string,Employee*);
	string serialize();
	Session *getobj();
};
