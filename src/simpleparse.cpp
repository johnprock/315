#pragma once

#include "parser.h"
#include "Tokenizer.h"
#include "dbEngine.h"
#include <iostream>

using namespace std;

class SimpleParser {

    SimpleParser() {

    }

  // This simple parser integrates with the dbEngine and provides necessary core functions for building our application
	bool parse(string input) {

		    // CREATE
        if(input[0] == 'C') {
          // process Create Table

          // First we extract the table name
          int start = 13;
          int end = ( input.find("(") - 2 ); // name ends two spaces before first open paren
          string name;

          // Then we get the Attributes, for now assume one attribute
          Attibute attr;



          // Then we get the Primary Keys

          // Finally we make the dbengine call
        }

        // SHOW
        else if(input[0] == 'S') {

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
};