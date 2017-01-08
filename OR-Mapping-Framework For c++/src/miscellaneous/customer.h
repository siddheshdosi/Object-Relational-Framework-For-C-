#ifndef CUSTOMER_H
#define CUSTOMER_H
#include"Session.h"
#include<vector>
#include<string>

using namespace std;
class Customer : public Session
{
  
public:
	string name;
	string street;	
	string city;
	string state;
	string country;
	string mobno;
	Customer();
	Customer(string,string,string,string,string,string);
	//function declaration
	string serialize();
	void set(vector<string>);
	Session * createobj();
	string getname();
	string getstreet();
	string getcity();
	string getstate();
	string getcountry();
	string getmobno();
};
#endif

