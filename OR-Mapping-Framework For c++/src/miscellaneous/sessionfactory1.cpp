#include<stdio.h>
#include "mySqlConnectivity.h"
#include<vector>
#include<string>
#include<stdlib.h>
#include<typeinfo>
#include<sstream>
#include "XmlParser.h"

#include<iostream>
using namespace std;


extern vector<string> classname;
extern vector<string> tablename;
extern vector<string> propertyname;
extern vector<string> columnName;
extern vector<string> type;
 
static string url;
using namespace std;

class Session{
 public:
	string virtual serialize()=0; 	
};

class cSessionFactory
{
 public:
	
     void openSession(){ 
	XmlParser xparser;
	
		xparser.dump_to_stdout("employee.hbm.xml");
	
	cout<<"value of class size="<<classname.size();
	cout<<"value of table size="<<tablename.size();
	cout<<"value of property size="<<propertyname.size();
	cout<<"value of column size="<<columnName.size();
	string strdb ("create table ");
	string s=tablename[0];
	 url = strdb + s+"(";
	for(int i=0;i<columnName.size();i++){
		if(type[i]=="int"){
			if(i==columnName.size()-1){
				url=url+columnName[i]+" INT";
			}
			else
				url=url+columnName[i]+" INT,";	
		}
		else if(type[i]=="string"){
			
			if(i==(columnName.size()-1)){
				url=url+columnName[i]+" VARCHAR(100)";
			}
			else
				url=url+columnName[i]+" VARCHAR(100),";
		
		}
	}
        url=url+")"+";";
	//allocate the memory
	char *ch = new char[url.length()+1];
	strcpy(ch,url.c_str());
	//string s=tablename[0];
	cout<<"name of the table="<<url<<endl;



}

void save(Session *s){
  string s1 =typeid(*s).name(),token;
  string obj=s1.substr(1);
  cout<<"typeid of s is="<<obj<<endl;
  string str = s->serialize();
  cout<<"String is= "<<str<<endl;


  //cout<<"name of the employee is ="<<obj.getid()<<endl;
  MYSQL *conn;      // the connection
  MYSQL_RES *res;   // the results
  MYSQL_ROW row;    // the results row (line by line)

  struct connection_details mysqlD;
  mysqlD.server = "localhost";  // where the mysql database is
  mysqlD.user = "root";     // the root user of mysql   
  mysqlD.password = "root"; // the password of the root user in mysql
  mysqlD.database = "test";    // the databse to pick

  // connect to the mysql database
  mySqlConnectivity conMysqlObj;
  conn = conMysqlObj.mysql_connection_setup(mysqlD);
  
  
  // assign the results return to the MYSQL_RES pointer
  res = conMysqlObj.mysql_perform_query(conn, "create database Employee;");
  res= conMysqlObj.mysql_perform_query(conn,"use Employee;");

  char *c = new char[url.length()+1];
   strcpy(c,url.c_str());
   cout<<"value of url====================="<<c<<endl;
  res=conMysqlObj.mysql_perform_query(conn,c);
  res= conMysqlObj.mysql_perform_query(conn,"show tables;");
 
  printf("MySQL Tables in mysql database:\n");
  while ((row = mysql_fetch_row(res)) !=NULL)
      printf("%s\n", row[0]);
   // clean up the database result set 
  //mysql_free_result(res);
  // clean up the database link 
 // mysql_close(conn);



int id;
string firstname,lastname,birthdate,cellphone;
//id=employee.getid();
//firstname=employee.getfirstname();
//lastname=employee.getlastname();
//birthdate=employee.getbirthdate();
//cellphone=employee.getcellphone();
//string insert=; 
int i;
string Insert ="INSERT INTO ";
Insert= Insert+obj+" (";
for(i=0;i<columnName.size();i++){
	if(i==columnName.size()-1){
		Insert = Insert+columnName[i]+") VALUES (";
	}
	else {
		Insert=Insert+columnName[i]+",";
	}

}
istringstream iss(str);
int count=0;
while ( getline(iss, token, ',') )
	{
		if(count==type.size()-1){
			if(type[count]=="int"){		
				Insert=Insert+token;
				count++;
				
				continue;			
			}
			else if(type[count]=="string"){
				Insert=Insert+"'"+token+"'";
				count++;
				
				continue;
			}
		}
		else if(count<type.size()-1){
			if(type[count]=="int"){		
				Insert=Insert+token+",";
				count++;
				continue;			
			}
			else if(type[count]=="string"){
				Insert=Insert+"'"+token+"'"+",";
				count++;
				continue;
			}
		}
	}
Insert = Insert+");";
char *chr = new char[Insert.length()+1];
 strcpy(chr,Insert.c_str());
cout<<"Insert is="<<Insert<<endl;
//res=conMysqlObj.mysql_perform_query(conn,"INSERT INTO Employee (ID,Firstname,Lastname,Birthdate,Cellphone) VALUES ( 1,'siddhesh','dosi','23-08-1990','9001156287');");
res=conMysqlObj.mysql_perform_query(conn,chr);
//while ((row = mysql_fetch_row(res)) !=NULL)
      //printf("%s\n", row[0]);
   // clean up the database result set 
  mysql_free_result(res);
  // clean up the database link 
  mysql_close(conn);

}
};
