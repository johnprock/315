// Parses tokenized expression
// 9/13/13

#pragma once

#include "tokenizer.h"
using namespace std;

class Parser {
  public:
    Parser(string text);

  	// main parsing function
    bool parse();
  
  private:
    Tokenizer tokenizer;
    string command;

  	// parsing helper functions, called by parse()
  	// query parsing functions
  	bool parse_query();

    bool parse_relation();

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
	bool ret = parse_relation()                  && 
	           tokenizer.consume_token("<-")     && 
	           parse_expr()                      &&
	           tokenizer.consume_token(";")      ;
	// execute query code
	if(ret) {
		;
	}
    return ret;
}

bool Parser::parse_relation() {
	return isid(tokenizer.get_token());
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
	bool ret =  tokenizer.consume_token("CREATE TABLE") &&
	            parse_relation()                        &&
	            tokenizer.consume_token("(")            &&
	            parse_typed_attribute_list()            &&
	            tokenizer.consume_token(")")            &&
                tokenizer.consume_token("PRIMATY_KEY")  &&
                tokenizer.consume_token("(")            &&
                parse_attribute_list()                  &&
                tokenizer.consume_token(")")            ;
	if(ret){
	  ;	
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
	return true;
}

bool Parser::parse_typed_attribute_list() {
	bool ret = true;
	return ret;
}

//--------------------//
//--HELPER FUNCTIONS--//
//--------------------//
bool Parser::isid(string id){
	return true;
}