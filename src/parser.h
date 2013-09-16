// Parses tokenized expression
// 9/13/13

#pragma once

#include "tokenizer.h"
#include "dbEngine.h"
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

    bool parse_conjuction();

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

    string parse_type();

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
	return parse_atomic()  ||
           parse_selection()   ||
           parse_projection()  ||
           parse_renaming()    ||
           parse_union()       ||
           parse_difference()  ||
           parse_product()     ;
}

bool Parser::parse_atomic() {
	tokenizer.checkpoint();

	bool ret =  parse_relation() ||
		    parse_expr() ;
	if(ret){
	    //????
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
	  //execute db engine calls
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
	  //execute db engine calls
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
	  //execute db engine calls
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
	            parse_atomic()                                    &&
	if(ret){
	  //execute db engine calls	
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
	            parse_atomic()                                    &&
	if(ret){
	  //execute db engine calls	
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
	            parse_atomic()                                    &&
	if(ret){
	  //execute db engine calls	
	}
	else {
		tokenizer.backup();
	}
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
	return true;
}

bool Parser::parse_close() {
	return true;
}

bool Parser::parse_write() {
	return true;
}

bool Parser::parse_exit() {
	return true;
}

bool Parser::parse_show() {
	return true;
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
	return true;
}

bool Parser::parse_insert() {
    return true;
}

bool Parser::parse_delete() {
	return true;
}

string Parser::parse_attribute_name() {
  if(isid(tokenizer.get_token()))
    return tokenizer.get_token();
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
  while(s != "") { // consume list and store in attrs
    attrs.push_back(s);
    s = parse_attribute_name();
  }
  return ret;
}

// sets attrs to the value of the attribute list
bool Parser::parse_typed_attribute_list() {
 	tokenizer.checkpoint();
  bool ret;
  string name;
  string type;
  typed_attrs = vector<Attribute>();

  name = parse_attribute_name();
  type = parse_type();

}

string Parser::parse_type() {
	return "";
}
//--------------------//
//--HELPER FUNCTIONS--//
//--------------------//
bool Parser::isid(string id){
	return true;
}
