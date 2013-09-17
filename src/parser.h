// Parses tokenized expression
// 9/13/13

#pragma once

#include "tokenizer.h"
#include "dbEngine.h"
#include <iostream>

using namespace std;

class Parser {
  public:
    Parser(string text);

  	// main parsing function
  	// some parsing functions return a bool to indicate a sucessfull parse
  	// others return data that is the result of the parse
    bool parse();
  
  private:
    Tokenizer tokenizer;
    string command;
    DbEngine db;

    vector<Attribute> attrs;  // holds attribute lists 
    vector<Attribute> typed_attrs;  // holds typed attribute lists
    vector<Attribute> primes;
    vector<Type> types;

  	// parsing helper functions, called by parse()
  	// query parsing functions
  	bool parse_query();

    string parse_relation();

    bool parse_identifier();

    bool parse_expr();

    bool parse_atomic();

    bool parse_selection();

    bool parse_condition();

    bool parse_conjunction();

    bool parse_comparison();

    bool parse_operand();

    string parse_attribute_name();

    bool parse_projection();

    bool parse_attribute_list();

    bool parse_renaming();

    bool parse_union();

    bool parse_difference();

    bool parse_product();

    //command parsing functions
    bool parse_command();

    bool parse_open();

    bool parse_close();

    bool parse_write();

    bool parse_exit();

    bool parse_show();

    bool parse_create();

    bool parse_update();

    bool parse_insert();

    bool parse_delete();

    bool parse_typed_attribute_list();

    Type parse_type();

    bool parse_int();

    bool parse_var_type();

    bool parse_int_type();

	string parse_literal();

    bool isid(string id); //helper function tests for valid identifier names, needs implementation currently returns true

};

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
	// execute query code
	if(ret) {
		;
	}
	else {
		tokenizer.backup();
	}
    return ret;
}

string Parser::parse_relation() {
	if (isid(tokenizer.get_token())) {
	  tokenizer.index++;
	  return tokenizer.get_token();
	}
	else return "";
}

bool Parser::parse_expr() {
	return   parse_atomic()      ||
           parse_selection()   ||
           parse_projection()  ||
           parse_renaming()    ||
           parse_union()       ||
           parse_difference()  ||
           parse_product()     ;
}

bool Parser::parse_atomic() {
	tokenizer.checkpoint();
	string name;
	bool ret =  (name = parse_relation()) != "" ||
		          parse_expr();
	if(ret){
    cout << "Atomic parsed.";
	  ;	
	}
	else {
		tokenizer.backup();
	}
	return ret;
}

bool Parser::parse_selection() {
	tokenizer.checkpoint();
	bool ret =  tokenizer.consume_token("SELECT")                 &&
	            tokenizer.consume_token("(")                      &&
	            parse_condition()                                 &&
	            tokenizer.consume_token(")")                      &&
                    parse_atomic();
	if(ret){
    cout << "Selection parsed.";
	  //going to need stuff from condition and parse atomic, i assume	
	}
	else {
		tokenizer.backup();
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
    cout << "Projection parsed.";
	}
	else {
		tokenizer.backup();
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
    cout << "Renaming parsed.";
	}
	else {
		tokenizer.backup();
	}
	return ret;
}

bool Parser::parse_union() {
	tokenizer.checkpoint();
	bool ret =  parse_atomic()                                    &&
	            tokenizer.consume_token("+")                      &&
	            parse_atomic();
	if(ret){
	  cout << "Union parsed.";
	}
	else {
		tokenizer.backup();
	}
	return ret;
}

bool Parser::parse_difference() {
	tokenizer.checkpoint();
	bool ret =  parse_atomic()                                    &&
	            tokenizer.consume_token("-")                      &&
	            parse_atomic();
	if(ret){
    cout << "Difference parsed.";
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
    cout << "Product parsed.";
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
    cout << "Condition parsed.";
	}
	else{
	    tokenizer.backup();
	}
	return ret;
}

bool Parser::parse_conjunction(){
	tokenizer.checkpoint();
	bool ret = parse_condition();

	while(tokenizer.consume_token("&&")) ret = ret && parse_condition();

	if(ret){
    cout << "Conjunction parsed.";
	}
	else tokenizer.backup();
	return ret;
}

