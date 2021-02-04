#ifndef COUNTRY
#define COUNTRY
#include <string>
using namespace std;
class Country {
 public:
 // view methods
 string getName();
 // update (controller) methods
 void setName(string newName);
 private:
 // state data
 string name = "Undefined";
 // view methods
 // update methods
};
#endif
