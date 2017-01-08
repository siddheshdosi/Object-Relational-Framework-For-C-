#include"Session.h"
#include<string>
class Employee;
//#include"employee.h"
//class Session;

using namespace std;
class Chair : public Session 
{
  
public:
	int chairid;
	string chairLocation;
	
	Employee *employee;

	//function declaration
	//EmployeeDetails(int,string,string,string,string);
	Chair(int,string,Employee*);
	string serialize();
};
