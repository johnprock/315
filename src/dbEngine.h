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
    void Open(string directory_name);	

    //Writes a given table into SQL instruction to a file in the database
    void Write(Table table_name);

    // Shows requested table
    void Show(Table table);


    //Updates an attribute in a given table and row.
    void Update(Table table_name, Tuple row, Attribute column);

    //Inserts a new Tuple into a Table
    void Insert(Table table_name, void* args);

    //Deletes an entire Table
    void Delete(Table table_name);

    //Deletes a Tuple in a Table
    void Delete(Table table_name, Tuple tuple_name);

    //returns a tuple containing only the specified tuples
    Table Select(Table table_name, Tuple tuple_name);

    //Returns a Table which is the projection of a table over a list of attributes
    void Project(Table table_name, Tuple attributes);

    //Renames a table
    void Rename(Table table_name);

    //The following overloaded operators probably need to be fixed. Its been a while since I've messed with operator overloading. 

    //Returns a Table that is the union of two Tables
    Table operator+(Table table);

    //returns the difference between two Tables
    Table operator-(Table table);

    //Returns a table that is the cartesian product of two tables
    Table operator*(Table table);

  private:
    vector<Table> tables;
};

//---------------------------//
//--IMPLEMENTATIONS GO HERE--//
//---------------------------//

void DbEngine::createTable(string name, vector<Type> types) {
  Table new_table = Table(name, types);
  tables.push_back(new_table);
}


void DbEngine::Open(string directory_name) {
  //to be implemented
}

void DbEngine::Write(Table table_name) {
  //to be implemented
}

void DbEngine::Show(Table table) {
    table.show();
}

void DbEngine::Update(Table table_name, Tuple row, Attribute column) {

}

void DbEngine::Insert(Table table_name, void* args) {

}

void DbEngine::Delete(Table table_name) {

}

void DbEngine::Delete(Table table_name, Tuple tuple_name) {

}

Table DbEngine::Select(Table table_name, Tuple tuple_name) {

}

void DbEngine::Project(Table table_name, Tuple attributes) {

}

void DbEngine::Rename(Table table_name) {
    
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
