#include <mysql/mysql.h>

struct connection_details
{
  const  char *server;
   const char *user;
    const char *password;
   const  char *database;
};

class mySqlConnectivity{

public:

MYSQL* mysql_connection_setup(struct connection_details);
MYSQL_RES* mysql_perform_query(MYSQL *,const char *);


};
