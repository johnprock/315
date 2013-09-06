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
};

//---------------//
//--TABLE CLASS--//
//---------------//

class Table {
  public:
  private:
    vector<Tuple> tuples;
};


