#include<iostream>
#include<string>
#include"employee.h"
#include"customer.h"
#include"Sessionfactory.h"
#include<typeinfo>
#include<vector>
using namespace std;

int main(){
	Session *s1 = new Employee(1,"siddhesh","dosi","23-08-1990","9001156287");
	Session *s2 = new Employee(2,"Nikhil","shah","29-03-1991","9413625222");
	
    Session *customer1=new Customer("Rakesh RajPurohit","36 China Town","Jodhpur","Rajasthan","India","9999999999");
    Session *customer2=new Customer("Ashutosh Vyas","Tilawara","Jaipur","Rajasthan","India","8989898989");
    Session *customer3=new Customer("Srinivas Vaidhya","IIIT B","Bangalore","Karnataka","India","9867543423");
	
	cSessionFactory sf;
	
	sf.openSession();
	
	sf.save(s1);
	sf.save(s2);
	
	//sf.save(customer1);
	//sf.save(customer2);
	//sf.save(customer3);
	
	//update function
    ((Customer *)customer1)->setname("Rakesh");
	sf.update(customer1,"Customer_ID","1");
	
	sf.close();
	return 0;	
}
