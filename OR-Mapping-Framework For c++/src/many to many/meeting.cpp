//#ifdef
#include"meeting.h"
#include<iostream>
#include<sstream>
#include<string>

#include<vector>
using namespace std;
extern int meeting_id;
extern string subject;
extern string meeting_date;

//extern string birthdate;
//extern string cellphone;

string Meeting::serialize(){
	//ostringstream oss;
	//oss << id;
	//string s = oss.str();
	return (subject+","+meeting_date);
}
Meeting::Meeting(string subject,string meeting_date){

	//this->id=id;
	this->subject=subject;
	this->meeting_date=meeting_date;
	
	//this->birthdate=birthdate;
	//this->cellphone=cellphone;

}



