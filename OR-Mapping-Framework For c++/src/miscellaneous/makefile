 CC=g++


hibernateMake: employeeTest.o employee.o employeeDetails.o chair.o sessionfactory.o XmlParser.o mySqlConnectivity.o
	$(CC) employeeTest.o employee.o employeeDetails.o chair.o sessionfactory.o XmlParser.o mySqlConnectivity.o  -o hibernateMake -L/usr/include/mysql -lmysqlclient -Iusr/include/mysql/mysql -ltinyxml

employeeTest.o:
	$(CC) -c employeeTest.cpp -o employeeTest.o 

employee.o: 
	$(CC) -c employee.cpp -o employee.o

employeeDetails.o:
	$(CC) -c employeeDetails.cpp -o employeeDetails.o

chair.o :
	$(CC) -c chair.cpp -o chair.o

sessionfactory.o:
	$(CC) -c sessionfactory.cpp -o sessionfactory.o -L/usr/include/mysql -lmysqlclient -Iusr/include/mysql/mysql

XmlParser.o:
	$(CC) -c XmlParser.cpp -o XmlParser.o -ltinyxml

mySqlConnectivity.o:
	$(CC) -c mySqlConnectivity.cpp -o mySqlConnectivity.o -L/usr/include/mysql -lmysqlclient -Iusr/include/mysql/mysql 


