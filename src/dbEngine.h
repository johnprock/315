// Patrick Rock
// 9/5/2013
// Database Engine Header

#include "table.h"
#include <vector>
using namespace std;

//-------------------------//
//--DATABASE ENGINE CLASS--//
//-------------------------//

class DbEngine {
  public:
    
    // The relation stored in the table has types equivilant to those in the argument vector
    void createTable(string name, vector<Type> types);
    
    //opens and imports the SQL of all files in a directory into our object structure (Tables, Attributes, Tuples)
    void Open(string directory);	

    //Writes a given table into SQL instruction to a file in the database
    void Write(Table table);

    //Closes the current database session
    void Close();

    // Shows requested table
    void Show(Table table);

    //Updates an attribute in a given table and row.
    void Update(Table table, string attr_name, Attribute attr, bool (*f)(Attribute));

    //Inserts a new Tuple into a Table
    void Insert(Table table, Tuple tuple);

    //Deletes an entire Table
    void Delete(Table table);

    //Deletes a Tuple in a Table
    void Delete(Table table, Tuple tuple);

    //returns a tuple containing only the specified tuples
    // takes an attribute name and a function pointer
    // the function tests the attribute and decides if it should be selected
    Table Select(Table table, string attr_name, bool (*f) (Attribute));

    //Returns a Table which is the projection of a table over a list of attributes
    void Project(Table table, Tuple attributes);

    //Replaces the attribute names in the table with new_attribute_names
    Table rename(vector<string> new_attr_names, Table table);

    //The following overloaded operators probably need to be fixed. Its been a while since I've messed with operator overloading. 

    //Returns a Table that is the union of two Tables
    Table operator+(Table table);

    //returns the difference between two Tables
    Table operator-(Table table);

    //Returns a table that is the cartesian product of two tables
    Table operator*(Table table);
    

  //private: //i made this public to get DbEngine.Show() to work. This is gross. 
    vector<Table> tables;
};

//---------------------------//
//--IMPLEMENTATIONS GO HERE--//
//---------------------------//

void DbEngine::createTable(string name, vector<Type> types) {
  Table new_table = Table(name, types);
  tables.push_back(new_table);
}


void DbEngine::Open(string directory) {
  // this will wait until we have a working parser
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

}
