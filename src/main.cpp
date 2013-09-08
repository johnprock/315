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

  vector<Attribute> attrs1;
  attrs1.push_back(attr1);
  attrs1.push_back(attr2);

  vector<Attribute> attrs2;
  attrs2.push_back(attr2);
  attrs2.push_back(attr1);

  Tuple tuple1 = Tuple(attrs1);
  Tuple tuple2 = Tuple(attrs2);
   
  vector<Tuple> tuples;
  tuples.push_back(tuple1);
  tuples.push_back(tuple2);
  
  Table table = Table("test", tuples);


  //attr1.show();
  //tuple1.show();
  table.show();

  return 0;
}
