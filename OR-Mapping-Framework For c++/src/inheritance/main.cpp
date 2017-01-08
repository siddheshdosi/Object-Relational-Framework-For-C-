//#ifdef
#include<iostream>
#include<string>



#include"person.h"
#include"student.h"

#include"Sessionfactory.h"
#include<typeinfo>
#include<vector>

using namespace std;

int main(){
	
	
	Session *p1 = new Person("abc","asd");
	Session *st = new Student("siddhesh","dosi","23-45-6","drpt01");
	
	
	cSessionFactory sf;
//	string str="employee.hbm.xml";
	
	sf.openSession();
	//sf.Delete(s2,"2");
	
	sf.save(p1);
	sf.save(st);
	
	
	
	sf.close();
	return 0;	
}
