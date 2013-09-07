#include "table.h"

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
