//#ifdef
#include<iostream>
#include<string>

#include"employee.h"


#include"meeting.h"

#include"Sessionfactory.h"
#include<typeinfo>
#include<vector>

using namespace std;

int main(){
	
	
	
	Session *m1 = new Meeting("Data Modeling project meeting","10-04-2014");
	Session *m2 = new Meeting("Big Data","15-04-2014");
	vector<Meeting*> *meeting1= new vector <Meeting*> ();;
	meeting1->push_back((Meeting*)m1);
	meeting1->push_back((Meeting*)m2);
	vector<Meeting*> *meeting2= new vector <Meeting*> ();;
	Session *m3 = new Meeting("Data Analytics","20-04-2014");
	Session *m4 = new Meeting("Active Data","25-04-2014");
	meeting2->push_back((Meeting*)m3);
	meeting2->push_back((Meeting*)m4);
	Session *e1 = new Employee("siddhesh","dosi","23-08-1990","9001156287",meeting1);
	Session *e2 = new Employee("Nikhil","shah","29-03-1991","9413625222",meeting2);
	//Session *s4 = new Employee("Rakesh","Rajpurohit","23-12-1990","9001456343");
	
	
	cSessionFactory sf;
	sf.openSession();
	sf.save(e1);
	sf.save(e2);
	sf.close();
	return 0;	
}
