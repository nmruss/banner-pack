//Parser for CSS files 
#pragma once
#include <iostream>
#include <vector>
#include <fstream>

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

   std::vector<selector> parseCSS(std::ifstream& ist);

   void writeCSS(std::ifstream& ist,std::vector<selector> v);
}