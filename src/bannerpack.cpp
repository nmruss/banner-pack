#include <iostream>
#include "../include/parser.h"
using namespace std;

int main(){
   string filename;
   cout << "provide a filename" << endl;
   cin >> filename;
   cout << filename << endl;
   ifstream file(filename);   
   Parser::parseCSS(file);
   return 0;
}
