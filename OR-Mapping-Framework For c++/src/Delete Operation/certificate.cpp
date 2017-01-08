#include"certificate.h"
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
extern  int cid;
extern	string certificate_name;
extern	int EMPLOYEE_ID;
extern Employee *employee;

string Certificate::serialize(){
	//ostringstream oss;
	//oss << cid;
	//string s = oss.str();
	return certificate_name;

}
Certificate::Certificate(string certificate_name,Employee *employee){

	
	this->certificate_name=certificate_name;
	this->employee=employee;

}

Session* Certificate::getobj(){
	return employee;	
 
}
