#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>
#include<stdlib.h>
#include<typeinfo>
#include<sstream>
#include "mySqlConnectivity.h"
#include "XmlParser.h"
#include"Session.h"
#include"Sessionfactory.h"

using namespace std;
extern vector<string> classname;
extern vector<string> tablename;
extern vector<string> one_to_one;
extern vector<bool> one_to_one_constrained;
extern vector<string> generator;
extern vector<vector<string> > foreign_key;
extern vector<vector<string> > foreign_key_type; 
extern vector<vector<string> > propertyname;
extern vector<vector<string> > columnName;
extern vector<vector<string> > type;
extern vector<vector<string> > NotNull;
extern vector<vector<string> > unique;
extern vector<vector<string> > Default;

//update for inheritance

extern vector<string>subclass;
extern vector<string>extend;
extern vector<vector<string> >disc_value;
extern vector<string>disc_column;
extern vector<string>disc_column_type;
extern vector<vector<string> >subcolumnName;
extern vector<vector<string> >subtype;
vector<string> disc_value_v1;
//end update for inheritance


/* for one_to_many and many_to_one variable declaratioon */
extern vector<string> many_to_one_key;
extern vector<string> many_to_one;
extern vector<string> set;
extern vector<string> set_key;
//-----------------------------------


//udate for m2m here
extern vector<string> m2m_classname;
extern vector<string> m2m_columnName;
extern vector<string> m2m_foreignkey;
extern vector<string> m2m_tablename;


vector<string>createtable_m2m;
vector<string> already_created;
vector<string> create_m2m_v;
vector<string>create_m2m_url;
vector<string> Insert_m2m;
vector<string> str_m2m;
vector<string> tok_m2m;
//end udate for m2m here


extern string server;
extern string user;
extern string password;
extern string database; 

//for xml mapping file
extern vector<string>mappingfile;

