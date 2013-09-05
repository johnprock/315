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
    void createTable(vector<Type>);
    //opens and imports the SQL of all files in a directory into our object structure (Tables, Attributes, Tuples)
    void DbEngine::Open(String directory_name);	

    //Writes a given table into SQL instruction to a file in the database
    void DbEngine::Write(Table table_name);

    //returns a formatted string to display the contents of a table.
    //This might should be handled by something other than DbEngine. Though its either this or the Application according
    //to our little diagram in the design.doc 
    string DbEngine::Show(Table table_name);


    //Updates an attribute in a given table and row.
    void DbEngine::Update(Table table_name, Tuple row, Attribute column);

    //Inserts a new Tuple into a Table
    void DbEngine::Insert(Table table_name, void* args);

    //Deletes an entire Table
    void DbEngine::Delete(Table table_name);

    //Deletes a Tuple in a Table
    void DbEngine::Delete(Table table_name, Tuple tuple_name);

    //returns a tuple containing only the specified tuples
    Table DbEngine::Select(Table table_name, Tuple tuple_name);

    //Returns a Table which is the projection of a table over a list of attributes
    void DbEngine::Project(Table table_name, Tuple attributes);

    //Renames a table
    void DbEngine::Rename(Table table_name);

    //The following overloaded operators probably need to be fixed. Its been a while since I've messed with operator overloading. 

    //Returns a Table that is the union of two Tables
    Table operator+(Table table_name1, Table table_name2);

    //returns the difference between two Tables
    Table operator-(Table table_name1, Table table_name2);

    //Returns a table that is the cartesian product of two tables
    Table operator*(Table table_name1, Table table_name2);
  private:
    vector<Table> tables;
};

void DbEngine::createTable(vector<Type> types){}
