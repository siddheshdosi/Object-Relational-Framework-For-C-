#ifndef PERSON_H
#define PERSON_H
#include"Session.h"

#include<string>

using namespace std;
class Person : public Session
{
  
public:
	int id;
	string firstname;
	string lastname;
	//string birthdate;
	//string cellphone;
	
	Person(string,string);
	//function declaration
	virtual string serialize();
	string getfirstname();
	string getlastname();	
	

};
#endif
