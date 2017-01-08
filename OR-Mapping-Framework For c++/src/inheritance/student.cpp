//#ifdef
#include"student.h"
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
//extern int person_id;
extern string joiningdate;
extern string deptname;
//extern string birthdate;
//extern string cellphone;

 string Student::serialize(){
	
	return (getfirstname()+","+getlastname()+","+joiningdate+","+deptname);
}
Student::Student(string firstname,string lastname,string joiningdate,string deptname): Person(firstname,lastname){

	//this->id=id;
	this->joiningdate=joiningdate;
	this->deptname=deptname;
	//this->birthdate=birthdate;
	//this->cellphone=cellphone;

}