static string url;
vector<string> create;
int createdatabase_num=0;
string prev_obj="?00?";
  MYSQL *conn;      // the connection
  MYSQL_RES *res;   // the results
  MYSQL_ROW row;    // the results row (line by line)


 void cSessionFactory::openSession(){ 
	XmlParser xparser;
	    xparser.dump_to_stdout("hibernate.cfg.xml");

		for(int map=0;map<mappingfile.size();map++){
			
			char *ch = new char[mappingfile[map].length()+1];
			strcpy(ch,mappingfile[map].c_str());
			xparser.dump_to_stdout(ch);
		}
		//xparser.dump_to_stdout("employee.hbm.xml");
		//xparser.dump_to_stdout("certificate.hbm.xml");
		//xparser.dump_to_stdout("employeeDetails.hbm.xml");
		//xparser.dump_to_stdout("person.hbm.xml");
		//xparser.dump_to_stdout("meeting.hbm.xml");
		//xparser.dump_to_stdout("customer.hbm.xml");		
		//xparser.dump_to_stdout("meeting.hbm.xml");
		//xparser.dump_to_stdout("chair.hbm.xml");
		
		
	
/* to print one to many many to one values */
for(int i =0;i<tablename.size();i++)
{
cout<<"table name="<<tablename[i]<<endl;
cout<<"value of many_to_one key="<<many_to_one_key[i]<<endl;
cout<<"value of one_to_many set key ="<<set_key[i]<<endl;
}
//----------- end print o2m and m2o----------------

	
		
		
/*	cout<<"value of mapping file"<<mappingfile.size()<<endl;	
	cout<<"vaue of m2m_classname"<<m2m_classname.size()<<endl;
	cout<<"vaue of m2m_columnName"<<m2m_columnName.size()<<endl;
	cout<<"vaue of m2m_foreignkey"<<m2m_foreignkey.size()<<endl;
	cout<<"vaue of m2m_tablename"<<m2m_tablename.size()<<endl;	
	cout<<"value of disc_column size="<<disc_column.size()<<endl;
	cout<<"value of subcolumn is="<<subtype[0][0]<<endl;
	cout<<"value of disc_value size="<<disc_value[0].size()<<endl;
	cout<<"value of extend size="<<extend.size()<<endl;
	cout<<"value of subclass size"<<subclass[1]<<endl;
	cout<<"value of class size="<<classname.size()<<endl;
	cout<<"value of table size="<<tablename.size()<<endl;
	cout<<"cloumn size="<<columnName[0].size()<<endl;
	cout<<"type[2].size() is="<<type[0].size()<<endl;
	cout<<"value of one_to_one size="<<one_to_one.size()<<endl;
	cout<<"value of one_to_one_constrained size="<<one_to_one_constrained.size()<<endl;
	cout<<"value of foreign_key size = "<<foreign_key[1].size()<<endl;
	cout<<"value of property size="<<propertyname[0].size()<<endl;
	cout<<"value of column size="<<columnName[0].size()<<endl;
	cout<<"value of NotNull size="<<NotNull[0].size()<<endl;
	cout<<"value of unique size="<<unique[0].size()<<endl;
	cout<<"Value of Default size="<<Default[0].size()<<endl;
	cout<<"Value of generator= "<<generator[0]<<endl; */
	//cout<<"user= "<<user<<endl;
	//cout<<"server= "<<server<<endl;
	//cout<<"password= "<<password<<endl;
	//cout<<"database= "<<database<<endl;
	string strdb ("create table ");
	//string s=tablename[0];
	// url = strdb + s+"(";
    for(int j=0;j<tablename.size();j++){
	string s=tablename[j];
	url = strdb + s+"(";
	//cout<<"here";
	for(int i=0;i<columnName[j].size();i++){
		
		if(type[j][i]=="int"){
			url=url+columnName[j][i]+" INT";
			if(i==columnName[j].size()-1){
				
				if(NotNull[j][i]=="T"){
					url=url+" NOT NULL";

				}
				if(j<generator.size()){
					if(generator[j]==columnName[j][i]){
						url= url+" NOT NULL AUTO_INCREMENT";
					}
				}
				if(unique[j][i]=="T"){
					url=url+" UNIQUE";

				}
				if( Default[j][i] =="Null" || Default[j][i] == "null" || Default[j][i]== "NULL"){
					url = url+" DEFAULT "+"NULL";
				}
				else if(Default[j][i] != "?00?" ){
					url = url+" DEFAULT "+"'"+Default[j][i]+"'";
				}
				
			}
			else{
				if(NotNull[j][i]=="T"){
					url=url+" NOT NULL";
				}

				if(j<generator.size()){
					if(generator[j]==columnName[j][i]){
						url= url+" NOT NULL AUTO_INCREMENT";
					}
				}
				if(unique[j][i]=="T"){
					url=url+" UNIQUE";
				}
				if( Default[j][i] == "Null" || Default[j][i] == "null" || Default[j][i]== "NULL"){
					url = url+" DEFAULT "+"NULL";
				}
				else if(Default[j][i] != "?00?" ){
					url = url+" DEFAULT "+"'"+Default[j][i]+"'";
				}
			
				url=url+", ";					

			}	
		}
		else if(type[j][i]=="string"){
			url=url+columnName[j][i]+" VARCHAR(100)";
			if(i==(columnName[j].size()-1)){

				if(NotNull[j][i]=="T"){
					url=url+" NOT NULL";

				}
				if(j<generator.size()){
					if(generator[j]==columnName[j][i]){
						url =url+" NOT NULL AUTO_INCREMENT";
					}
				}
				if(unique[j][i]=="T"){
					url=url+" UNIQUE";

				}
				if(Default[j][i] == "Null" || Default[j][i] == "null" || Default[j][i] == "NULL"){
					url = url+" DEFAULT "+"NULL";
				}
				else if(Default[j][i] != "?00?" ){
					url = url+" DEFAULT "+"'"+Default[j][i]+"'";
				}
			}
			else{
				if(NotNull[j][i]=="T"){
					url=url+" NOT NULL ";
				}

				if(j<generator.size()){
					if(generator[j]==columnName[j][i]){
						url= url+" NOT NULL AUTO_INCREMENT";
					}
				}
				if(unique[j][i]=="T"){
					url=url+" UNIQUE ";
				}
				if( Default[j][i] == "Null" || Default[j][i] == "null" || Default[j][i] == "NULL"){
					url = url+" DEFAULT "+"NULL";
				}
				else if(Default[j][i] != "?00?" ){
					url = url+" DEFAULT "+"'"+Default[j][i]+"'";
				}
				url=url+", ";		
			}
		
		}
	} //for loop end i=0
	

	//update for inheritance
	vector<string> check_dbl;
	vector<string> check_dbltype;
	int num=0;
	
	for(int a =0 ; a<extend.size() ; a++){

		if(classname[j]==extend[a]){
			for(int b=0 ; b< subcolumnName[a].size();b++){
				bool sub_flage=true;
				if(num==0){
					check_dbl.push_back(subcolumnName[a][b]);
					check_dbltype.push_back(subtype[a][b]);
					num++;
				}
				else{
					for(int t =0 ;t<check_dbl.size();t++){
						if(check_dbl[t]==subcolumnName[a][b]){
							sub_flage=false;
						}
					}//end for loop t
					if(sub_flage==true){
						check_dbl.push_back(subcolumnName[a][b]);
						check_dbltype.push_back(subtype[a][b]);
					}
				}
				//if(subtype[a][b]=="string"){
					//url = url+", "+subcolumnName[a][b]+" VARCHAR(100) NULL DEFAULT NULL ";
				//}

				//if(subtype[a][b]=="int"){
					//url = url+", "+subcolumnName[a][b]+" INT NULL DEFAULT NULL ";
				//}
			}// end for loop b
		} 

	} //end for loop a
	
	for(int a=0;a<check_dbl.size();a++){
		if(check_dbltype[a]=="string"){
			url = url+", "+check_dbl[a]+" VARCHAR(100) NULL DEFAULT NULL ";
		}

		if(check_dbltype[a]=="int"){
			url = url+", "+check_dbl[a]+" INT NULL DEFAULT NULL ";
		}
	
	}
	check_dbl.clear();
	check_dbltype.clear();
	if(disc_column[j]!="?00?"){
		if(disc_column_type[j]=="int"){
			url=url+", "+disc_column[j]+" INT NOT NULL ";
		}
		else{
			url=url+", "+disc_column[j]+" VARCHAR(100) NOT NULL ";
		}
	}
       //end update for inheritance
	if(j<generator.size()){
		url=url+", PRIMARY KEY "+"("+generator[j]+")";
	}
	int pk=0;
	//cout<<"one_to_one is"<<one_to_one[j]<<endl;
	
	//making work for one to one
	if(one_to_one[j] != "?00?"){
		
		if(one_to_one_constrained[j]==1){
			
			for(int k=0;k<tablename.size();k++){
				if(tablename[k]==one_to_one[j]){
					pk=k;
					break;
				}
			}
			if(foreign_key[j][0]!="?00?"){
				
				if(foreign_key_type[j][0]=="string"){
					url=url+", CONSTRAINT 'FK' FOREIGN KEY ( '"+foreign_key[j][0]+"' ) REFERENCES '"
						+one_to_one[j]+"' ( '"+generator[pk]+"' ) ON DELETE CASCADE ON UPDATE CASCADE";
				}
				if(foreign_key_type[j][0]=="int"){
					url=url+", CONSTRAINT FOREIGN KEY ("+foreign_key[j][0]+") REFERENCES "
						+one_to_one[j]+"("+generator[pk]+") ON DELETE CASCADE ON UPDATE CASCADE";
				}						
			}
		}
	}
	//end for working on one to one
	
	
	//-------------- m2o--------------------
	if(many_to_one[j] != "?00?"){
		int k;
		
		//cout<<"in many_to_one"<<endl;
		//if(many_to_one_constrained[j]==1){//one_to_one
			
			for(k=0;k<tablename.size();k++){
				if(columnName[j][k]==many_to_one_key[j]){
					//cout<<"in many_to_one_k"<<endl;
					break;
				}
			}
			if(columnName[j][k]!="?00?"){
				
				if(type[j][k]=="string"){
					url=url+", CONSTRAINT FOREIGN KEY ("+many_to_one_key[j]+") REFERENCES "
						+many_to_one[j]+" ("+many_to_one_key[j]+") ON DELETE CASCADE ON UPDATE CASCADE ";
				}
				if(type[j][k]=="int"){
					url=url+", CONSTRAINT FOREIGN KEY ("+many_to_one_key[j]+") REFERENCES "
						+many_to_one[j]+" ("+many_to_one_key[j]+") ON DELETE CASCADE ON UPDATE CASCADE ";
				}						
			}
		//}
		//url=url+")"+";";
	//cout<<url<<endl;
	//create.push_back(url); 
	  //}
        } //if many to one 
    
	
	
//----------- end m20 and o2m---------- 
	
	
	url=url+")"+";";
	create.push_back(url);
	
	//start creating query for many to many mapping
	string create_m2m="CREATE TABLE ";
	
	int m2m_pk;
	bool check_m2m_table=false,isInt1=false,isInt2=false;
	if(m2m_tablename[j] !="?00?"){
		
		for(int q=0;q<createtable_m2m.size();q++){
				if(m2m_tablename[j]==createtable_m2m[q]){
					check_m2m_table=true;
				}
		}
		if(check_m2m_table==false){
			createtable_m2m.push_back(m2m_tablename[j]);
		}
	}
	//cout<<"check_m2m_table is = "<<check_m2m_table<<createtable_m2m.size()<<endl;
	if(m2m_tablename[j] !="?00?" && check_m2m_table==false){
		
		create_m2m= create_m2m + m2m_tablename[j]+" (";
			for(int p=0;p<columnName[j].size();p++){
				
				if(columnName[j][p]==m2m_foreignkey[j]){
					if(type[j][p]=="int" ){
						create_m2m= create_m2m+m2m_foreignkey[j]+" INT NOT NULL,";
						isInt1=true;
					}
					if(type[j][p]=="string"){
						create_m2m= create_m2m+"'"+m2m_columnName[j]+"'"+" VARCHAR(100) NOT NULL";
					}
					
				}
			}//-----------------end for loop p-------------------------
			string mapClassname_m2m=m2m_classname[j];
			//cout<<"name of the current table is = "<<tablename[j]<<endl;
			for(int p=0;p<classname.size();p++){
				
					if(classname[p]==m2m_classname[j]){
						for(int r=0;r<columnName[p].size();r++){
							if(columnName[p][r]==m2m_columnName[j]){
								m2m_pk=p;
								
								if(type[p][r]=="int"){
									create_m2m= create_m2m+m2m_columnName[j]+" INT NOT NULL";
									isInt2=true;
								}
								if(type[p][r]=="string"){
									create_m2m= create_m2m+"'"+m2m_columnName[j]+"'"+" VARCHAR(100) NOT NULL";
								}
								
							}
							
						}//end r loop
					}//end if
				
				
			}//end p loop
			if(isInt1==true && isInt2==true){
				create_m2m=create_m2m+", PRIMARY KEY ("+m2m_foreignkey[j]+","+m2m_columnName[j]+")";
			}
			if(isInt1==true && isInt2==false){
				create_m2m=create_m2m+", PRIMARY KEY ("+m2m_foreignkey[j]+","+"'"+m2m_columnName[j]+"'"+")";
			}
			if(isInt1==false && isInt2==true){
				create_m2m=create_m2m+", PRIMARY KEY ("+"'"+m2m_foreignkey[j]+"'"+","+m2m_columnName[j]+")";
			}
			if(isInt1==false && isInt2==false){
				create_m2m=create_m2m+", PRIMARY KEY ("+"'"+m2m_foreignkey[j]+"'"+","+"'"+m2m_columnName[j]+"'"+")";
			}
			
			
			
				
			if(isInt1==true && isInt2==true){
				create_m2m=create_m2m+", CONSTRAINT FOREIGN KEY ("+m2m_foreignkey[j]+") REFERENCES "+tablename[j]+" ("+m2m_foreignkey[j]+") ON DELETE CASCADE ON UPDATE CASCADE,"+
			                                  " CONSTRAINT FOREIGN KEY ("+m2m_columnName[j]+") REFERENCES "+tablename[m2m_pk]+" ("+m2m_columnName[j]+") ON DELETE CASCADE ON UPDATE CASCADE "+");";
			}
			if(isInt1==true && isInt2==false){
				create_m2m=create_m2m+", CONSTRAINT FOREIGN KEY ("+m2m_foreignkey[j]+") REFERENCES "+tablename[j]+" ("+m2m_foreignkey[j]+") ON DELETE CASCADE ON UPDATE CASCADE ,"+
			                                  " CONSTRAINT FOREIGN KEY ("+m2m_columnName[j]+") REFERENCES "+tablename[m2m_pk]+" ('"+m2m_columnName[j]+"') ON DELETE CASCADE ON UPDATE CASCADE "+");";
			}	
			if(isInt1==false && isInt2==true){
				create_m2m=create_m2m+", CONSTRAINT FOREIGN KEY ('"+m2m_foreignkey[j]+"') REFERENCES "+tablename[j]+" ("+m2m_foreignkey[j]+") ON DELETE CASCADE ON UPDATE CASCADE ,"+
			                                  " CONSTRAINT FOREIGN KEY ("+m2m_columnName[j]+") REFERENCES "+tablename[m2m_pk]+" ("+m2m_columnName[j]+") ON DELETE CASCADE ON UPDATE CASCADE"+");";
			}
			if(isInt1==false && isInt2==false){
				create_m2m=create_m2m+", CONSTRAINT FOREIGN KEY ('"+m2m_foreignkey[j]+"') REFERENCES "+tablename[j]+" ("+m2m_foreignkey[j]+") ON DELETE CASCADE ON UPDATE CASCADE ,"+
			                                  " CONSTRAINT FOREIGN KEY ("+m2m_columnName[j]+") REFERENCES "+tablename[m2m_pk]+" ('"+m2m_columnName[j]+"') ON DELETE CASCADE ON UPDATE CASCADE "+");";
			}							
	 // cout<<"000000000000000000 m2m create is = "<<create_m2m<<endl;
	  create_m2m_v.push_back(tablename[j]);
	  create_m2m_v.push_back(tablename[m2m_pk]);
	  
	  create_m2m_url.push_back(create_m2m);
	  create_m2m_url.push_back(create_m2m);
	 
	  
	  
	}//end if of m2m_tablename 
	
	
	//end creating query for many to many mapping
	
	
	


	
	
	
     } //for loop end j=0
       // url=url+")"+";";
       for(int i=0;i<create.size();i++){
		   cout<<"table "<<tablename[i]<<"\n No ="<<i<<"\n create query is= "<<create[i]<<endl;
		   
	   }
       
	//allocate the memory
	char *ch = new char[url.length()+1];
	strcpy(ch,url.c_str());
	//string s=tablename[0];
	//cout<<"name of the table="<<url<<endl;
	//cout<<"ctreate is="<<create[0]<<"\n"<<create.size()<<endl;
//--------------------update for inheritance--------------------------------------------------------------
	for(int x=0;x<classname.size();x++){
		for(int y=0;y<disc_value[x].size();y++){
			if(disc_value[x][y]!="?00?" && y!=0){
				disc_value_v1.push_back(disc_value[x][y]);
			}

		}//end loop y

	}//end for loop x
//cout<<"size of the disc_value_v1 ="<<disc_value_v1.size()<<endl;
//------------------end update for inheritance---------------------------------------------------------------
	
} // end openSession



