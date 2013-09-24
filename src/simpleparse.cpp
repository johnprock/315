#pragma once

#include "parser.h"
#include "Tokenizer.h"
#include "dbEngine.h"
#include <iostream>
#include <vector>

using namespace std;

class SimpleParser {

public:
  SimpleParser();

  // This simple parser integrates with the dbEngine and provides necessary core functions for building our application
	bool parse(string input);

  vector<Attribute> get_attrs(string input) {
    vector<Attribute> attrs;

    return attrs;
  }
private:
};

SimpleParser::SimpleParser(){}

SimpleParser::parse() {

        // CREATE
        if(input[0] == 'C') {
          // process Create Table

          // First we extract the table name
          int start = 13;
          int end = ( input.find("(") - 1 ); // name ends two spaces before first open paren
          string name = input.substr(start, end);
          cout << "Name string: " << input.substr(start end);

          // Then we get the Attributes, for now assume one attribute
          Vector<Attributes> attrs;
          start = input.find("(");
          end = input.find("P") - 1;
          cout << "Attr string: " << input.substr(start, end);
          attrs = get_attrs(input.substr(start, end));

          // Then we get the Primary Keys

          // Finally we make the dbengine call
        }

        // SHOW
        else if(input[0] == 'S') {

          // extract string name and call db show function
          string name;

        }

        // INSERT
        else if(input[0] == 'I') {
          
          // first we extract the name
        
          // then extract the values, for now assume one value

          // then make dbengine call
        }

        // SELECT
        else {

        }

        return true;
}


