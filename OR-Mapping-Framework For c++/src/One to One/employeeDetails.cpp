//#include"Sessionfactory.h"
#include"employeeDetails.h"
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
extern int id;
extern string street;
extern string city;
extern string state;
extern string country;
extern Employee *employee;
string EmployeeDetails::serialize(){
	ostringstream oss;
	oss << id;
	string s = oss.str();
	//string s = "1,26/c IIITB Electronic city,Bangalore,Karanatak,India";	
	return (street+","+city+","+state+","+country);
}
//EmployeeDetails::EmployeeDetails(int id,string street,string city,string state,string country){
EmployeeDetails::EmployeeDetails(string street,string city,string state,string country,Employee *e){
	//this->id=id;
	this->street=street;
	this->city=city;
	this->state=state;
	this->country=country;
	this->employee=e;

}
Session* EmployeeDetails::getobj(){
	return employee;	
 
}


