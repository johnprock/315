// Patrick Rock
// 9/3/2013
// Database Engine table and supporting classes 

#pragma once

#include <string>
#include <vector>
#include <assert.h>
using namespace std;


//--------------//
//--TYPE CLASS--//
//--------------//

class Type{
  public:
    Type();     //constructor for integer type
    Type(int);  //constructor for varchar type
    bool isInt();
    int isVarchar();
    bool operator==(Type);
  private:
    int length;
};

Type::Type() {
  length = -1; //for integer types we set an impossible size
}

Type::Type(int _length) {
  assert(_length > 0); //catch impossible sizes for varchars
  length = _length;
}

bool Type::operator==(Type){
  return true;          //lol, dont breathe this. 
}

//-------------------//
//--ATTRIBUTE CLASS--//
//-------------------//

class Attribute {
  public:
    inline Attribute(int);
    inline Attribute(string, int);
  private:
    int intVal;
    int length;
    string stringVal;
    Type type;
};

Attribute::Attribute(int _val) {
  intVal = _val;
  type = Type();
}

Attribute::Attribute(string _val, int _length) {
  stringVal = _val;
  length = _length;
  type = Type(length);
}

//---------------//
//--TUPLE CLASS--//
//---------------//


class Tuple {
  public:
    inline Tuple(vector<Type>);
  private:
    vector<Attribute> attributes;
    vector<Type> types;
};

Tuple::Tuple(vector<Type> _types) {
  types = _types;
}

//---------------//
//--TABLE CLASS--//
//---------------//

class Table {
  public:
    Table(string, vector<Type>); // the table constructor takes as an argument a list of types that
                                 // that are present in the rows
    Table(vector<Type>);

    //Returns a Table that is the union of two Tables
    Table operator+(Table table);

    //returns the difference between two Tables
    Table operator-(Table table);

    //Returns a table that is the cartesian product of two tables
    Table operator*(Table table);

    //Inserts a new Tuple into a Table
    void insert(Tuple new_tuple);

  private:
    string name;
    vector<Tuple> tuples;
    vector<Type> types;
};

Table::Table(string, vector<Type>){
}

Table::Table(vector<Type>){
}

//Inserts a new Tuple into a Table
void Table::insert(Tuple new_tuple){
  tuples.push_back(new_tuple);
}

//Returns a Table that is the union of two Tables
Table Table::operator+(Table table){
  //check for union-compatibility first
  if(tuples.size() == table.tuples.size()){
    int i = 0;
    while(i < types.size()){
      if(types[i] == table.types[i]){           //if table1 and table2 are not equal
        std::cout<<"The tables are not union compatible\n";
	break;
      }
    }
  }
  else{
    Table temp = Table(table.types);
    for (int i = 0; i < tuples.size(); i++){
      temp.insert(tuples[i]);
    }
    for (int i = 0; i < table.tuples.size(); i++){
      temp.insert(table.tuples[i]);
    }
    return temp;
  }
}

//returns the difference between two Tables
Table Table::operator-(Table table){

}

//Returns a table that is the cartesian product of two tables
Table Table::operator*(Table table){

}
