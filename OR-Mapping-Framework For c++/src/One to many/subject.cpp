#include"subject.h"
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
extern  int s_id;
extern	string s_name;
extern	string Teacher_ID;
extern Teacher *teacher;

string Subject::serialize(){
	ostringstream oss;
	oss << s_id;
	string s = oss.str();
	return s+","+s_name;

}
//Subject::Subject(int s_id,string s_name){
Subject::Subject(int s_id,string s_name,Teacher *teacher){

	this->s_id=s_id;
	this->s_name=s_name;
	this->teacher=teacher;

}

Session* Subject::getobj(){
	return teacher;	
 
}
