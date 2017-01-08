#include<string>
#include "tinyxml.h"
using namespace std;



class XmlParser{
	public:
		const char * getIndent( unsigned int );
		const char * getIndentAlt( unsigned int);
		int dump_attribs_to_stdout(string,string,string ,TiXmlElement*,unsigned int);
		void dump_to_stdout( TiXmlNode*,unsigned int);
		void dump_to_stdout(const char* );
		
};
