#pragma once

#include "parser.h"
#include "Tokenizer.h"
#include "dbEngine.h"
#include <iostream>

using namespace std;

class SimpleParser {

    SimpleParser() {

    }

	bool parse(string input) {
		    // create
        if(input[0] == 'C') {
          // call dbengine
        }

        // insert
        else if(input[0] == 'I') {
          // call dbengine
        }

        // select
        else {
          //call dbengine
        }

        return true;
	}
};