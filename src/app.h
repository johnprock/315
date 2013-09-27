// Patrick Rock
// 9/25/2013

#include <iostream>


// This class represents the final application
// This app is a grocery list tracking system
class App {

  //members
  DbEngine db;

public:
  // constructor
  App();

  // initialize the application and start user dialogue
  void init();

  // creates a new grocery list 
  void create();

  // removes a grocery list
  void remove();

  // shows all of the lists in the 
  void show();

};

App::App(){
  db = DbEngine();
}

void App::create(){
  string name;
  int num_attr;
  int datatype;
  int field_length;
  string attr_name;
  
  vector<Type> types;
  
  
  using namespace std; 
  
  cout<<"List name:\n";
  cin >> name;
  cout<<"\nHow many attributes?\n";
  cin >> num_attr;
  for(int i = 0; i < num_attr; i++){
    cout<<"\n Attribute Type:\n1. for INTEGER\n2. for VARCHAR\n";
    cin >> datatype;
    if(datatype == 1){
      Type temp_type = Type(false);
      types.push_back(temp_type);
    }
    else{
      cout<<"\nDatafield Size:\n";
      cin >> field_length;
      Type temp_type = Type(field_length, false);
      types.push_back(temp_type);
    }
  }
  db.createTable(name, types);
}

void App::init(){
  
}
