#ifndef CERTIFICATE_H
#define CERTIFICATE_H
#include"employee.h"
#include<string>
class Employee;

using namespace std;
class Certificate : public Session
{

public:
	int cid;
	string certificate_name;
	int employee_id;
   	Employee *employee;

	Certificate(string,Employee*);
	string serialize();
	Session *getobj();
};

#endif
