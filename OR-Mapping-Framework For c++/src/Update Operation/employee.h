#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include"Session.h"
#include<vector>
#include<string>
using namespace std;
class Employee : public Session
{
  
public:
	int id;
	string firstname;
	string lastname;
	string birthdate;
	string cellphone;
	Employee(int,string,string,string,string);
	void setfirstname(string);
	void setid(int);
	//function declaration
	string serialize();
	
};
#endif