//*******************save method is statring here*********************//



void cSessionFactory::save(Session *s){
  int k,counter,t=0,d;
  string s1 =typeid(*s).name(),token;
  bool already_created_flage=false;
  for(d=0;d<s1.length();d++){
	
	if(s1[t]=='0'||s1[t]=='1'||s1[t]=='2'||s1[t]=='3'||s1[t]=='4'||s1[t]=='5'||s1[t]=='6'||s1[t]=='7'||s1[t]=='8'||s1[t]=='9'){
		t++;
		
	}
  }
  string obj=s1.substr(t);
  cout<<"typeid of s is="<<obj<<endl;

//------------------------------update for inheritance------------------------------
	bool flage_for_subclass=false;
	int subclass_counter=0;	
	for(d=0;d<subclass.size();d++){
		if(subclass[d]==obj){
			obj=extend[d];
			subclass_counter=d;
			flage_for_subclass=true;
		}

	}

//------------------------------end update for inheritance---------------------------------
  for(k=0;k<classname.size();k++){
	if(classname[k]==obj){
		counter=k;
		break;
	}
  }
string str = s->serialize();
  cout<<"String is= "<<str<<"  counter is="<<counter<<endl;
  
  char *cs = new char[server.length()+1];
  char *cu = new char[user.length()+1];
  char *cp = new char[password.length()+1];
  char *cd = new char[database.length()+1];
   strcpy(cs,server.c_str());
    strcpy(cu,user.c_str());
   strcpy(cp,password.c_str());
    strcpy(cd,database.c_str());
  struct connection_details mysqlD;
  mysqlD.server = cs;  // where the mysql database is
  mysqlD.user = cu;     // the root user of mysql   
  mysqlD.password =cp; // the password of the root user in mysql
  mysqlD.database = cd;    // the databse to pick

  // connect to the mysql database
  mySqlConnectivity conMysqlObj;
  conn = conMysqlObj.mysql_connection_setup(mysqlD);
  
//____________________code for one to one mapping_______________________//
	if(foreign_key[counter][0]!="?00?"){
		cout<<"-------------------------------"<<foreign_key[counter][0]<<"*********"<<one_to_one[counter]<<"------------"<<classname[counter]<<endl;
		int pk;
		string primary_key;
		Session *session= s->getobj();
		string str_one_to_one = session->serialize();
		for(int i=0 ;i<tablename.size();i++){
			if(tablename[i]==one_to_one[counter] || classname[i]==one_to_one[counter]){
				pk = i;
				break;
				
			}
		} //end for loop i
		
		primary_key= generator[pk];
		string tok_1;
		istringstream is(str_one_to_one);
		vector<string> tok_one_to_one;
		while (getline(is,tok_1,',')){
			tok_one_to_one.push_back(tok_1);

		}
		int w=0;
		string retrieve= "SELECT "+primary_key+" FROM "+tablename[pk]+" WHERE ";
		for(int i=0;i<columnName[pk].size();i++){
			if(primary_key==columnName[pk][i] && tok_one_to_one.size() < columnName[pk].size()){
				 continue;
			}
			if(i== columnName[pk].size()-1 && type[pk][i]=="string"){
					retrieve=retrieve+columnName[pk][i]+"= "+"'"+tok_one_to_one[w++]+"'"+";";
			}
			else if(i== columnName[pk].size()-1 && type[pk][i]=="int"){
					retrieve=retrieve+columnName[pk][i]+"= "+tok_one_to_one[w++]+";";
			}
			else if(type[pk][i]=="int")
			
					retrieve=retrieve+columnName[pk][i]+"= "+tok_one_to_one[w++]+" AND ";
					
			else
			        retrieve=retrieve+columnName[pk][i]+"= "+"'"+tok_one_to_one[w++]+"'"+" AND ";
		}//end for loop i
		cout<<"select query for one to one is="<<retrieve<<endl;
		tok_one_to_one.clear();
		char *chr = new char[retrieve.length()+1];
		strcpy(chr,retrieve.c_str());
		
		//MYSQL_RES *res_set;
		//MYSQL_ROW row;
		//mysql_query (conn,chr);
		//unsigned int i =0;
		res= conMysqlObj.mysql_perform_query(conn,"use hibernate_db;");
		res=conMysqlObj.mysql_perform_query(conn,chr);
		//res_set = mysql_store_result(conn);
		cout<<"numrows is="<<endl;
		//unsigned int numrows = mysql_num_rows(res_set);
		vector<string> resultvalue;
		while (((row= mysql_fetch_row(res)) !=NULL ))
		{ //cout<<" %s\n",row[i] !=NULL?row[i] : "NULL";
			resultvalue.push_back(row[0]);
			cout <<"\t | \t" << row[0] << "\t | \t";
			//cout <<  row[i+1] <<  "\t |"<< endl;
			//cout<<row[i+2]<<"\t |"<<endl;
		}//end while loop
		for(int i=0;i<resultvalue.size();i++){
			str=resultvalue[i]+","+str;
		}
		cout<<"update str is="<<str<<endl; 
		resultvalue.clear();
	}// end if of foreign key


//____________________end code for one to one mapping___________________//
  

		//-----------------------------------making work on many to one here----------------------------------------------
		if(many_to_one[counter]!="?00?"){
			
		int pk_m2m;
		//string primary_key;
		Session *session= s->getobj();
		string str_mtom = session->serialize();
		for(int i=0 ;i<tablename.size();i++){
			if(tablename[i]==many_to_one[counter]){
				pk_m2m = i;
				break;
				
			}
		} //end for loop i
		
		//primary_key= generator[pk];
		string tok_m2o;
		istringstream is(str_mtom);
		vector<string> tok_mtom;
		while (getline(is,tok_m2o,',')){
			tok_mtom.push_back(tok_m2o);

		}
		int w=0;
		int m2m_col;
		string retrieve_m2m= "SELECT "+many_to_one_key[counter]+" FROM "+tablename[pk_m2m]+" WHERE ";
		for(int i=0;i<columnName[pk_m2m].size();i++){
			if(many_to_one_key[counter]==columnName[pk_m2m][i]){
				m2m_col=i;
			}
			if(many_to_one_key[counter]==columnName[pk_m2m][i] && tok_mtom.size() < columnName[pk_m2m].size()){
				 continue;
			}
			if(i== columnName[pk_m2m].size()-1 && type[pk_m2m][i]=="string"){
					retrieve_m2m=retrieve_m2m+columnName[pk_m2m][i]+"= "+"'"+tok_mtom[w++]+"'"+";";
			}
			else if(i== columnName[pk_m2m].size()-1 && type[pk_m2m][i]=="int"){
					retrieve_m2m=retrieve_m2m+columnName[pk_m2m][i]+"= "+tok_mtom[w++]+";";
			}
			else if(type[pk_m2m][i]=="int")
			
					retrieve_m2m=retrieve_m2m+columnName[pk_m2m][i]+"= "+tok_mtom[w++]+" AND ";
					
			else
			        retrieve_m2m=retrieve_m2m+columnName[pk_m2m][i]+"= "+"'"+tok_mtom[w++]+"'"+" AND ";
		}//end for loop i
		cout<<"select query for many to one is="<<retrieve_m2m<<endl;
		tok_mtom.clear();
		char *chr = new char[retrieve_m2m.length()+1];
		strcpy(chr,retrieve_m2m.c_str());
		
		//MYSQL_RES *res_set;
		//MYSQL_ROW row;
		//mysql_query (conn,chr);
		//unsigned int i =0;
		res= conMysqlObj.mysql_perform_query(conn,"use hibernate_db;");
		res=conMysqlObj.mysql_perform_query(conn,chr);
		//res_set = mysql_store_result(conn);
		//cout<<"numrows is="<<endl;
		//unsigned int numrows = mysql_num_rows(res_set);
		vector<string> resultvalue_m2m;
		while (((row= mysql_fetch_row(res)) !=NULL ))
		{ //cout<<" %s\n",row[i] !=NULL?row[i] : "NULL";
			resultvalue_m2m.push_back(row[m2m_col]);
			cout <<"\t | \t" << row[0] << "\t | \t";
			//cout <<  row[i+1] <<  "\t |"<< endl;
			//cout<<row[i+2]<<"\t |"<<endl;
		}//end while loop
		for(int i=0;i<resultvalue_m2m.size();i++){
			str=str+","+resultvalue_m2m[i];
		}
		cout<<"update str is for many to on="<<str<<endl; 
		resultvalue_m2m.clear();
			
		}//end if condition for many to many 
  
		//end making work on many to one here
  
  //MYSQL *conn;      // the connection
  //MYSQL_RES *res;   // the results
  //MYSQL_ROW row;    // the results row (line by line)

  
  
  
  // assign the results return to the MYSQL_RES pointer
  if(createdatabase_num==0){
	res = conMysqlObj.mysql_perform_query(conn,"drop schema hibernate_db;");
	cout<<"database drope successfully"<<endl;
  	res = conMysqlObj.mysql_perform_query(conn, "create database hibernate_db;");
	cout<<"database created successfully"<<endl;
	createdatabase_num++;
  }
  res= conMysqlObj.mysql_perform_query(conn,"use hibernate_db;");
  url = create[counter];
 cout<<"url is="<<url<<endl;
  char *c = new char[url.length()+1];
   strcpy(c,url.c_str());
   cout<<"value of url====================="<<c<<endl;
   
   
for(int i=0;i<already_created.size();i++){
	if(already_created[i]==tablename[counter]){
		already_created_flage=true;
	}
}
  if(already_created_flage==false){
  	res=conMysqlObj.mysql_perform_query(conn,c);
	prev_obj=obj;
	already_created.push_back(tablename[counter]);
  }
  already_created_flage=false;
  res= conMysqlObj.mysql_perform_query(conn,"show tables;");
 
  printf("MySQL Tables in mysql database:\n");
  while ((row = mysql_fetch_row(res)) !=NULL)
      printf("%s\n", row[0]);
   // clean up the database result set 
  //mysql_free_result(res);
  // clean up the database link 
 // mysql_close(conn);
 
 
 
//***************************************************************work on many to many start*********************************************************//
int counter_m2m;
string url_m2m;
if(m2m_classname[counter] != "?00?"){
	for(int i=0;i<m2m_classname.size();i++){
		if(m2m_classname[counter]==classname[i]){
			counter_m2m=i;
			break;
		}
		
	}
	url_m2m=create[counter_m2m];
	cout<<"###############################______________---------------"<<create[counter_m2m]<<endl;
	char *c_m2m = new char[url_m2m.length()+1];
    strcpy(c_m2m,url_m2m.c_str());
    for(int i=0;i<already_created.size();i++){
		if(already_created[i]==tablename[counter_m2m]){
			already_created_flage=true;
		}
	}
	if(already_created_flage==false){
		res=conMysqlObj.mysql_perform_query(conn,c_m2m);
		already_created.push_back(tablename[counter_m2m]);
	}
	already_created_flage=false;
	for(int i =0;i<create_m2m_v.size();i++){
		for(int j=0;j<already_created.size();j++){
			if(already_created[j]==m2m_tablename[counter]){
				already_created_flage=true;
			}
		}
		if(tablename[counter]==create_m2m_v[i] && already_created_flage==false){
			cout<<"create of the metting_employee is ="<<create_m2m_url[i]<<endl;
			char *c_m2m = new char[create_m2m_url[i].length()+1];
			strcpy(c_m2m,create_m2m_url[i].c_str());
			res=conMysqlObj.mysql_perform_query(conn,c_m2m);
			already_created.push_back(m2m_tablename[counter]);
			already_created_flage=false;
		}
		
	}
	//making insert query for many to many table (meeting table)
		
		//string insert_m2m="INSERT INTO "+m2m_classname[counter]+" ("+m2m_columnName[counter]+","+m2m_columnName[counter_m2m]+") VALUES (";
		int counter_1;
		for(int i = 0;i<classname.size();i++){
			if(classname[i]==m2m_classname[counter]){
				counter_1=i;
				break;
			}
		}
		
		vector<Session *>*se=s->getlistobj();
		//vector<string> str_m2m;
		//vector<string> tok_m2m;
		for(int i=0;i<(*se).size();i++){
			str_m2m.push_back((*se)[i]->serialize());
		}
		for(int h=0;h<str_m2m.size();h++){
			istringstream iss(str_m2m[h]);
			
			while (getline(iss,token,',')){
				tok_m2m.push_back(token);

			}
		
			string insert_m2m="INSERT INTO "+classname[counter_1]+" (";
			
			for(int i=0;i<columnName[counter_1].size();i++){
				if(generator[counter_1]==columnName[counter_1][i] && tok_m2m.size() != columnName[counter_1].size()){
					continue;
				}
				if(i==columnName[counter_1].size()-1){
					insert_m2m = insert_m2m+columnName[counter_1][i];
				}
				else {
					insert_m2m=insert_m2m+columnName[counter_1][i]+",";
				}

			}
			insert_m2m=insert_m2m+") VALUES (";
			int count=0;

			cout<<"size of the tok_m2m is"<<str_m2m.size()<<endl;

			for(int i=0;i<columnName[counter_1].size();i++){
				if(generator[counter_1]==columnName[counter_1][i] && tok_m2m.size()!=columnName[counter_1].size()){
					continue;
				}
				if(i==type[counter_1].size()-1){
					if(type[counter_1][i]=="int"){		
						insert_m2m=insert_m2m+tok_m2m[count];
				
						count++;
						continue;			
					}
					else if(type[counter_1][i]=="string"){
						insert_m2m=insert_m2m+"'"+tok_m2m[count]+"'";
						count++;
				
						continue;
					}
				}
				else if(i<type[counter_1].size()-1){
					if(type[counter_1][i]=="int"){		
						insert_m2m=insert_m2m+tok_m2m[count]+",";
						count++;
						continue;			
					}
					else if(type[counter_1][i]=="string"){
						insert_m2m=insert_m2m+"'"+tok_m2m[count]+"'"+",";
						count++;
						continue;
					}
				}

			} //end for loop
			insert_m2m=insert_m2m+");";
			Insert_m2m.push_back(insert_m2m);
			cout<<"insert_m2m is="<<insert_m2m<<endl;
			cout<<"Insert_m2m size is="<<Insert_m2m.size()<<endl;
			
		tok_m2m.clear();
	}// end for loop h here
	//end making inset query for many to many table
	
} //end if condtion for check m2m 





//***************************************************************end work on many to many************************************************************//




//id=employee.getid();
//firstname=employee.getfirstname();
//lastname=employee.getlastname();
//birthdate=employee.getbirthdate();
//cellphone=employee.getcellphone();
//string insert=; 
istringstream iss(str);
vector<string> tok;
while (getline(iss,token,',')){
	tok.push_back(token);

}
int i,j;

//***************************************insert query**********************************************************
string Insert ="INSERT INTO ";
Insert= Insert+tablename[counter]+" (";

for(i=0;i<columnName[counter].size();i++){
	if(generator[counter]==columnName[counter][i] && tok.size() != columnName[counter].size()){
		continue;
	}
	if(i==columnName[counter].size()-1){
		Insert = Insert+columnName[counter][i];
	}
	else {
		Insert=Insert+columnName[counter][i]+",";
	}

}


//----------------------update for inheritance------------------------------------------------
if(flage_for_subclass==true){
	Insert= Insert+",";
	for(i=0;i<subcolumnName[subclass_counter].size();i++){
		if(i==subcolumnName[subclass_counter].size()-1){
			Insert = Insert+subcolumnName[subclass_counter][i];
		}
		else {
			Insert = Insert+subcolumnName[subclass_counter][i]+",";
		}
	}
	
}

for(i=0;i<extend.size();i++){
	if(extend[i]==classname[counter]){
		Insert = Insert+", "+disc_column[counter];
		break;
	}
}
Insert=Insert+") VALUES (";


//-----------------------------------------end update for inheritance--------------------------------------------------------



//istringstream iss(str);
int count=0;

cout<<"size of the tok is"<<tok.size()<<endl;

for(i=0;i<columnName[counter].size();i++){
		if(generator[counter]==columnName[counter][i] && tok.size()!=columnName[counter].size()){
			continue;
  		}
 		if(i==type[counter].size()-1){
			if(type[counter][i]=="int"){		
				Insert=Insert+tok[count];
				
				count++;
				continue;			
			}
			else if(type[counter][i]=="string"){
				Insert=Insert+"'"+tok[count]+"'";
				count++;
				
				continue;
			}
		}
		else if(i<type[counter].size()-1){
			if(type[counter][i]=="int"){		
				Insert=Insert+tok[count]+",";
				count++;
				continue;			
			}
			else if(type[counter][i]=="string"){
				Insert=Insert+"'"+tok[count]+"'"+",";
				count++;
				continue;
			}
		}

} //end for loop

//--------------------------update for inhritance----------------------------------

if(flage_for_subclass==true){
	Insert=Insert+",";
	for(i=0;i<subcolumnName[subclass_counter].size();i++){
		
		if(i==subtype[subclass_counter].size()-1){
			if(subtype[subclass_counter][i]=="int"){		
				Insert=Insert+tok[count];
				
				count++;
				continue;			
			}
			else if(subtype[subclass_counter][i]=="string"){
				Insert=Insert+"'"+tok[count]+"'";
				count++;
				
				continue;
			}
		}
		else if(i<subtype[subclass_counter].size()-1){
			if(subtype[subclass_counter][i]=="int"){		
				Insert=Insert+tok[count]+",";
				count++;
				continue;			
			}
			else if(subtype[subclass_counter][i]=="string"){
				Insert=Insert+"'"+tok[count]+"'"+",";
				count++;
				continue;
			}
		}



	}

}

if(flage_for_subclass==false && disc_value[counter][0]!="?00?"){
	
	if(disc_column_type[counter]=="int"){
		Insert=Insert+","+disc_value[counter][0];
	}
	else{
		
		Insert=Insert+","+"'"+disc_value[counter][0]+"'";
	
	}

}
if(flage_for_subclass==true && disc_value[counter][0]!="?00?"){
	if(disc_column_type[counter]=="int"){
		Insert=Insert+","+disc_value_v1[subclass_counter];
	}
	else
		Insert=Insert+","+"'"+disc_value_v1[subclass_counter]+"'";

}

//------------------------------end update for inheritance-----------------------------------



Insert = Insert+");";
char *chr = new char[Insert.length()+1];
 strcpy(chr,Insert.c_str());
cout<<"Insert is="<<Insert<<endl;
//res=conMysqlObj.mysql_perform_query(conn,"INSERT INTO Employee (ID,Firstname,Lastname,Birthdate,Cellphone) VALUES ( 1,'siddhesh','dosi','23-08-1990','9001156287');");
res=conMysqlObj.mysql_perform_query(conn,chr);
//while ((row = mysql_fetch_row(res)) !=NULL)
      //printf("%s\n", row[0]);
   // clean up the database result set 
  //mysql_free_result(res);
  // clean up the database link 
  //mysql_close(conn);
  
  
  //store insert query for many to many
  if(m2m_classname[counter] != "?00?"){
	  for(int i=0 ; i<Insert_m2m.size();i++){
		  char *chr = new char[Insert_m2m[i].length()+1];
		  strcpy(chr,Insert_m2m[i].c_str());
		  res=conMysqlObj.mysql_perform_query(conn,chr);
	  }
	  
  
	/* change here*/                            Insert_m2m.clear();
	//make insert query for intermidiate table
	vector<string> Insert_m2m_inter;
	vector<string> resultvalue_m2m;
	for(int h=0;h<str_m2m.size();h++){
			istringstream iss(str_m2m[h]);
			
			while (getline(iss,token,',')){
				tok_m2m.push_back(token);

			}
	
		//string insert_m2m_inter="INSERT INTO "+m2m_tablename[counter]+" ("+m2m_columnName[counter]+","+m2m_columnName[counter_m2m]+") VALUES (";
		int w_m2m=0;
		string retrieve_m2m= "SELECT "+m2m_columnName[counter]+" FROM "+tablename[counter_m2m]+" WHERE ";
		for(int i=0;i<columnName[counter_m2m].size();i++){
			if(generator[counter_m2m]==columnName[counter_m2m][i] && tok_m2m.size() < columnName[counter_m2m].size()){
				 continue;
			}
			if(i== columnName[counter_m2m].size()-1 && type[counter_m2m][i]=="string"){
					retrieve_m2m=retrieve_m2m+columnName[counter_m2m][i]+"= "+"'"+tok_m2m[w_m2m++]+"'"+";";
			}
			else if(i== columnName[counter_m2m].size()-1 && type[counter_m2m][i]=="int"){
					retrieve_m2m=retrieve_m2m+columnName[counter_m2m][i]+"= "+tok_m2m[w_m2m++]+";";
			}
			else if(type[counter_m2m][i]=="int")
			
					retrieve_m2m=retrieve_m2m+columnName[counter_m2m][i]+"= "+tok_m2m[w_m2m++]+" AND ";
					
			else
			        retrieve_m2m=retrieve_m2m+columnName[counter_m2m][i]+"= "+"'"+tok_m2m[w_m2m++]+"'"+" AND ";
		}//end for loop i
		cout<<"select query for many to many is="<<retrieve_m2m<<endl;
		
		char *chr = new char[retrieve_m2m.length()+1];
		strcpy(chr,retrieve_m2m.c_str());
		
		//MYSQL_RES *res_set;
		//MYSQL_ROW row;
		//mysql_query (conn,chr);
		//unsigned int i =0;
		res= conMysqlObj.mysql_perform_query(conn,"use hibernate_db;");
		res=conMysqlObj.mysql_perform_query(conn,chr);
		//res_set = mysql_store_result(conn);
		cout<<"numrows is="<<endl;
		//unsigned int numrows = mysql_num_rows(res_set);
		
		while (((row= mysql_fetch_row(res)) !=NULL ))
		{ //cout<<" %s\n",row[i] !=NULL?row[i] : "NULL";
			resultvalue_m2m.push_back(row[0]);
			cout <<"\t | \t" << row[0] << "\t | \t";
			//cout <<  row[i+1] <<  "\t |"<< endl;
			//cout<<row[i+2]<<"\t |"<<endl;
		}//end while loop
		//for(int i=0;i<resultvalue_m2m.size();i++){
			//cout<<"resultvalue_m2m is ="<<resultvalue_m2m[i]<<endl;
		//}
		//cout<<"update str is="<<str<<endl; 
	//	resultvalue.clear();*/
		
		tok_m2m.clear();
	}//end for loop h	
		
		//select value from the table for m2m
		int w=0;
		string select_m2m="SELECT "+m2m_columnName[counter_m2m]+" FROM "+tablename[counter]+" WHERE ";
		for(int i=0;i<columnName[counter].size();i++){
			if(generator[counter]==columnName[counter][i] && tok.size() < columnName[counter].size()){
				 continue;
			}
			if(i== columnName[counter].size()-1 && type[counter][i]=="string"){
					select_m2m=select_m2m+columnName[counter][i]+"= "+"'"+tok[w++]+"'"+";";
			}
			else if(i== columnName[counter].size()-1 && type[counter][i]=="int"){
					select_m2m=select_m2m+columnName[counter][i]+"= "+tok[w++]+";";
			}
			else if(type[counter][i]=="int")
			
					select_m2m=select_m2m+columnName[counter][i]+"= "+tok[w++]+" AND ";
					
			else
			        select_m2m=select_m2m+columnName[counter][i]+"= "+"'"+tok[w++]+"'"+" AND ";
		}//end for loop i
		cout<<"Select value from employee table is="<<select_m2m<<endl;
		//end select value from the table for m2m
		char *chr = new char[select_m2m.length()+1];
		strcpy(chr,select_m2m.c_str());
		res= conMysqlObj.mysql_perform_query(conn,"use hibernate_db;");
		res=conMysqlObj.mysql_perform_query(conn,chr);
		vector<string> m2m_instance;
		while (((row= mysql_fetch_row(res)) !=NULL ))
		{ //cout<<" %s\n",row[i] !=NULL?row[i] : "NULL";
			m2m_instance.push_back(row[0]);
			
			cout <<"\t | \t" << row[0] << "\t | \t";
			//cout <<  row[i+1] <<  "\t |"<< endl;
			//cout<<row[i+2]<<"\t |"<<endl;
		}//end while loop
		for(int i=0 ;i<m2m_instance.size();i++){
			for(int j=0; j<resultvalue_m2m.size();j++){
				string insert_m2m_inter="INSERT INTO "+m2m_tablename[counter]+" ("+m2m_columnName[counter]+","+m2m_columnName[counter_m2m]+") VALUES ("
										+resultvalue_m2m[j]+","+m2m_instance[i]+");";
				char *chr = new char[insert_m2m_inter.length()+1];
				strcpy(chr,insert_m2m_inter.c_str());
				res= conMysqlObj.mysql_perform_query(conn,"use hibernate_db;");
				res=conMysqlObj.mysql_perform_query(conn,chr);		
										
			}
			
		}
		
	//make insert query for intermidiate table
	
  //end to store insert query for many to many 
  
	/* change here */ str_m2m.clear();
  }//end if condition for m2m here

}




