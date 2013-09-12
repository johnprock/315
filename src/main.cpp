// Patrick Rock
// 9/3/2013
// Testing file for database engine

#include <iostream>
#include "table.h"
#include "dbEngine.h"
#include <vector>
#include "tokenizer.h"

bool f(Attribute a) {
	return true;
}

int main() {
  
  // Testing code  
  Attribute attr1 = Attribute(1, true, "attr1");
  Attribute attr2 = Attribute("attr", true, "attr2");
  Type type1 = Type(true);
  Type type2 = Type(2, true);

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
  
  //testing DbEngine interface
  DbEngine db;
  vector<Type> type_vector;
  type_vector.push_back(Type(true));
  type_vector.push_back(Type(2, true));
  db.createTable("test_table", type_vector);
  db.Show(db.tables[0]);
  
  //testing union function
  Attribute attr3 = Attribute(4, true, "attr3");
  Attribute attr4 = Attribute("BOLG", true, "attr4");
  
  vector<Attribute> attrs3;
  attrs3.push_back(attr3);
  attrs3.push_back(attr4);

  vector<Attribute> attrs4;
  attrs4.push_back(attr4);
  attrs4.push_back(attr3);
  
  Tuple tuple3 = Tuple(attrs3);
  Tuple tuple4 = Tuple(attrs4);
  
  vector<Tuple> tuples2;
  tuples2.push_back(tuple3);
  tuples2.push_back(tuple4);
  
  Table table2 = Table("test_table2", tuples2);
  table2.show();
  
  //testing union
  Table table3 = table + table2; 
  table3.show();
  
  //testing insert
  vector<Attribute> attrs5;
  attrs5.push_back(attr1);
  attrs5.push_back(attr4);
  Tuple tuple5 = Tuple(attrs5);
  table3.insert(tuple5);
  table3.show();

  // testing select
  cout << "Selecting...";
  db.Select(table2, "attr3", f);
  cout << "done.\n";

  // testing update
  cout << "Updating...";
  db.Update(table2, "attr3", attr4, f);
  cout << "done.\n";
  
  // testing rename
  vector<string> names;
  names.push_back("test1");
  names.push_back("test2");
  cout << "Renaming...";
  db.rename(names, table2);
  cout << " done.\n";  
  
  //testing difference
  cout<<"table1\n================\n";
  table2.insert(tuple1);
  table2.insert(tuple1);
  table2.insert(tuple5);
  table2.show();
  cout<<"table2\n================\n";
  table.show();
  cout<<"new table - table 2 is\n\n";
  table3 = table2-table;
  table3.show();
  
  //testing cartesian product
  table3 = table*table2;
  table3.show(); 

  cout<<"\n\n\ntokenizer test\n========================\n";
  string test_string = "OPEN a dude3 up 3 times +!=> %$blah";
  tokenizer T = tokenizer(&test_string);
  for(int i = 0; i < T.tokens.size(); i++) cout<<T.tokens[i]<<'\n';
  return 0;
}


