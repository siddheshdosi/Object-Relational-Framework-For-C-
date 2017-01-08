#ifndef Teacher_H
#define Teacher_H
#include"Session.h"
#include<vector>
#include<string>

using namespace std;
class Teacher : public Session
{
  
public:
	int t_id;
	string t_name;
	string t_cabin;
	
	string cellphone;
	Teacher(int,string,string,string);
	//function declaration
	string serialize();
	
	

};
#endif
