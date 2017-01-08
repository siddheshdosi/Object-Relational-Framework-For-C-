#ifndef STUDENT_H
#define STUDENT_H
//#include"Session.h"
#include"person.h"
#include<string>

using namespace std;
class Student : public Person{
  
public:
	
	string joiningdate;
	string deptname;
	//string birthdate;
	//string cellphone;
	
	Student(string,string,string,string);
	//function declaration
	string serialize();
	
};
#endif
