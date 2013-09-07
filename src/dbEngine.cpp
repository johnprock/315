#include <iostream>

//Returns a Table that is the union of two Tables
Table DbEngine::operator+(Table table1, Table table2){
  //check for union-compatibility first
  if(table1.getTypes().size() == table2.getTypes().size(){
    for(int i = 0; i < table1.getTypes().size(); i++){
      if(!(table1.getTypes()[i] == table1.getTypes[i]))            //if table1 and table2 are not equal
        std::cout<<"The tables are not union compatible\n";
    }
  }
  else{
    Table temp = Table(table1.getTypes());
    for (int i = 0; i < table1.size(); i++){
      temp.insert(table1.getTupel(i);
    }
    for (int i = 0; i < table2.size(); i++){
      temp.insert(table2.getTupel(i);
    }
  }
}

//returns the difference between two Tables
Table DbEngine::operator-(Table table){

}

//Returns a table that is the cartesian product of two tables
Table DbEngine::operator*(Table table){

}
