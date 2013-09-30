// Patrick Rock
// 9/25/2013

#include <iostream>
#include <vector>

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

// reads in the name of a table then calls db code to remove
void App::remove(){
  string name;
  cout << "Which list would you like to delete? ";
  cin >> name;
  int tableIndex = db.find(name);
  if(tableIndex == -1) {
    cout << "The list you have named does not exist.\n";
  }
  else {
    cout << "Working... ";
    db.Delete(db.tables[tableIndex]);
    cout << "List deleted.\n";
  }
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
  cout<<"\nHow many items?\n";
  cin >> num_attr;
  for(int i = 0; i < num_attr; i++){
    cout<<"\nItem Type:\n1. for INTEGER\n2. for VARCHAR\n";
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
  int tableIndex = db.find(name);
  Table table = db.tables[tableIndex];
  vector<Attribute> attrs; // holds user input and builds tuple for insertion 
  int ival;      // holds integer input
  string sval;   // holds string input

  // now we populate table with values
  // iterate through the list of types and build a tuple for insertion
  for(int i=0; i<table.types.size(); i++) {
   
    cout << "\nEnter the " << i << "th item: ";
   
    if(table.types[i].isInt()) {
      cin >> ival;
      attrs.push_back(Attribute(ival, true, "item"));   
    }
   
    else {
      cin >> sval;
      attrs.push_back(Attribute(sval, true, "item")); 
    }
  }
  
  // build tuple and insert
  Tuple tuple = Tuple(attrs);  
  db.Insert(table, tuple);
  cout << "\nDone.\n";
}

void App::show(){
  cout << "Retrieving lists...\n\n";
  if(db.tables.size() == 0){
    cout << "Database is empty, no lists to show.\n\n";
  }
  else{
    for(int i = 0; i<db.tables.size(); i++){
      db.Show(db.tables[i]);
    }
  }  
}

void App::init(){
  char choice;
  App app = App();
  bool loop = true;

  while(loop) {
    cout << "Please choose from the options listed below: \n\n"
       << "1. Create New List \n"
       << "2. Show Lists \n"
       << "3. Remove List \n"
       << "4. EXIT \n";
    cin >> choice;
    cout << "\n\n";
    switch(choice){
      case '1':
        app.create();
        break;
      case '2':
        app.show();
        break;
      case '3':
        app.remove();
        break;
      case '4':
        loop = false;
        break;
      default:
        cout << "Not a valid entry.\n\n";
        app.init();
        break;
    }
  }
}
