// Patrick Rock
// 9/5/2013
// Database Engine Header

#include "table.h"
#include <vector>
using namespace std;

//-------------------------//
//--DATABASE ENGINE CLASS--//
//-------------------------//

class DbEngine {
  public:
    void createTable(vector<Type>);
  private:
    vector<Table> tables;
};

void DbEngine::createTable(vector<Type> types) {
}
