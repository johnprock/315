//class tokenizer, tokenizes a string

#include <string>
#include <vector>

using namespace std;

class tokenizer{
  public:
    //constructor actually does the tokenizer
    vector<string> tokenizer(string * text);

};

tokenizer::tokenizer(string * text){
    //all possible tokens
      //OPEN
      //CLOSE
      //WRITE
      //EXIT
      //SHOW
      //CREATE TABLE    PRIMARY KEY
      //UPDATE  SET  WHERE 
      //INSERT INTO  VALUES FROM 
      //INSERT INTO  VALUES FROM RELATION 
      //SELECT
      //PROJECT
      //RENAME
      //operators: == <- != < > <= >= + - *  ( ) 
      //literals: VARCHAR INTEGER
      

delete-cmd ::= DELETE FROM relation-name WHERE condition
}
