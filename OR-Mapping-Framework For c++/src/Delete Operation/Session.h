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
	virtual vector<Session *> *getlistobj(){
		vector<Session *> *v;
		return v;
	}
	virtual void set(vector<string> v){
		
		NULL;
	}
	virtual Session * createobj(){
		return NULL;
	}	
};



#endif
