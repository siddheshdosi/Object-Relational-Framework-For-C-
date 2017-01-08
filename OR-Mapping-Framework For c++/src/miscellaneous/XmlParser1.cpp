#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<vector>
#include "tinyxml.h"
#include "XmlParser.h"

using namespace std;


typedef vector<string> v;
v classname;
v tablename;
v propertyname;
v columnName;
v type;
string server,user,password,database,father;
bool conserver=false,conuser=false,conpassword=false,condatabase=false;
string parentValue,pAttr;
XmlParser xparser;
const unsigned int NUM_INDENTS_PER_SPACE=2;

const char* XmlParser::getIndent( unsigned int numIndents )
{
	static const char * pINDENT="                                      + ";
	static const unsigned int LENGTH=strlen( pINDENT );
	unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}

// same as getIndent but no "+" at the end
const char* XmlParser::getIndentAlt( unsigned int numIndents )
{
	static const char * pINDENT="                                        ";
	static const unsigned int LENGTH=strlen( pINDENT );
	unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}

int XmlParser::dump_attribs_to_stdout(string father,string parentValue,TiXmlElement* pElement,unsigned int indent){
	if ( !pElement ) return 0;

	TiXmlAttribute* pAttrib=pElement->FirstAttribute();
	int i=0;
	int ival;
	double dval;
	const char* pIndent=xparser.getIndent(indent);
	printf("\n");
	while (pAttrib)
	{
		printf( "%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());
		string str=pAttrib->Name();
		if(str=="name" && parentValue=="class"){
			classname.push_back(pAttrib->Value());
			

		}
		if(str=="table" && parentValue=="class"){
			tablename.push_back(pAttrib->Value());
			

		}

		if((str=="name")&&(parentValue=="property"||parentValue=="id") && father=="hibernate-mapping"){
			propertyname.push_back(pAttrib->Value());
			
		}
                
		
		if((str=="column")&&(parentValue=="property"||parentValue=="id")){
			
			columnName.push_back(pAttrib->Value());
			
		}
		if((str=="type")&&(parentValue=="property"||parentValue=="id")){
			
			type.push_back(pAttrib->Value());
			
		}
		if((str=="name") && parentValue=="property" && father=="hibernate-configuration"){
			//cout<<"In conserver"<<endl;
			pAttr=pAttrib->Value();
			if(pAttr=="connection.server"){
				conserver=true;
				cout<<"In conserver"<<endl;
			}
			if(pAttr=="connection.user"){
				conuser=true;
			}
			if(pAttr=="connection.password"){
				conpassword=true;
			}
			if(pAttr=="connection.database"){
				condatabase=true;
			}
		}

		if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS)    printf( " int=%d", ival);
		if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) printf( " d=%1.1f", dval);
		printf( "\n" );
		i++;
		pAttrib=pAttrib->Next();
	}
	return i;	
}

void XmlParser::dump_to_stdout( TiXmlNode* pParent,unsigned int indent = 0 )
{
	if ( !pParent ) return;

	TiXmlNode* pChild;
	TiXmlText* pText;
	int t = pParent->Type();
	printf( "%s :--", xparser.getIndent(indent));
	int num;

	switch ( t )
	{
	case TiXmlNode::TINYXML_DOCUMENT:
		printf( "Document" );
		break;

	case TiXmlNode::TINYXML_ELEMENT:
		
		//father=pParent->Value();
			//cout<<"------father"<<father<<endl;
		printf( "Element [%s]", pParent->Value() );
		parentValue = pParent->Value();
		if(parentValue=="hibernate-configuration"|| parentValue=="hibernate-mapping"){
			father=pParent->Value();
			cout<<"Father= "<<father<<endl;
		}
		num=xparser.dump_attribs_to_stdout(father,parentValue,pParent->ToElement(),indent+1);
		switch(num)
		{
			case 0:  printf( " (No attributes)"); break;
			case 1:  printf( "%s1 attribute", xparser.getIndentAlt(indent)); break;
			default: printf( "%s%d attributes", xparser.getIndentAlt(indent), num); break;
		}
		break;

	case TiXmlNode::TINYXML_COMMENT:
		printf( "Comment: [%s]", pParent->Value());
		break;

	case TiXmlNode::TINYXML_UNKNOWN:
		printf( "Unknown" );
		break;

	case TiXmlNode::TINYXML_TEXT:
		pText = pParent->ToText();
		if(conserver==true){
			server=pText->Value();
			conserver=false;
		}
		else if(conuser==true){
			user=pText->Value();
			conuser=false;
		}
		else if(conpassword==true){
			password=pText->Value();
			conpassword=false;
		}
		else if (condatabase==true){
			database=pText->Value();
			condatabase=false;
		}
		printf( "Text: [%s]", pText->Value() );
		break;

	case TiXmlNode::TINYXML_DECLARATION:
		printf( "Declaration" );
		break;
	default:
		break;
	}
	printf( "\n" );
	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		dump_to_stdout( pChild,indent+1 );
	}
}

// load the named file and dump its structure to STDOUT
void XmlParser::dump_to_stdout(const char* pFilename )
{
	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{ 
		
		printf("\n%s:\n", pFilename);
		xparser.dump_to_stdout( &doc); 
	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
	}
}


