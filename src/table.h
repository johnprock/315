// Patrick Rock
// 9/3/2013
// Database Engine table and supporting classes 

#pragma once

#include <string>
#include <vector>
#include <assert.h>
#include <iostream>
using namespace std;


//--------------//
//--TYPE CLASS--//
//--------------//

class Type{
  public:
    Type();
    Type(bool);     //constructor for integer type
    Type(int, bool);  //constructor for varchar type
    bool isInt();
    int isVarchar();
    bool operator==(Type);
    bool isPrimary();

    int length;
    bool primary; //is this a primary key
};

Type::Type() {

}

Type::Type(bool _prime) {
  length = -1; //for integer types we set an impossible size
  primary = _prime;
}

Type::Type(int _length, bool _prime) {
  assert(_length > 0); //catch impossible sizes for varchars
  length = _length;
  primary = _prime;
}

bool Type::isInt(){
  if (length == -1) return true;
  return false;
}

int Type::isVarchar(){
  return length;
}

bool Type::operator==(Type type){
  if(length == type.length) return true;
  else return false; 
}

bool Type::isPrimary() {
  return primary;
}

//-------------------//
//--ATTRIBUTE CLASS--//
//-------------------//

class Attribute {
  public:
    inline Attribute(int, bool, string);
    inline Attribute(string, bool, string);
    bool operator==(Attribute);
    void show(); // used to display contents of database and debugging
    Type get_type();
    string get_name();

    int intVal;
    int length;
    string stringVal;
    Type type;
    string name;  // assume attributes have unique names
};

string Attribute::get_name() {
  return name;
}

Type Attribute::get_type() {
  return type;
}

Attribute::Attribute(int _val, bool prime, string _name) {
  intVal = _val;
  type = Type(prime);
  name = _name;
}

Attribute::Attribute(string _val, bool prime, string _name) {
  stringVal = _val;
  length = _val.length();
  type = Type(length, prime);
  name = _name;
}

bool Attribute::operator==(Attribute attribute){
  if(type.isInt()){
    if(intVal == attribute.intVal) return true;
  }
  else if(stringVal == attribute.stringVal) return true;
  else return false;
}
  
  void Attribute::show() {
    if(type.isInt()) {
      cout << intVal;
    }
    else {
      cout << stringVal;
    }
  }

//---------------//
//--TUPLE CLASS--//
//---------------//


class Tuple {
  public:
    inline Tuple(vector<Type>); // used for empty tuples
    Tuple(vector<Attribute>);   // used to initialize full tuple
    bool operator==(Tuple);
    void show(); 
    vector<Type> get_types();
    vector<Attribute> get_attributes();
    int getSize();
    int replaceAttribute(string attr_name, Attribute attr);
  
    vector<Attribute> attributes;
    vector<Type> types;
};

int Tuple::replaceAttribute(string attr_name, Attribute attr) {

  for(int i=0; i<attributes.size(); i++) {
    if(attributes[i].get_name() == attr_name) {
        attributes[i] = attr;
    }
  }
}

vector<Attribute> Tuple::get_attributes() {
  return attributes;
}

Tuple::Tuple(vector<Type> _types) {
  types = _types;
}

Tuple::Tuple(vector<Attribute> _attributes) {
  attributes = _attributes;
  for(int i=0; i<attributes.size(); i++) {
    types.push_back(attributes[i].get_type());
  }
}

int Tuple::getSize(){
  return attributes.size();
}

vector<Type> Tuple::get_types() {
  return types;
}

bool Tuple::operator==(Tuple tuple){
  //check size first
  if(attributes.size() == tuple.attributes.size()){
    for(int i = 0; i < attributes.size(); i++){
      if(!(attributes[i] == tuple.attributes[i])) return false;
    }
    return true;
  }
  else return false;
}

void Tuple::show() {
  for(int i=0; i<attributes.size(); i++) {
    attributes[i].show();
    cout << " ";
  }
}

//---------------//
//--TABLE CLASS--//
//---------------//
// Currently the names of attributes is stored in the attributes themselves. The names should be stored in the Table as well?

class Table {
  public:
    Table(string, vector<Type>); // the table constructor takes as an argument a list of types that
                                 // that are present in the rows
    Table(vector<Type>);         //for a blank table

    Table(string, vector<Tuple>);        //initialize a full table

    //Returns a Table that is the union of two Tables
    Table operator+(Table table);

    //returns the difference between two Tables
    Table operator-(Table table);

    //Returns a table that is the cartesian product of two tables
    Table operator*(Table table);
    
    //copies a table to a new table
   // Table operator=(Table table); This is breaking the code

    //Inserts a new Tuple into a Table
    void insert(Tuple new_tuple);
    
    //Deletes a Tuple in a Table
    void remove(Tuple tuple_name);

    //Returns Table name
    string getname();

    //Returns the Tuples vector
    vector<Tuple> gettuples();

