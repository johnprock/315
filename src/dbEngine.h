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
    Table Select(Table table, bool (*f)(Attribute));

    //Returns a Table which is the projection of a table over a list of attributes
    void Project(Table table, Tuple attributes);

    //Renames a table
    Table Rename(vector<string>, Table table);

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
	else
	    i++;
	}
}

void DbEngine::Delete(Table table) {
    for(int i = 0; i < tables.size(); i++){
	if(tables[i].getname() == table.getname())
		tables.erase(tables.begin()+i);
	else
		i++;
    }
}

void DbEngine::Delete(Table table, Tuple tuple) {
    vector<Tuple> tuples = table.gettuples();
    for(int i = 0; i < tables.size(); i++){
	if(tables[i].getname() == table.getname()){
		for(int j = 0; j < tuples.size(); j++){
			if(tuples[j] == tuple)
				tuples.erase(tuples.begin()+j);
			else
				j++;
		}
	}
	else
		i++;
    }
}

Table DbEngine::Select(Table table, bool (*f)(Attribute)) {

}

void DbEngine::Project(Table table, Tuple attributes) {

}

Table DbEngine::Rename(vector<string>, Table table) {

}

void DbEngine::Close() {

}




// We may not need these operators...

// THIS FUNCTION IS BROKEN, OPERATORS ONLY TAKE ONE ARGUMENT!
//Returns a Table that is the union of two Tables
/* Table DbEngine::operator+(Table table){
  //check for union-compatibility first
  if(table1.getTypes().size() == table2.getTypes().size(){
    for(int i = 0; i < table1.getTypes().size(); i++){
      if(!(table1.getTypes()[i] == table1.getTypes[i]))            //if table1 and table2 are not equal
        std::cout<<"The tables are not union compatible\n";
    }
  }
  else{
    Table temp = Table(table1.getTypes());
    for (int i = 0; i < table1.size(); i++){
      temp.insert(table1.getTupel(i);
    }
    for (int i = 0; i < table2.size(); i++){
      temp.insert(table2.getTupel(i);
    }
  }
}*/

//returns the difference between two Tables
Table DbEngine::operator-(Table table){

}

//Returns a table that is the cartesian product of two tables
Table DbEngine::operator*(Table table){

}
