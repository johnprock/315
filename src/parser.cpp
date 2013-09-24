#pragma once

#include "parser.h"
#include "Tokenizer.h"
#include "dbEngine.h"
#include <iostream>

using namespace std;

//constructor
Parser::Parser(string _command) {
	command = _command;
	tokenizer = Tokenizer(&command); 
}

bool Parser::parse() {
	return parse_command() || parse_query();
}

//-----------------//
//--QUERY PARSING--//
//-----------------//
bool Parser::parse_query() {
	tokenizer.checkpoint();
	string name;
	bool ret = (name = parse_relation()) != ""   && 
	           tokenizer.consume_token("<-")     && 
	           parse_expr()                      &&
	           tokenizer.consume_token(";")      ;
	
	if(ret) {
		cout<<"query parsed\n";
	}
	else {
		tokenizer.backup();
	}
    return ret;
}

string Parser::parse_relation() {
	string s;
	if (isid(tokenizer.get_token())) {
	  s = tokenizer.get_token();
	  tokenizer.index++;
	  return s;
	}
	else return "";
}

bool Parser::parse_expr() {
	return   parse_selection()   ||
           parse_projection()  ||
           parse_renaming()    ||
           parse_union()       ||
           parse_difference()  ||
           parse_product()     ||
	         parse_atomic()      ;
}

bool Parser::parse_atomic() {
	tokenizer.checkpoint();
	string name;
	bool ret =  ((name = parse_relation()) != "")            ||
			        (tokenizer.consume_token("(")                &&
		           parse_expr()                                &&
			         tokenizer.consume_token(")"));
	if(ret){
    cout << "Atomic parsed.\n";
	}
	else {
		tokenizer.backup();
	}
	return ret;
}

bool Parser::parse_selection() {
  cout << "Parsing selection...";
	tokenizer.checkpoint();
	bool ret =  tokenizer.consume_token("select") /*                &&
	            tokenizer.consume_token("(")                      &&
	            parse_condition()                                 &&
	            tokenizer.consume_token(")")                      &&
              parse_atomic()*/;
	if(ret){
    cout << "Selection parsed.\n";
	  //going to need stuff from condition and parse atomic, i assume	
	}
	else {
		tokenizer.backup();
    cout << "Selection parse fail.\n";
	}
	return ret;
}

bool Parser::parse_projection() {
	tokenizer.checkpoint();
	bool ret =  tokenizer.consume_token("PROJECT")                &&
	            tokenizer.consume_token("(")                      &&
	            parse_attribute_list()                            &&
	            tokenizer.consume_token(")")                      &&
                    parse_atomic();
	if(ret){
    cout << "Projection parsed.\n";
	}
	else {
		tokenizer.backup();
		cout << "Projection parse failed.\n";
	}
	return ret;
}

bool Parser::parse_renaming() {
	tokenizer.checkpoint();
	bool ret =  tokenizer.consume_token("RENAME")                 &&
	            tokenizer.consume_token("(")                      &&
	            parse_attribute_list()                            &&
	            tokenizer.consume_token(")")                      &&
                    parse_atomic();
	if(ret){
    cout << "Renaming parsed.\n";
	}
	else {
		tokenizer.backup();
		cout << "Renaming parse failed.\n";
	}
	return ret;
}

bool Parser::parse_union() {
	tokenizer.checkpoint();
	bool ret =  parse_atomic()                                    &&
	            tokenizer.consume_token("+")                      &&
	            parse_atomic();
	if(ret){
	  cout << "Union parsed.\n";
	}
	else {
		tokenizer.backup();
		cout << "Union parse failed.\n";
	}
	return ret;
}

bool Parser::parse_difference() {
	tokenizer.checkpoint();
	bool ret =  parse_atomic()                                    &&
	            tokenizer.consume_token("-")                      &&
	            parse_atomic();
	if(ret){
    cout << "Difference parsed.\n";
	}
	else {
		tokenizer.backup();
	}
	return ret;
}

bool Parser::parse_product() {
	tokenizer.checkpoint();
	bool ret =  parse_atomic()                                    &&
	            tokenizer.consume_token("*")                      &&
	            parse_atomic();
	if(ret){
    cout << "Product parsed.\n";
	}
	else {
		tokenizer.backup();
	}
	return ret;
}

