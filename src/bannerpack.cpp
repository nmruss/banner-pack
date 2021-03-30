#include <iostream>
#include "../include/parser.h"
using namespace std;

int main(){
   string filename;
   cout << "provide a css file for reading" << endl;
   cin >> filename;
   ifstream file(filename);   
   Parser::parseCSS(file);
   return 0;
}
