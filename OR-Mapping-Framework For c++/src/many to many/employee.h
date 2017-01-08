#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include"Session.h"
#include<vector>
#include<string>
#include"meeting.h"
using namespace std;
class Employee : public Session
{
  
public:
	int id;
	string firstname;
	string lastname;
	string birthdate;
	string cellphone;
	vector<Meeting *>*m;
	Employee(string,string,string,string,vector<Meeting*>*);
	//function declaration
	string serialize();
	vector<Session *> * getlistobj();
	

};
#endif
