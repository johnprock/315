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

//-------------------//
//--ATTRIBUTE CLASS--//
//-------------------//

class Attribute {
  public:
    Attribute(int);
    Attribute(string, int);
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
//--Tuple CLASS--//
//---------------//


class Tuple {
  public:
    Tuple(vector<Type>);
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

    //getter's
    Tuple getTuple(int);
    vector<Type> getTypes();
  private:
    string name;
    vector<Tuple> tuples;
    vector<Type> types;
};

Table::Table(string, vector<Type>) {
}

Table::Table(vector<Type>){
}

Tuple Table::getTuple(int index){
    return tuples[index];
}

vector<Type> Table::getTypes(){
    return types;
}
