#include <iostream>
#include "../include/parser.h"
using namespace std;

void TestCSSParser();
void TestPNGParser();

const string CSS_TEST_PARAM = "test-css-parser";
const string PNG_TEST_PARAM = "test-png-parser";

int main(int argc,char **argv){
   //TESTS//
   for(int i=0;i<argc;++i){
      cout << argv[i] << endl;

      if(argv[i] == CSS_TEST_PARAM){
         cout << "~TESTING CSS PARSER~" << endl;
         TestCSSParser();
      };
      if(argv[i] == PNG_TEST_PARAM){
         cout << "~TESTING PNG PARSER~" << endl;
         TestPNGParser();
      }
   };
   ////////

   return 0;
}


//takes an input file from tests/
//tests css parser
void TestCSSParser(){
   string filename;
   cin >> filename;
   Parser::parseCSS(filename);
}

//takes an input file from tests/
//tests png parser
void TestPNGParser(){
   string filename;
   cin >> filename;
   Parser::PNGImageTrimData testTrimData;
   testTrimData = Parser::parsePNGTrimData(filename);
   std::cout << "x: " << testTrimData.topLeft.x << std::endl;
   std::cout << "y: " << testTrimData.topLeft.y << std::endl;
}
