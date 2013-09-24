// Patrick Rock
// 9/5/2013
// Database Engine Header
#pragma once

#include "table.h"
#include "parser.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Parser;

//-------------------------//
//--DATABASE ENGINE CLASS--//
//-------------------------//

class DbEngine {
  public:
    //DbEngine(){};
    //Parser openfile;
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
    
    //finds a table in the tables vector by its name
    int find(string name);
    

  //private: //i made this public to get DbEngine.Show() to work. This is gross. 
    vector<Table> tables;
};