    void show();

    //Returns the column corresponding to that attribute name in the table
    vector<Attribute> getColumn(string attr_name);

    // returns 0 if the attribute is successfully changed, 1 for failure
    int replaceAttribute(string attr_name, Attribute attr, int tuple);

    
    string name;
    vector<Tuple> tuples;
    vector<Type> types;
};

int Table::replaceAttribute(string attr_name, Attribute attr, int tuple) {
  tuples[tuple].replaceAttribute(attr_name, attr);
}

vector<Attribute> Table::getColumn(string attr_name) {
  vector<Attribute> col;

  // iterate down rows
  for(int i=0; i<tuples.size(); i++) {
    Tuple tup = tuples[i];
    vector<Attribute> attrs = tup.get_attributes();
    
    // iterate across columns
    for(int j=0; j<attrs.size(); j++) {
      if(attrs[j].get_name() == attr_name) {
        col.push_back(attrs[j]);
      }
    }
  }
  return col;
}

void Table::show() {
  cout << "Table: " << name << "\n\n";
  for(int i=0; i<tuples.size(); i++){
    tuples[i].show();
    cout << "\n";
  }
}

Table::Table(string _name, vector<Tuple> _tuples) {
  tuples = _tuples;
  name = _name;
  types = _tuples[0].get_types(); // assume all tuples have the same types, might check this later
}

Table::Table(string _name, vector<Type> _types){
  name = _name;
  types = _types;
}

Table::Table(vector<Type> _types){
  types = _types;
}

//Inserts a new Tuple into a Table
void Table::insert(Tuple new_tuple){
  tuples.push_back(new_tuple);
}

//Deletes a Tuple in a Table
void Table::remove(Tuple _tuple){
  for(std::vector<Tuple>::iterator it = tuples.begin(); it != tuples.end(); ++it) {
    if(*it == _tuple) tuples.erase(it);
  }
}

//Returns the name of the Table
string Table::getname(){
      return name;
}

//Returns the tuples vector
vector<Tuple> Table::gettuples(){
	return tuples;
}

//Returns a Table that is the union of two Tables
Table Table::operator+(Table table){
  //check for union-compatibility first
  if(tuples.size() == table.tuples.size()){
    for(int i = 0; i < types.size(); i++){
      if(!(types[i] == table.types[i])){           //if table1 and table2 are not equal
        std::cout<<"The tables are not union compatible\n";
        break;
      }
    }
    Table temp = Table(table.types);
    for (int i = 0; i < tuples.size(); i++){
      temp.insert(tuples[i]);
    }
    for (int i = 0; i < table.tuples.size(); i++){
      temp.insert(table.tuples[i]);
    }
    return temp;
  }
  else{
    std::cout<<"The tables are not union compatible\n";
  }
  return table;         //WATCH OUT FOR THIS. returns the rhs table if they are not-union compatible
}

//returns the difference between two Tables
Table Table::operator-(Table table){
  //check for union-compatibility first
  if(tuples[0].getSize() == table.tuples[0].getSize()){
    for(int i = 0; i < types.size(); i++){
      if(!(types[i] == table.types[i])){           //if table1 and table2 are not equal
        std::cout<<"The tables are not union compatible\n";
        break;
      }
    }
    Table temp = Table(tuples[0].get_types());    //make a copy of the left-hand-side table using DEFAULT copy constructor.
    for(int i = 0; i < tuples.size(); i++) temp.insert(tuples[i]);
    for (int i = 0; i < temp.tuples.size(); i++){
      for(int j = 0; j < tuples.size(); j++){
        if (temp.tuples[j] == table.tuples[i]){
           temp.remove(tuples[j]);
         }
      }
    }
    return temp;
  }
  else{
    std::cout<<"The tables are not union compatible\n";
  }
  return table;         //WATCH OUT FOR THIS. returns the rhs table if they are not-union compatible
}

//Returns a table that is the cartesian product of two tables
Table Table::operator*(Table table){
	//create a new vector of all the types in both tables
	vector<Type> new_types;
	for(int i = 0; i < tuples[0].types.size(); i++) new_types.push_back(tuples[0].types[i]);
	for(int i = 0; i < table.tuples[0].types.size(); i++) new_types.push_back(table.tuples[0].types[i]);
	
	//create the new table to be returned
	Table temp = Table(new_types);
	//new attribute vector for new tuple
	vector<Attribute> new_attributes;
	for(int i = 0; i < tuples.size(); i++){
		for(int j = 0; j < table.tuples.size(); j++){
			//create a new tuple
			for(int k = 0; k < tuples.size(); k++){
         new_attributes.push_back(tuples[i].attributes[k]);
       }
			for(int k = 0; k < table.tuples.size(); k++){
         new_attributes.push_back(table.tuples[j].attributes[k]);
       }
			Tuple new_tuple = Tuple(new_attributes);
		}
	}
	return temp;
}
