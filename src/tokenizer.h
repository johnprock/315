//class tokenizer, tokenizes a string

#include <string>
#include <vector>

using namespace std;

class tokenizer{
  public:
    //constructor actually does the tokenizer
    tokenizer(string * text);
    vector<string> tokens;
  private:
    int position;
    bool match(string * text, int position , string exp);
};

tokenizer::tokenizer(string * text){
    //all possible tokens
      //OPEN
      //CLOSE
      //WRITE
      //EXIT
      //SHOW
      //CREATE TABLE
      //PRIMARY KEY
      //UPDATE
      //SET
      //WHERE 
      //INSERT INTO
      //VALUES FROM
      //VALUES FROM RELATION 
      //SELECT
      //PROJECT
      //RENAME
      //DELETE FROM
      //operators: == <- != < > <= >= + - *  ( ) 
      //literals: VARCHAR INTEGER
  for(int position = 0; position < text->size(); position++){
  char c = (*text)[position];
  switch (c){
    case 'O':
      if(match(text, position, "OPEN")){
        tokens.push_back("OPEN");
        position += 4;
      }
      break;
    case 'C':
      if(match(text, position, "CLOSE")){
        tokens.push_back("CLOSE");
        position += 5;
      }
      if(match(text, position, "CREATE TABLE")){
        tokens.push_back("CREATE TABLE");
        position += 12;
      }
      break;
    case 'W':
      //WRITE
      //WHERE
    case 'E':
      //EXIT
    case 'S':
      //SHOW
      //SET
      //SELECT
    case 'P':
      //PRIMARY KEY
      //PROJECT
    case 'U':
      //UPDATE
    case 'I':
      //INSERT INTO
    case 'V':
      //VALUES FROM
      //VALUES FROM RELATION
    case 'R':
      //RENAME
    case 'D':
      //DELETE FROM
    case '=':
      //==
    case '<': 
    //test
      //<-
      //<
      //<=
    case '!':
      //!=
    case '>':
      //>
      //>=
    case '+':
    case '-':
    case '*':
    case '(':
    case ')':;
  }
}
}

bool tokenizer::match(string * text, int position, string exp){
  string substring = text->substr(position, exp.size());
  if (substring == exp) return true;
  else return false;
}
