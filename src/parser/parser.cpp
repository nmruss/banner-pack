//Defines a parser for CSS files and other utility files as needed
#include <vector>
#include <fstream>
#include <iostream>

namespace Parser{
   struct attribute{
      std::string name;
      //is this best stored as a string,
      //will likely need to be typecast
      std::string value;
   };

   struct selector{
      std::string selection;
      std::vector<attribute> attrbutesList;
   };

   //read a css file and return a vector of selectors
   std::vector<selector> parseCSS(std::ifstream& ist){
      if(ist.fail()){
         std::cerr << "failed to read input stream";
      }

      //file read success
      std::string line;
      while(std::getline(ist,line)){
         std::cout << line << std::endl;
      }

      std::vector<selector> v;

      return v;
   }
}

