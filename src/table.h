// Patrick Rock
// 9/3/2013
// Database Engine table and supporting classes 

#pragma once

#include <string>
using namespace std;


// An attribute is either an integer or a varchar
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

