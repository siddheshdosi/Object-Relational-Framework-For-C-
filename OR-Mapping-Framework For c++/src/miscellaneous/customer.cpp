//#ifdef
#include"customer.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
//#include"meeting.h"
#include"Session.h"
using namespace std;
extern int id;
extern string name;
extern string street;
extern string city;
extern string state;
extern string country;
extern string mobno;

Customer::Customer(){}

string Customer::serialize(){
	//ostringstream oss;
	//oss << id;
	//string s = oss.str();
	return (name+","+street+","+city+","+state+","+country+","+mobno);
}
Customer::Customer(string name,string street,string city,string state,string country,string mobno){

	//this->id=id;
	this->name=name;
	this->street=street;
	this->city=city;
	this->state=state;
	this->country=country;
	this->mobno=mobno;
	

}

void Customer::set(vector<string> v){
	//this->id= v[0]
	this->name=v[1];
	this->street=v[2];
	this->city=v[3];
	this->state=v[4];
	this->country=v[5];
	this->mobno=v[6];
	
}	
Session * Customer::createobj(){
	Session *c = new Customer();
	return c;
	
} 	

string Customer::getname(){
	return name;
}
string Customer::getstreet(){
	return street;
}
string Customer::getcity(){
	return city;
}
string Customer::getstate(){
	return state;
}
string Customer::getcountry(){
	return country;
}
string Customer::getmobno(){
	return mobno;
}
