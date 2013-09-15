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
    int i; //stores position in token stream

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

};

Parser::Parser(string _command) {
	command = _command;
	tokenizer = Tokenizer(&command); 
}

bool Parser::parse() {
	return parse_command() || parse_query();
}

//query parsing functions
bool Parser::parse_query() {
	bool ret = parse_relation() && tokenizer.tokens[i] == "<-" && parse_expr();
	// execute query code
    return ret;
}

bool Parser::parse_relation() {
	return true;
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

//command parsing funtions
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
	return true;
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

