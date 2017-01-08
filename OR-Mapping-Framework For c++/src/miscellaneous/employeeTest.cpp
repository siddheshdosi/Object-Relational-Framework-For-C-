//#ifdef
#include<iostream>
#include<string>
#include"employeeDetails.h"
#include"employee.h"
#include"chair.h"
#include"person.h"
#include"student.h"
#include"meeting.h"
#include"customer.h"
#include"Sessionfactory.h"
#include<typeinfo>
#include<vector>
#include"certificate.h"
using namespace std;

int main(){
	//Employee employee;
	//employee.setid(1);	
	//employee.setfirstname("siddhesh");
	//employee.setlastname("dosi");
	//employee.setbirthdate("23-08-1990");
	//employee.setcellphone("9001156287");
	//int i= employee.getid();
	
	Session *p1 = new Person("abc","asd");
	Session *st = new Student("siddhesh","dosi","23-45-6","drpt01");
	//Session *s1 = new Employee("siddhesh","dosi","23-08-1990","9001156287");
	//Session *s2 = new Employee("Nikhil","shah","29-03-1991","9413625222");
	//Session *s4 = new Employee("Rakesh","Rajpurohit","23-12-1990","9001456343");
	Session *m1 = new Meeting("Data Modeling project meeting","10-04-2014");
	Session *m2 = new Meeting("Big Data","15-04-2014");
	vector<Meeting*> *meeting= new vector <Meeting*> ();;
	meeting->push_back((Meeting*)m1);
	meeting->push_back((Meeting*)m2);
	
	Session *s1 = new Employee("siddhesh","dosi","23-08-1990","9001156287",meeting);
	//Session *s2 = new Employee("Nikhil","shah","29-03-1991","9413625222",meeting);
	//Session *s4 = new Employee("Rakesh","Rajpurohit","23-12-1990","9001456343");
	//Session *del = new Employee;
	//Session *s3 = new EmployeeDetails(2,"26/c IIITB Electronic city","Bangalore","Karanataka","India");

	Session *s3 = new EmployeeDetails("26/c IIITB Electronic city","Bangalore","Karanataka","India",(Employee*)s1);
	
	//Session *ch = new Chair(1,"Building No. 2 Floor 1st Room No 3 Block No. 5",(Employee*)s2);
    Session *cer1 = new Certificate("SCJP Certified",(Employee *)s1);
    
    Session *customer1=new Customer("Rakesh RajPurohit","36 China Town","Jodhpur","Rajasthan","India","9999999999");
    Session *customer2=new Customer("Ashutosh Vyas","Tilawara","Jaipur","Rajasthan","India","8989898989");
    Session *customer3=new Customer("Srinivas Vaidhya","IIIT B","Bangalore","Karnataka","India","9867543423");
	//if(typeid(*s2).name==typeid(*s3->getobj()).name){
	//	cout<<"true"<<endl;
	//}
	//cout<<"the id of employee is = "<<i<<endl;
	//cout<<"the firstname of employee is = "<<employee.getfirstname();
	//cout<<"; the lastname of employee is = "<<employee.getlastname();
	//cout<<"; the birthdate of employee is = "<<employee.getbirthdate();
	//cout<<"; the cellphone of employee is = "<<employee.getcellphone();
	cSessionFactory sf;
//	string str="employee.hbm.xml";
	
	sf.openSession();
	//sf.Delete(s2,"2");
	
	sf.save(p1);
	sf.save(st);
	sf.save(s1);
	//sf.beginTransaction();
	//sf.save(s2);
	//sf.save(st);
	//sf.save(s2);
	//sf.save(s4);
	sf.save(s3);
	sf.save(cer1);
	sf.save(customer1);
	sf.save(customer2);
	sf.save(customer3);
	
	vector<Session *>sess=sf.get(customer1,"Id","*");
	
	for(int i=0;i<sess.size();i++){
		cout<<"name of the customer is ="<<((Customer *)sess[i])->getname()<<endl;
		
		
	}
	
	
	//s1=sf.get(customer1,"all","*");
	//sf.save(m1);
	//sf.save(m2);
	//sf.save(ch);
	
	sf.close();
	return 0;	
}
