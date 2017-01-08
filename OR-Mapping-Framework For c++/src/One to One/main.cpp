//#ifdef
#include<iostream>
#include<string>

#include"employee.h"
#include"employeeDetails.h"

#include"Sessionfactory.h"
#include<typeinfo>
#include<vector>

using namespace std;

int main(){
	
	
	Session *e1= new Employee(2,"Ashutosh","Vyas","26-09-1989","9460234512");
	Session *ed1 = new EmployeeDetails("Tilawara","Jaipur","Rajasthan","India",(Employee *)e1);
	//Session *sub2 = new Subject(6,"Data Structure",(Teacher *)t1);
	
	
	cSessionFactory sf;
	
	
	sf.openSession();
	
	sf.save(e1);
	sf.save(ed1);
	//sf.save(sub2);
	
	sf.close();
	return 0;	
}
