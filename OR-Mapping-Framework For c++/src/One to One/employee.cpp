//#ifdef
#include"employee.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>

#include"Session.h"
using namespace std;
/*extern int id;
extern string firstname;
extern string lastname;
extern string birthdate;
extern string cellphone;*/

string Employee::serialize(){
	ostringstream oss;
	oss << id;
	string s = oss.str();
	return (s+","+firstname+","+lastname+","+birthdate+","+cellphone);
}
Employee::Employee(int id,string firstname,string lastname,string birthdate,string cellphone){

	this->id=id;
	this->firstname=firstname;
	this->lastname=lastname;
	this->birthdate=birthdate;
	this->cellphone=cellphone;
	

}

	
 	



