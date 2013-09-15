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

    vector<Attribute> attrs;
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

    bool parse_attribute_name();

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

    bool parse_type();

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
	return parse_atomic()      ||
           parse_selection()   ||
           parse_projection()  ||
           parse_renaming()    ||
           parse_union()       ||
           parse_difference()  ||
           parse_product()     ;
}

bool Parser::parse_atomic() {
	return true;
}

bool Parser::parse_selection() {
	return true;
}

bool Parser::parse_projection() {
	return true;
}

bool Parser::parse_renaming() {
	return true;
}

bool Parser::parse_union() {
	return true;
}

bool Parser::parse_difference() {
	return true;
}

bool Parser::parse_product() {
	return true;
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

bool Parser::parse_attribute_name() {
	return isid(tokenizer.get_token());
}


bool Parser::parse_attribute_list() {
	tokenizer.checkpoint();
	bool ret = parse_attribute_name();
	while(tokenizer.consume_token(",") && parse_attribute_name()) // consume list
		;
	if(!ret){
      tokenizer.backup();
      return true;
    }
    else {
	    return false;
    }
}

// may return data representing the contents of the list 
bool Parser::parse_typed_attribute_list() {
	tokenizer.checkpoint();
	bool ret = parse_attribute_name() && parse_type();
	while(tokenizer.consume_token(",") && parse_attribute_name() && parse_type()) // arbitrary number of name type pairs
		;
	if(!ret) {
	  tokenizer.backup();
	  return true;
	}
	else {
	  return false;
	}
 	
}

bool Parser::parse_type() {
	return true;
}
//--------------------//
//--HELPER FUNCTIONS--//
//--------------------//
bool Parser::isid(string id){
	return true;
}