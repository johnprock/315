#pragma once

#include "dbEngine.h"
#include "table.h"
#include "parser.h"
#include <vector>
#include <iostream>
#include <fstream>


//---------------------------//
//--IMPLEMENTATIONS GO HERE--//
//---------------------------//

void DbEngine::createTable(string name, vector<Type> types) {
  Table new_table = Table(name, types);
  tables.push_back(new_table);
}


void DbEngine::Open(string directory) {
  ifstream myReadFile;
  myReadFile.open(directory.c_str());
  char output[1000];
  if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
                myReadFile >> output;
         }
  }
  Parser openfile = Parser(output);
  openfile.parse();
}

void DbEngine::Write(Table table) {
  // this will wait until we have a working parser
}

void DbEngine::Show(Table table) {
    table.show();
}

// set attributes in column attr_name to attr if they pass the test function f
// only updates one attribute at a time
void DbEngine::Update(Table table, string attr_name, Attribute attr, bool (*f)(Attribute)) {
  vector<Attribute> attrs = table.getColumn(attr_name);
  for(int i=0; i<attrs.size(); i++) {
    if((*f)(attrs[i]) == true) { // then we update
      table.replaceAttribute(attr_name, attr, i);
    }
  }
}

void DbEngine::Insert(Table table, Tuple tuple) {
    for(int i = 0; i < tables.size(); i++){
        if(tables[i].getname() == table.getname())
	    table.insert(tuple);
	}
}

void DbEngine::Delete(Table table) {
    for(int i = 0; i < tables.size(); i++){
	if(tables[i].getname() == table.getname())
		tables.erase(tables.begin()+i);
    }
}

void DbEngine::Delete(Table table, Tuple tuple) {
    vector<Tuple> tuples = table.gettuples();
    for(int i = 0; i < tables.size(); i++){
	if(tables[i].getname() == table.getname()){
		for(int j = 0; j < tuples.size(); j++){
			if(tuples[j] == tuple)
				tuples.erase(tuples.begin()+j);
		}
	}
    }
}

// selects all tuples whose attributes pass the testing function f
Table DbEngine::Select(Table table, string attr_name, bool (*f) (Attribute)) {
  Table new_table = Table(table.types); // this will be returned 

  // iterate down rows
  for(int i=0; i<table.tuples.size(); i++) {
    Tuple tuple = table.tuples[i];
    vector<Attribute> attrs = tuple.attributes;
    for(int j=0; j<attrs.size(); j++) {
      if(attrs[j].name == attr_name) {
        if( f(attrs[j]) ) {
          new_table.insert(tuple);
        }
      }
    }
  }
  return new_table;
}

void DbEngine::Project(Table table, Tuple attributes) {

}

// changes the name of every attribute
Table DbEngine::rename(vector<string> names, Table table) {
  // iterate down rows
  for(int i=0; i<table.tuples.size(); i++) {
    Tuple tuple = table.tuples[i];
     //iterate across columns
    for(int j=0; j<tuple.attributes.size(); j++) {
       Attribute attr = tuple.attributes[j];
        attr.name = names[j];
    }
  }
  return table;
}

void DbEngine::Close() {
  //ifstream myReadFile;
  //myReadFile.close();
}

int DbEngine::find(string name){
	for(int i = 0; i < tables.size(); i++){
		if (tables[i].name == name) return i;
	}
	return -1;
}