// read data from the relational table

vector<Session *> cSessionFactory::get(Session *s,string  str1 , string str2){

	int k,counter_read,t=0,d;
	string s1 =typeid(*s).name(),token;
	bool already_created_flage=false;
	string read;
	for(d=0;d<s1.length();d++){
	
		if(s1[t]=='0'||s1[t]=='1'||s1[t]=='2'||s1[t]=='3'||s1[t]=='4'||s1[t]=='5'||s1[t]=='6'||s1[t]=='7'||s1[t]=='8'||s1[t]=='9'){
			t++;
		
		}
	}
	string obj_read=s1.substr(t);
	cout<<"typeid of s is="<<obj_read<<endl;
	for (int i=0;i<classname.size();i++){
		if(classname[i]==obj_read){
			counter_read=i;
			break;
		}
		
	}
	if(str2!="*"){	
		 read= "SELECT "+str1+" FROM "+tablename[counter_read]+" WHERE "+str1+" = "+str2+";";
	}
	else
		read= "SELECT * FROM "+tablename[counter_read]+";";
		
	char *cs = new char[server.length()+1];
	char *cu = new char[user.length()+1];
    char *cp = new char[password.length()+1];
    char *cd = new char[database.length()+1];
    strcpy(cs,server.c_str());
    strcpy(cu,user.c_str());
    strcpy(cp,password.c_str());
    strcpy(cd,database.c_str());
    struct connection_details mysqlD;
    mysqlD.server = cs;  // where the mysql database is
    mysqlD.user = cu;     // the root user of mysql   
    mysqlD.password =cp; // the password of the root user in mysql
    mysqlD.database = cd;    // the databse to pick

  // connect to the mysql database
    mySqlConnectivity conMysqlObj;
    conn = conMysqlObj.mysql_connection_setup(mysqlD);
    
    res= conMysqlObj.mysql_perform_query(conn,"use hibernate_db;");
	//res=conMysqlObj.mysql_perform_query(conn,chr);
    	
	char *chr = new char[read.length()+1];
	strcpy(chr,read.c_str());	
	res=conMysqlObj.mysql_perform_query(conn,chr);
	cout<<"read query is = "<<read<<endl;
	vector<string> readvalue;
	vector<Session *> sess;
	unsigned int i;
	while (((row= mysql_fetch_row(res)) !=NULL ))
	{ //cout<<" %s\n",row[i] !=NULL?row[i] : "NULL";
			//readvalue.push_back(row);
			for(i=0;i<columnName[counter_read].size();i++){
				readvalue.push_back(row[i]);
				
				
				//s->set(readvalue);
				cout <<"\t | \t" << row[i] << "\t | \t";
			}
			Session *se = s->createobj();
			se->set(readvalue);
			sess.push_back(se);
			readvalue.clear();	
			//cout <<  row[i+1] <<  "\t |"<< endl;
			//cout<<row[i+2]<<"\t |"<<endl;
	}//end while loop
	
	
	
	
	
	return sess;
}
//end function get to read data from the table






