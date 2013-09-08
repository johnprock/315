// Patrick Rock
// 9/3/2013
// Testing file for database engine

#include <iostream>
#include "table.h"
#include "dbEngine.h"
#include <vector>

int main() {
  
  // Testing code  
  Attribute attr1 = Attribute(1);
  Attribute attr2 = Attribute("attr");
  Type type1 = Type();
  Type type2 = Type(2);

  vector<Attribute> attrs;
  attrs.push_back(attr1);
  attrs.push_back(attr2);

  Tuple tuple1 = Tuple(attrs);
   
  //attr1.show();
  tuple1.show();

  return 0;
}
