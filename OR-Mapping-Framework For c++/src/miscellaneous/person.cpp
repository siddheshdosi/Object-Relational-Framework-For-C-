//#ifdef
#include"person.h"
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
extern int person_id;
extern string firstname;
extern string lastname;
//extern string birthdate;
//extern string cellphone;

 string Person::serialize(){
	ostringstream oss;
	oss << id;
	string s = oss.str();
	return (firstname+","+lastname);
}
Person::Person(string firstname,string lastname){

	//this->id=id;
	this->firstname=firstname;
	this->lastname=lastname;
	//this->birthdate=birthdate;
	//this->cellphone=cellphone;

}
string Person::getfirstname(){
 
	return firstname;
}
string Person::getlastname(){
	return lastname;
}

