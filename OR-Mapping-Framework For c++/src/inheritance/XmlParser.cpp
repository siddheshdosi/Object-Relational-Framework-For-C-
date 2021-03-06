#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<vector>
#include "tinyxml.h"
#include "XmlParser.h"

using namespace std;


typedef vector<string> v1;
typedef vector< vector<string> > v2;
typedef vector<bool> v3;
v1 classname;
v1 tablename;
v1 one_to_one;
v1 one_to_many;
v1 foreign;
v1 foreign_type;
v2 foreign_key;
v2 foreign_key_type; 
v3 one_to_one_constrained;
v1 property;
v1 column;
v1 type_v1;
v1 NotNull_v1;
v1 unique_v1;
v1 Default_v1;
v2 propertyname;
v2 columnName;
v2 type;
v2 NotNull;
v2 unique;
v2 Default;
v1 generator;


// for one_to_many and many_to_one variable declaratioon
v1 many_to_one_key; 
v1 many_to_one; 
v1 set;
v1 set_key;
int check_o2m=0;
int check_set=0;
//end declaration




//update for inheritance


v1 subclass;
v1 extend;
v1 disc;
v2 disc_value;
bool disc_value_flage=false;
v1 disc_column;
v1 disc_column_type;
bool subclass_flage=false;
v1 subcolumnName_v1;
v1 subtype_v1;
v2 subcolumnName;
v2 subtype;
int subclass_count=0,subclass_precount=1;
bool change=false;
bool disc_column_flage=false;
// end update for inheritance


//update for many to many 
v1 m2m_tablename;
v1 m2m_foreignkey;
v1 m2m_columnName;
v1 m2m_classname;
bool m2m_flage=false;
int check_m2m=0;
string m2m_parentValue;
//end for many to many

//for xml file
v1 mappingfile;



bool notnull_flage=false,unique_flage=false,Default_flage=false,one_to_one_flage=false,one_to_one_constrained_flage=false,foreign_flage=false,many_to_one_flag=false,one_to_many_flag=false;
			

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

