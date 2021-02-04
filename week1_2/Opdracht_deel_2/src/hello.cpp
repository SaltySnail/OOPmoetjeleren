#include <iostream>
#include "country.h"

using namespace std;

int main(int ac, char **ap) {
 Country country_array[5];
 country_array[0].setName("Netherlands");
 country_array[1].setName("France");
 country_array[2].setName("Brazil");
 country_array[3].setName("Japan");
 country_array[4].setName("Canada");
 cout << "Countries of the world: " << endl;
 for(Country c : country_array) {
 	cout << c.getName() << endl;
 }
 cout << endl;
 return 0;
} 
