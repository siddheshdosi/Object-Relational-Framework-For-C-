//#ifdef
#include"employee.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include"meeting.h"
#include"Session.h"
using namespace std;
extern int id;
extern string firstname;
extern string lastname;
extern string birthdate;
extern string cellphone;
extern vector<Meeting *> *m;
string Employee::serialize(){
	//ostringstream oss;
	//oss << id;
	//string s = oss.str();
	return (firstname+","+lastname+","+birthdate+","+cellphone);
}
Employee::Employee(string firstname,string lastname,string birthdate,string cellphone,vector<Meeting*> *m){

	//this->id=id;
	this->firstname=firstname;
	this->lastname=lastname;
	this->birthdate=birthdate;
	this->cellphone=cellphone;
	this->m=m;

}
vector<Session*> * Employee::getlistobj(){
			return (vector<Session*> *)m;
	}
	
 	



