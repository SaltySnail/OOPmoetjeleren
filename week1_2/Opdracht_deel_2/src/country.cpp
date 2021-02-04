#include <string>
#include "country.h"
using namespace std;
// public view methods
string Country::getName() {
 return name;
}
// public update (controller) methods
void Country::setName(string newName) {
 name = newName;
} 
