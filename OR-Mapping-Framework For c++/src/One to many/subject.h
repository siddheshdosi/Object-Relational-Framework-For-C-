#ifndef SUBJECT_H
#define SUBJECT_H
#include"Session.h"
#include"teacher.h"
#include<string>
class Teacher;

using namespace std;
class Subject : public Session
{

public:
	int s_id;
	string s_name;
	string Teacher_id;
   	Teacher *teacher;
	//Subject(int,string);
	Subject(int,string,Teacher*);
	string serialize();
	Session *getobj();
};

#endif
