#ifndef SESSION_FACTORY___H
#define SESSION_FACTORY___H
#include<string>
#include<vector>
using namespace std;

class Session{
 public:
	 virtual string serialize()=0;
	  
	 virtual Session *getobj(){
		return NULL;
	 }

/*For many to many mapping need to get all objects in cSesstionfactory */
	virtual vector<Session *> *getlistobj(){
		vector<Session *> *v;
		return v;
	}
/*his method use to read data from The RDBMS*/
	virtual void set(vector<string> v){
		
		NULL;
	}
/*This method use to read data from The RDBMS*/
	virtual Session * createobj(){
		return NULL;
	}	
};


#endif
