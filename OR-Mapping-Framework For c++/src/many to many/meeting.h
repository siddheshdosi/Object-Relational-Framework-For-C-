#ifndef MEETING_H
#define MEETING_H
#include"Session.h"
#include<vector>
#include<string>

using namespace std;
class Meeting : public Session
{
  
public:
	int id;
	string subject;
	string meeting_date;
	//string birthdate;
	//string cellphone;
	
	Meeting(string,string);
	//function declaration
	string serialize();
	
	

};
#endif