//----------------------UPDATE FUNCTION Starts*************************


void cSessionFactory::update(Session *s,string tableID,string idValue){

 int k,counter,t=0,d;
 string token,ctype;
 string s1 =typeid(*s).name();
  
	for(d=0;d<s1.length();d++){
		if(s1[t]=='0'||s1[t]=='1'||s1[t]=='2'||s1[t]=='3'||s1[t]=='4'||s1[t]=='5'||s1[t]=='6'||s1[t]=='7'||s1[t]=='8'||s1[t]=='9'){
		t++;
		}
     }

  string obj=s1.substr(t);
 
	for(k=0;k<classname.size();k++){
		if(classname[k]==obj){
		counter=k;
		break;
		}
	}

  string str = s->serialize();
  cout<<"str="<<str<<endl;
 
	char *cs = new char[server.length()+1];
	char *cu = new char[user.length()+1];
	char *cp = new char[password.length()+1];
	char *cd = new char[database.length()+1];
	strcpy(cs,server.c_str());
	strcpy(cu,user.c_str());
	strcpy(cp,password.c_str());
    strcpy(cd,database.c_str());
  struct connection_details mysqlD;
  mysqlD.server = cs;  // where the mysql database is
  mysqlD.user = cu;     // the root user of mysql   
  mysqlD.password =cp; // the password of the root user in mysql
  mysqlD.database = cd;    // the databse to pick

  // connect to the mysql database
  mySqlConnectivity conMysqlObj;
  conn = conMysqlObj.mysql_connection_setup(mysqlD);
	
  res= conMysqlObj.mysql_perform_query(conn,"use hibernate_db;");

  istringstream iss(str);
  vector<string> tok;
  string update;
  
	while (getline(iss,token,',')){
		tok.push_back(token);	}


//update ="update employee set Firstname = "+" tsrk" +" where id =1";

	update= "update "+obj+" set ";

     cout<<"column size = "<<columnName[counter].size()<<endl;
     cout<<"token size = "<<token.size()<<endl;

	for(int i=0;i<5;i++){
		cout<<tok[i]<<endl;
	}


	for(int i=1;i<columnName[counter].size()-1;i++)
	{	
		if(i==1){
			update=update+" "+columnName[counter][i]+" = "+"'"+tok[i-1]+"'"; 
			}
		else{ 
			update=update+" ,"+columnName[counter][i]+" = "+"'"+tok[i-1]+"'";
			}
    }
    /*
    for(int i=0;i<columnName[counter].size();i++){
		if(columnName[counter][i]==tableID){
			ctype=type[counter][i];
		}
	}
	*/
	//cout<<ctype<<endl;
	/*
    if(ctype=="int"){ 
	//idValue=stoi(idValue);
	update=update+" where "+tableID+ " "+"= "+idValue+" ;";
    }*/
   //else {
   update=update+" where "+tableID+ " "+"= '"+idValue+"' ;";
   //}
   cout<<update<<endl;
	
//update="update "+obj+" set "+s9 +" = "+"'"+s8+"'"+" where "+s7+ " "+"= '"+s6+"' ;";

char *chr = new char[update.length()+1];
strcpy(chr,update.c_str());
res=conMysqlObj.mysql_perform_query(conn,chr);

}

