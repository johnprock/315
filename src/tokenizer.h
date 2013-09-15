//class Tokenizer, tokenizes a string
#pragma once

#include <string>
#include <vector>

using namespace std;

class Tokenizer{
  public:
    //constructor actually does the Tokenizer
    Tokenizer(string * text);
    Tokenizer();
    vector<string> tokens;
    string consume_token(); //returns the token at the current index and increments the index
    int index;
  private:
    int position;
    bool match(string * text, int position , string exp);
    string get_integer(string * text, int position);
    string get_varchar(string * text, int position);
};

Tokenizer::Tokenizer(){}

string Tokenizer::consume_token() {
  if(index = tokens.size()) {
    return "END OF STREAM";
  }
  else {
    index++;
    return tokens[index];
  }
}

Tokenizer::Tokenizer(string * text){
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
      position = 0;
      index = 0;
  while(position < text->size()){
  char c = (*text)[position];
  switch (c){
    case 'O':
      if(match(text, position, "OPEN")){
        tokens.push_back("OPEN");
        position += 4;
        break;
      }
    case 'C':
      if(match(text, position, "CLOSE")){
        tokens.push_back("CLOSE");
        position += 5;
        break;
      }
      if(match(text, position, "CREATE TABLE")){
        tokens.push_back("CREATE TABLE");
        position += 12;
        break;
      }
    case 'W':
      if(match(text, position, "WRITE")){
        tokens.push_back("WRITE");
        position += 5;
        break;
      }
      if(match(text, position, "WHERE")){
        tokens.push_back("WHERE");
        position += 5;
        break;
      }
    case 'E':
      if(match(text, position, "EXIT")){
        tokens.push_back("EXIT");
        position += 4;
        break;
      }
    case 'S':
      if(match(text, position, "SHOW")){
        tokens.push_back("SHOW");
        position += 4;
        break;
      }
      if(match(text, position, "SET")){
        tokens.push_back("SET");
        position += 3;
        break;
      }
      if(match(text, position, "SELECT")){
        tokens.push_back("SELECT");
        position += 6;
        break;
      }
    case 'P':
      if(match(text, position, "PRIMARY KEY")){
        tokens.push_back("PRIMARY KEY");
        position += 11;
        break;
      }
      if(match(text, position, "PROJECT")){
        tokens.push_back("PROJECT");
        position += 7;
        break;
      }
    case 'U':
      if(match(text, position, "UPDATE")){
        tokens.push_back("UPDATE");
        position += 6;
        break;
      }
    case 'I':
      if(match(text, position, "INSERT INTO")){
        tokens.push_back("INSERT INTO");
        position += 11;
        break;
      }
    case 'V':
      //CAUTION: check this case first since it contains the following
      if(match(text, position, "VALUES FROM RELATION")){
        tokens.push_back("VALUES FROM RELATION");
        position += 20;
        break;
      }
      if(match(text, position, "VALUES FROM")){
        tokens.push_back("VALUES FROM");
        position += 11;
        break;
      }
    case 'R':
      if(match(text, position, "RENAME")){
        tokens.push_back("RENAME");
        position += 6;
        break;
      }
    case 'D':
      if(match(text, position, "DELETE FROM")){
        tokens.push_back("DELETE FROM");
        position += 11;
        break;
      }
    case '=':
	  if(match(text, position, "==")){	
        tokens.push_back("==");
        position += 2;
        break;
	  }
    case '<': 
      if(match(text, position, "<-")){
        tokens.push_back("<-");
        position += 2;
        break;
      }
      if(match(text, position, "<=")){
        tokens.push_back("<=");
        position += 2;
        break;
      }
      else{
        tokens.push_back("<");
        position++;
        break;
      }
    case '!':
      if(match(text, position, "!=")){
        tokens.push_back("!=");
        position += 2;
        break;
      }
    case '>':
      if(match(text, position, ">=")){
        tokens.push_back(">=");
        position += 2;
        break;
      }
      else{
        tokens.push_back(">");
        position++;
        break;
      }
    case '+':
      tokens.push_back("+");
      position++;
      break;
    case '-':
      tokens.push_back("-");
      position++;
      break;
    case '*':
      tokens.push_back("*");
      position++;
      break;
    case '(':
      tokens.push_back("(");
      position++;
      break;
    case ')':
      tokens.push_back(")");
      position++;
      break;
    case ',':
      tokens.push_back(",");
      position++;
      break;
    case '"':
      tokens.push_back("\"");
      position++;
      break;
    case ';':
      tokens.push_back(";");
      position++;
      break;
    case ' ':
    case '\t':
    case '\n':
      position++;
      break;
    default:
      if(c <= '9' && c >= '0'){
        string temp = get_integer(text, position);
        tokens.push_back(temp);
        position += temp.size();
      }
      if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_')){
        string temp = get_varchar(text, position);
        tokens.push_back(temp);
        position += temp.size();
      }
      //ignore everything else
      else position++;
  }
}
}

bool Tokenizer::match(string * text, int position, string exp){
  string substring = text->substr(position, exp.size());
  if (substring == exp) return true;
  else return false;
}

string Tokenizer::get_integer(string * text, int position){
  char c = (*text)[position];
  string integer;
  while(c <= '9' && c >= '0'){
    integer.push_back(c);
    position++;
    c = (*text)[position];
  }
  return integer;
}

string Tokenizer::get_varchar(string * text, int position){
  char c = (*text)[position];
  string varchar;
  while((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || (c <= '9' && c >= '0') || (c == '_')){
    varchar.push_back(c);
    position++;
    c = (*text)[position];
  }
  return varchar;
}
