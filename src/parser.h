// Parses tokenized expression
// 9/13/13

#pragma once

#include "Tokenizer.h"
#include "dbEngine.h"
#include <iostream>

using namespace std;

class DbEngine;

class Parser {
  public:
    Parser(string text);
    
    // The application will function with a bare minimum of create, insert, and select.


  	// main parsing function
  	// some parsing functions return a bool to indicate a sucessfull parse
  	// others return data that is the result of the parse
    bool parse();
  
    Tokenizer tokenizer;
    string command;
    DbEngine* db;

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
    
    string parse_op();

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

    bool parse_type();

    bool parse_int();

    bool parse_var_type();

    bool parse_int_type();

	string parse_literal();

    bool isid(string id); //helper function tests for valid identifier names, needs implementation currently returns true

};