//-------------------------update function ended-----------------------------------------------//



//*************************************************Delete function Starts**********************************************************//



void cSessionFactory::Delete(Session *s,string tableID,string idValue)
{
 
  int k,counter,t=0,d;
  string s1 =typeid(*s).name();
  cout<<"\n\n\n"<<s1;
  for(d=0;d<s1.length();d++){
	if(s1[t]=='0'||s1[t]=='1'||s1[t]=='2'||s1[t]=='3'||s1[t]=='4'||s1[t]=='5'||s1[t]=='6'||s1[t]=='7'||s1[t]=='8'||s1[t]=='9'){
		t++;
	}
  }

  string obj=s1.substr(t);
  cout<<"typeid of s is=\n"<<obj<<endl;
  for(k=0;k<classname.size();k++){
	if(classname[k]==obj){
		counter=k;
		break;
	}
  }

string Del;
Del="DELETE FROM "+obj+" where "+tableID+"= "+idValue+";";


cout<<"Delete "<<Del<<endl;
char *chr = new char[Del.length()+1];
strcpy(chr,Del.c_str());

//cout<<"Delete  is="<<Del<<endl;

  char *cs = new char[server.length()+1];
  char *cu = new char[user.length()+1];
  char *cp = new char[password.length()+1];
  char *cd = new char[database.length()+1];
    strcpy(cs,server.c_str());
    strcpy(cu,user.c_str());
    strcpy(cp,password.c_str());
    strcpy(cd,database.c_str());
  struct connection_details mysqlD;
  mysqlD.server = cs;  // where the mysql database is
  mysqlD.user = cu;     // the root user of mysql   
  mysqlD.password =cp; // the password of the root user in mysql
  mysqlD.database = cd;    // the databse to pick

  // connect to the mysql database
mySqlConnectivity conMysqlObj;
conn = conMysqlObj.mysql_connection_setup(mysqlD);
res= conMysqlObj.mysql_perform_query(conn,"use hibernate_db;");
res=conMysqlObj.mysql_perform_query(conn,chr);
}


//******************************DELETE OBJECT FUNCTION COMPLETED**************************************************


void cSessionFactory::close(){
	mysql_free_result(res);
	mysql_close(conn);
}

