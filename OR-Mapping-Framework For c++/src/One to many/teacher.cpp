//#ifdef
#include"teacher.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>

#include"Session.h"
using namespace std;
extern int t_id;
extern string t_name;

extern string t_cabin;
extern string cellphone;

string Teacher::serialize(){
	ostringstream oss;
	oss << t_id;
	string s = oss.str();
	return (s+","+t_name+","+t_cabin+","+cellphone);
}
Teacher::Teacher(int t_id,string t_name,string t_cabin,string cellphone){

	this->t_id=t_id;
	this->t_name=t_name;
	this->t_cabin=t_cabin;
	
	this->cellphone=cellphone;
	

}

 	



