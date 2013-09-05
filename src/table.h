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
    int size;
};

Type::Type() {
  size = -1; //for integer types we set an impossible size
}

Type::Type(int _size) {
  assert(_size > 0); //catch impossible sizes for varchars
  size = _size;
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
    string type;
};

Attribute::Attribute(int _val) {
  intVal = _val;
}

Attribute::Attribute(string _val, int _length) {
  stringVal = _val;
  length = _length;
}

//------------------//
//--Tuple CLASS--//
//------------------//


class Tuple {
  public:
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


