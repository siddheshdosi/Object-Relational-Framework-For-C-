//#ifdef
#include<iostream>
#include<string>

#include"subject.h"

#include"Sessionfactory.h"
#include<typeinfo>
#include<vector>

using namespace std;

int main(){
	
	
	Session *t1= new Teacher(10,"Naveen Kedia","c12","9001156287");
	Session *sub1 = new Subject(5,"TOC",(Teacher *)t1);
	Session *sub2 = new Subject(6,"Data Structure",(Teacher *)t1);
	
	
	cSessionFactory sf;
	
	
	sf.openSession();
	
	sf.save(t1);
	sf.save(sub1);
	sf.save(sub2);
	
	sf.close();
	return 0;	
}
