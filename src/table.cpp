#include <iostream>
#include "table.h"

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
    for (int i = 0; i < size(); i++){
      temp.insert(tuples[i]);
    }
    for (int i = 0; i < table.size(); i++){
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