int XmlParser::dump_attribs_to_stdout(string m2m_parentValue,string father,string parentValue,TiXmlElement* pElement,unsigned int indent){
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



		//update for inheritance
		if(parentValue=="subclass" && str=="name"){
			subclass.push_back(pAttrib->Value());
			subclass_flage=true;
			subclass_count++;
			

		}
		if(parentValue=="subclass" && str=="extends"){
			extend.push_back(pAttrib->Value());
		}
		if(( parentValue=="subclass" || parentValue=="class")&& str=="discriminator-value"){
			disc.push_back(pAttrib->Value());
			disc_value_flage=true;
		}

		if(parentValue=="discriminator" ) {
			if(str=="column"){
				
				disc_column.push_back(pAttrib->Value());
				disc_column_flage=true;
				
			}
			if(str=="type"){
				disc_column_type.push_back(pAttrib->Value());
			}

		}

		if(subclass_flage==true &&(str=="name")&&(parentValue=="property"||parentValue=="id") && father=="hibernate-mapping"){
			
			//nothing
			
		}
                
		
		if(subclass_flage==true && (str=="column")&&(parentValue=="property"||parentValue=="id")){
			if(subclass_count == subclass_precount+1){
				subclass_precount++;
				
				subcolumnName.push_back(subcolumnName_v1);
				
				subcolumnName_v1.clear();
				change=true;
				
				
			}
			subcolumnName_v1.push_back(pAttrib->Value());
			
		}
		if(subclass_flage==true  && (str=="type")&&(parentValue=="property"||parentValue=="id")){
			if(change==true){
				change=false;
				subtype.push_back(subtype_v1);
				subtype_v1.clear();
				
			}
			subtype_v1.push_back(pAttrib->Value());
			
		}
		//end update for inheritance

        //update for many to many
        if(parentValue=="many-to-many"){
			if(str=="table"){
				m2m_tablename.push_back(pAttrib->Value());
				check_m2m=1;
				m2m_flage=true;
				
			}
			
			
		}//end if for m2m
        if(parentValue=="key" && str=="column"){
			
			m2m_foreignkey.push_back(pAttrib->Value());
		}
        if(parentValue=="column" && check_m2m==1 && m2m_parentValue=="many-to-many"){
			if(str=="name"){
				m2m_columnName.push_back(pAttrib->Value());
			}
			if(str=="class"){
				m2m_classname.push_back(pAttrib->Value());
				check_m2m=0;
			}
		} 
        //end update for many to many

		if(str=="table" && parentValue=="class"){
			tablename.push_back(pAttrib->Value());
			
		}
		//update for inheritance
		if(subclass_flage==false && (str=="name")&&(parentValue=="property"||parentValue=="id") && father=="hibernate-mapping"){
			
			property.push_back(pAttrib->Value());
			
		}
                
		//update for inheritance
		if(subclass_flage==false &&(str=="column")&&(parentValue=="property"||parentValue=="id")){
			
			column.push_back(pAttrib->Value());
			
		}
		//update for inheritance
		if(subclass_flage==false && (str=="type")&&(parentValue=="property"||parentValue=="id")){
			
			type_v1.push_back(pAttrib->Value());
			
		}
		string attribute=pAttrib->Value();

		if(parentValue=="one-to-one"){
			if(str=="name"){
				one_to_one.push_back(pAttrib->Value());
				one_to_one_flage=true;
			}
			if(str=="constrained"){
				one_to_one_constrained.push_back(pAttrib->Value());
				one_to_one_constrained_flage=true;
			}
			
		}
		
		
//---------------- start one to many and many to one ----------		
/* for one to many relationship */

 		if(parentValue=="set"){
			check_set=1;
		}

		if(parentValue=="one-to-many" && check_set==1 ){
			if(str=="class"){
				set.push_back(pAttrib->Value());
				one_to_many_flag=true;
				//check_set=1;
			}
						
		}
		
		if(parentValue=="key" && check_set==1){
			if(str=="column"){
				set_key.push_back(pAttrib->Value());
			}
				check_set=0;		
		}
		
/* for many to one relationship */			


		if(parentValue=="many-to-one"){
			if(str=="name"){
				many_to_one.push_back(pAttrib->Value());
				many_to_one_flag=true;
				check_o2m=1;
			}
		}

		if(parentValue=="column" && (check_o2m==1)){
			if(str=="name"){
				many_to_one_key.push_back(pAttrib->Value());
			}
			check_o2m=0;
		}

		
		
		
//------------------ end one to many and many to one -----------------		
		
		if(parentValue=="generator" && str=="class" && (attribute=="foreign"||attribute=="native" || attribute=="identity")){
			int gn = column.size();
			cout<<"column.size()= "<<column.size()<<endl;
			generator.push_back(column[gn-1]);
			
			if(attribute=="foreign"){
				foreign.push_back(column[gn-1]);
				foreign_type.push_back(type_v1[gn-1]);
				foreign_flage=true;
			}
					
		}
		
		if(parentValue=="column" && m2m_parentValue=="?00?" && many_to_one_flag==false){
			pAttr=pAttrib->Value();
			if(str=="name"){
				column.push_back(pAttrib->Value());
			}
			if(str=="not-null"){
				notnull_flage=true;
				if(pAttrib->Next()==NULL ){
					if( unique_flage==false){
					  
						unique_v1.push_back("F");
					}
					if(Default_flage==false){
						Default_v1.push_back("?00?");
					}
				}
				if(pAttr=="true"){
					NotNull_v1.push_back("T");
				}
				else
					NotNull_v1.push_back("F");
			}
			if(str=="unique"){
				unique_flage=true;
				if(pAttrib->Next()==NULL){
					if( notnull_flage==false){
					 
						NotNull_v1.push_back("F");
					}
					if(Default_flage==false){
						Default_v1.push_back("?00?");
					}
				}
				if(pAttr=="true"){
					unique_v1.push_back("T");
				}
				else
					unique_v1.push_back("F");
			}
			if(str=="default"){
				Default_flage=true;
				if(pAttrib->Next()==NULL ){
					if( notnull_flage==false){  
						NotNull_v1.push_back("F");
					}
					if(unique_flage==false){
						unique_v1.push_back("F");
					}
				}
				Default_v1.push_back(pAttrib->Value());
			}
			
			

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

		//for xml mapping file

		if((str=="resource") && parentValue=="mapping" && father=="hibernate-configuration"){
			//cout<<"In conserver"<<endl;
			pAttr=pAttrib->Value();
			mappingfile.push_back(pAttr);
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
		if(parentValue=="many-to-many"){
			m2m_parentValue="many-to-many";
			
		}
		if(parentValue =="property" || parentValue=="id" || parentValue=="generator"){
			
			m2m_parentValue="?00?";
		}
		//cout<<"here"<<endl;
		num=xparser.dump_attribs_to_stdout(m2m_parentValue,father,parentValue,pParent->ToElement(),indent+1);
		//cout<<"asdf"<<endl;
		notnull_flage=false;
		unique_flage=false;
		Default_flage=false;
		switch(num)
		{
			case 0:  printf( " (No attributes)"); break;
			case 1:  printf( "%s1 attribute", xparser.getIndentAlt(indent)); break;
			case 3:  if(parentValue=="property" || parentValue=="id"){
					NotNull_v1.push_back("F"); 
					unique_v1.push_back("F");
					Default_v1.push_back("?00?");
				 } 
				 break;
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
	if(father =="hibernate-mapping"){	
		propertyname.push_back(property);
		columnName.push_back(column);
		type.push_back(type_v1);
		NotNull.push_back(NotNull_v1);
		Default.push_back(Default_v1);
		unique.push_back(unique_v1);
//--------------- strat o2m m2o-----------------		
		/* insert default value for one to many flag  */
		if(one_to_many_flag==false){
			set.push_back("?00?");
			set_key.push_back("?00?");
		}
		one_to_many_flag=false;



       /*insert default value for many to one flag  */
		if(many_to_one_flag==false){
			many_to_one.push_back("?00?");
			many_to_one_key.push_back("?00?");
		}
		many_to_one_flag=false;

//------------ end insert o2m m2o ------------

		
		
		//change here && father=="hibernate-mapping"
		if(one_to_one_flage==false && father=="hibernate-mapping"){
			one_to_one.push_back("?00?");
		}
		one_to_one_flage=false;
		//change here && father=="hibernate-mapping"
		if(one_to_one_constrained_flage==false && father=="hibernate-mapping"){
			one_to_one_constrained.push_back(false);
		}
		//change here && father=="hibernate-mapping"
		if(foreign_flage==false && father=="hibernate-mapping"){
			foreign.push_back("?00?");
			foreign_type.push_back("?00?");
		}
		foreign_flage=false;
		//update for inheritance
		if (disc_value_flage==false && father=="hibernate-mapping"){
			disc.push_back("?00?");
			//disc_column.push_back("?00?");
			//disc_column_type.push_back("?00?");
			
		}
		disc_value.push_back(disc);
		disc.clear();
		disc_value_flage=false;
		if(subclass_flage==true){
			subcolumnName.push_back(subcolumnName_v1);
		
			subcolumnName_v1.clear();
			subtype.push_back(subtype_v1);
			subtype_v1.clear();
		}
		subclass_flage=false;
		if(disc_column_flage==false && father=="hibernate-mapping"){
			disc_column.push_back("?00?");
			disc_column_type.push_back("?00?");
		}
		disc_column_flage=false;
		//end update for inheritance

		//update for m2m here
		if(m2m_flage==false){
			m2m_classname.push_back("?00?");
			m2m_columnName.push_back("?00?");
			m2m_foreignkey.push_back("?00?");
			m2m_tablename.push_back("?00?");
			
			
		}
		m2m_flage=false;
		
		//end update for m2m here

		foreign_key.push_back(foreign);
		foreign_key_type.push_back(foreign_type);
	}//end if of father	
		foreign_type.clear();
		foreign.clear();
		property.clear();
		column.clear();
		type_v1.clear();
		NotNull_v1.clear();
		Default_v1.clear();
		unique_v1.clear();
		
	
	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
	}
}