//-------------------//
//--COMMAND PARSING--//
//-------------------//
bool Parser::parse_command() {
	return parse_open()   || 
	       parse_close()  || 
	       parse_write()  ||
	       parse_exit()   || 
	       parse_show()   || 
	       parse_create() || 
	       parse_update() ||
	       parse_insert() || 
	       parse_delete() ;
}

bool Parser::parse_open() {
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("OPEN")		&&
		((name = parse_relation()) != "");
	if(ret){
		//do some stuff
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_close() {
  cout << "Parsing close...";
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("CLOSE")		&&
		((name = parse_relation()) != "");
	if(ret){
    cout << "Close parsed.";
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
    cout << "Write parsed.";
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_exit() {
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("EXIT");
	if(ret){
    cout << "Exit parsed.";
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
    cout << "Show parsed.";
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
              tokenizer.consume_token("PRIMATY_KEY")                        &&
              tokenizer.consume_token("(")                                  &&
	            parse_attribute_list()                                        &&
              tokenizer.consume_token(")")                                  ;
	if(ret){
	  //execute db engine calls
	  db.createTable(name, types);	
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
	bool ret = tokenizer.consume_token("UPDATE")		&&
		((name = parse_relation()) != "")			      	&&
		tokenizer.consume_token("SET")			      		&&
		//there must be at least one attribute to set
		((name = parse_attribute_name()) != "")	   		&&
		tokenizer.consume_token("==")				        	&&
		((name = parse_literal()) != "");
		
		//only parse further if there are more comma sparated attributes to parse
		while(tokenizer.consume_token(",")) ret = ret		&&
				((name = parse_attribute_name()) != "")	  	&&
				tokenizer.consume_token("==")			        	&&
				((name = parse_literal()) != "");
	if(ret){
		//do some stuff
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_insert() {
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("INSERT INTO")		&&
		 ((name = parse_relation()) != "")					      &&
		 tokenizer.consume_token("VALUES FROM")			     	&&
		 tokenizer.consume_token("(")					          	&&
		 ((name = parse_literal()) != "");
	
	while(tokenizer.consume_token(",")) ret = ret		  	&&
		((name = parse_literal()) != "");

	ret = ret || 
		tokenizer.consume_token("INSERT INTO")			    	&&
		((name = parse_relation()) != "")				         	&&
		tokenizer.consume_token("VALUES FROM RELATION")		&&
		parse_expr();

	if(ret){
    cout << "Insert parsed.";
	}
	else tokenizer.backup();
	return ret;
}

bool Parser::parse_delete() {
	tokenizer.checkpoint();
	string name = "";
	bool ret = tokenizer.consume_token("DELETE FROM")		&&
		((name = parse_relation()) != "")			        		&&
		tokenizer.consume_token("WHERE")		         			&&
		parse_condition();

	if(ret){
    cout << "Delete parsed.";
	}
	else tokenizer.backup();
	return ret;
}

string Parser::parse_attribute_name() {
  if(isid(tokenizer.get_token())) {
    tokenizer.index++;
    return tokenizer.get_token();
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
  }
  else {
    tokenizer.backup();
  }
  while(s != "") { // consume list and store in attrs
    attrs.push_back(s);
    s = parse_attribute_name();
  }
  return ret;
}

// sets attrs to the value of the attribute list
bool Parser::parse_typed_attribute_list() {
	string name;
 	tokenizer.checkpoint();
  bool ret = ((name = parse_attribute_name()) != "");
  
  while(tokenizer.consume_token(",")) parse_attribute_name();
  
  if(ret){

  }
  else tokenizer.backup();
  return ret;  
}

Type Parser::parse_type() {
	tokenizer.backup();
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
        tokenizer.consume_token(")")       ;
  if(!ret) {
    tokenizer.backup();
  }
  return ret;
}

bool Parser::parse_int_type() {
	tokenizer.checkpoint();
	string s;
	bool ret = tokenizer.consume_token("INTEGER")	&&
		((s = parse_literal()) != "")		          	&&
		s.find_first_not_of("0123456789") == std::string::npos; // this fragment lifted from Stack Overflow checks if is integer
	if (ret){
		//asdfasdf
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
	return s;
}

//--------------------//
//--HELPER FUNCTIONS--//
//--------------------//
bool Parser::isid(string id){
	return true;
}