bool Parser::parse_condition() {
	tokenizer.checkpoint();
	bool ret = parse_conjunction();
	while (tokenizer.consume_token( "||")) ret = ret && parse_conjunction();
	if(ret){
	    cout << "Condition parsed.\n";
	}
	else{
	    tokenizer.backup();
	}
	return ret;
}

// not working
bool Parser::parse_conjunction(){
	tokenizer.checkpoint();
	bool ret = parse_comparison();

	while(tokenizer.consume_token("&&")) ret = ret && parse_comparison();

	if(ret){
    cout << "Conjunction parsed.\n";
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_comparison(){
    tokenizer.checkpoint();
    string op = "";
    string operand1 = "", operand2 = "";
    bool ret =	((operand1 = parse_literal()) != "")                  &&
		((op = parse_op()) != "")                             &&
		((operand2 = parse_literal()) != "")                  ||
		tokenizer.consume_token("(")                          &&
		parse_condition()                                     &&
		tokenizer.consume_token(")");
		
    if(ret){
      cout<<"Comparison parsed.\n";
    }
    else tokenizer.backup();
    return ret;
}

string Parser::parse_op(){
    tokenizer.checkpoint();
    string op = "";
    bool ret = false;
    op = parse_literal();
    if (op ==  "=="		||
	op == "!="		||
	op == "<"	    ||
	op == ">"	    ||
	op == "<="	    ||
	op == ">="	    ||
	op == ""    )
	ret = true;
    if (ret){
      cout<<"Comparison parsed.\n";
    }
    else tokenizer.backup();
    return op;
}

//-------------------//
//--COMMAND PARSING--//
//-------------------//
bool Parser::parse_command() {
	return (parse_open()   || 
	       parse_close()  || 
	       parse_write()  ||
	       parse_exit()   || 
	       parse_show()   || 
	       parse_create() || 
	       parse_update() ||
	       parse_insert() || 
	       parse_delete() ) &&
         tokenizer.consume_token(";");

         cout << "Command parserd.\n";
}

bool Parser::parse_open() {
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("OPEN")		&&
		((name = parse_relation()) != "");
	if(ret){
		cout<<"Open parsed.\n";
		
		db->Open(name);
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_close() {
  //cout << "Parsing close...";
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("CLOSE")		&&
		((name = parse_relation()) != "");
	if(ret){
    cout << "Close parsed.\n";
    db->Close();
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_write() {
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("WRITE")		&&
		((name = parse_relation()) != "");
	if(ret){
    cout << "Write parsed.\n";
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_exit() {
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("EXIT");
	if(ret){
    cout << "Exit parsed.\n";
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_show() {
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("SHOW")		&&
		parse_atomic();
	if(ret){
    cout << "Show parsed.\n";
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_create() {
	tokenizer.checkpoint();

	string name = "";


	bool ret =  tokenizer.consume_token("CREATE TABLE")                       &&
	            (name = parse_relation()) != ""                               &&
	            tokenizer.consume_token("(")                                  &&
	            parse_typed_attribute_list()                                  &&
	            tokenizer.consume_token(")")                                  &&
              tokenizer.consume_token("PRIMARY KEY")                        &&
              tokenizer.consume_token("(")                                  &&
	            parse_attribute_list()                                        &&
              tokenizer.consume_token(")")                                  ;
	if(ret){
	  //execute db engine calls
		cout<<"Create Table parsed.\n";
	  db->createTable(name, types);	
	}
	else {
		tokenizer.backup();
	}
	return ret;
}

bool Parser::parse_update() {
	tokenizer.checkpoint();
	string name = "";		//i used this variable for the attribute names too.
	//this will be changed when we have decied upon a good way of handling 
	//return values.
	bool ret = tokenizer.consume_token("UPDATE")	        &&
		((name = parse_relation()) != "")			      	&&
		tokenizer.consume_token("SET")			      		&&
		//there must be at least one attribute to set
	    ((name = parse_attribute_name()) != "")	   	    &&
		tokenizer.consume_token("==")				      	&&
		((name = parse_literal()) != "");
		
		//only parse further if there are more comma sparated attributes to parse
		while(tokenizer.consume_token(",")) ret = ret		&&
				((name = parse_attribute_name()) != "")	  	&&
				tokenizer.consume_token("==")			    &&
				((name = parse_literal()) != "");
	if(ret){
		//do some stuff
		cout<<"Update parsed.\n";
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_insert() {
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("INSERT INTO")		&&
		 ((name = parse_relation()) != "")					&&
		 tokenizer.consume_token("VALUES FROM")			  	&&
		 tokenizer.consume_token("(")			         	&&
		 ((name = parse_literal()) != "");
	
	while(tokenizer.consume_token(",")) ret = ret		  	&&
		((name = parse_literal()) != "");

	ret = ret || 
		tokenizer.consume_token("INSERT INTO")			    &&
		((name = parse_relation()) != "")			     	&&
		tokenizer.consume_token("VALUES FROM RELATION")		&&
		parse_expr();

	if(ret){
    cout << "Insert parsed.\n";
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_delete() {
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("DELETE FROM")		&&
		((name = parse_relation()) != "")			   		&&
		tokenizer.consume_token("WHERE")		   			&&
		parse_condition();

	if(ret){
    cout << "Delete parsed.\n";
	}
	else tokenizer.backup();
	return ret;
}

string Parser::parse_attribute_name() {
  string s;
  if(isid(tokenizer.get_token())) {
    s = tokenizer.get_token();
  	tokenizer.index++;
  	return s;
  }
  return "";
}


bool Parser::parse_attribute_list() {
	tokenizer.checkpoint();
  bool ret;
  string s;
  attrs = vector<Attribute>(); // initialize empty list
 
  s = parse_attribute_name();
  if(s != "") { // attribute name parse succeeded
    ret = true;
	  cout<<"Attribute list parsed.\n";
  }
  else {
    tokenizer.backup();
  }
  while(s != "") { // consume list and store in attrs
    attrs.push_back(s);
    tokenizer.consume_token(",");
    s = parse_attribute_name();
  }
  return ret;
}

// sets attrs to the value of the attribute list
bool Parser::parse_typed_attribute_list() { // this is broken, not parsing types...
	string name;
 	tokenizer.checkpoint();
  parse_attribute_name();
  bool ret = parse_type();
  bool loop = ret;
  
  if(ret){
    cout<<"typed attribute list parsed.\n";
  }
  else {
    tokenizer.backup();
  } 

  while(loop) {
    loop = tokenizer.consume_token(",") && (parse_attribute_name() != "") && parse_type();
  }
  return ret;  
}

bool Parser::parse_type() {
	tokenizer.checkpoint();
	bool ret = parse_int_type() || parse_var_type();

	if(ret){
		//do some stuff like  Type t = Type();
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_var_type() {
  tokenizer.checkpoint();
  bool ret;
  ret = tokenizer.consume_token("VARCHAR") &&
        tokenizer.consume_token("(")       &&
        parse_int()                        &&
        tokenizer.consume_token(")");
  if(!ret) {
    tokenizer.backup();
  }
  return ret;
}

bool Parser::parse_int_type() {
	tokenizer.checkpoint();
	string s;
	bool ret = tokenizer.consume_token("INTEGER");	
	if (ret){
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_int() {
  string s = tokenizer.get_token();
  bool ret = s.find_first_not_of("0123456789") == std::string::npos; // this fragment lifted from Stack Overflow checks if is integer
  if(ret)
    tokenizer.index++;
  return ret;
}

string Parser::parse_literal(){
	bool ret = false;
	string s = tokenizer.get_token();
	tokenizer.index++;
	cout<<"Literal parsed.\n";
	return s;
}

//--------------------//
//--HELPER FUNCTIONS--//
//--------------------//

// returns true if the string is an alpha followed by 0 or more alphanumerics
bool Parser::isid(string id){
  bool ret = true;
  if(!isalpha(id[0])) {
    ret = false;
  }
  for(int i=1; i<id.length(); i++) {
    if(!isalnum(id[i])) {
      ret = false;
    }
  }
  return ret;
}