//#include"Sessionfactory.h"
#include"chair.h"
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
extern int chairid;
extern string chairLocation;

extern Employee *employee;
string Chair::serialize(){
	ostringstream oss;
	oss << chairid;
	string s = oss.str();
	//string s = "1,26/c IIITB Electronic city,Bangalore,Karanatak,India";	
	//return (s+","+chairLocation);
	return ("2,Building No. 2 Floor 1st Room No 3 Block No. 5");
}
//EmployeeDetails::EmployeeDetails(int id,string street,string city,string state,string country){
Chair::Chair(int id,string chairLocation,Employee *e){
	this->chairid=chairid;
	this->chairLocation=chairLocation;
	
}


