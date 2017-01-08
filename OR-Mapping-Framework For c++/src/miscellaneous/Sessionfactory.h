#include "Session.h"
#include<vector>
class cSessionFactory
{
 public:
	
     void openSession();
     void save(Session *s);
     vector<Session *>  get(Session *s, string , string);
     void Delete(Session *s , string, string);
     void update(Session *s,string , string);
         void close();
};
