
#include<iostream>
#include<string>
#include"employee.h"
#include"Sessionfactory.h"
#include<typeinfo>
#include<vector>
#include"certificate.h"
using namespace std;

int main(){
	
	Session *s1 = new Employee(1,"siddhesh","dosi","23-08-1990","9001156287");
	Session *s2 = new Employee(2,"Nikhil","shah","29-03-1991","9413625222");

    cSessionFactory sf;
//	string str="employee.hbm.xml";
	
	sf.openSession();
	sf.save(s1);
	sf.save(s2);
	sf.Delete(s2,"id","2");
	
	sf.close();
	return 0;	
}
