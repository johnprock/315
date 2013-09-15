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

    bool parse_atomic_expr();

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
