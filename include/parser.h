//Parser for CSS files 
#pragma once
#include <iostream>
#include <vector>
#include <fstream>

namespace Parser{
   struct attribute{
      std::string name;
      //is this best stored as a string?
      //will likely need to be typecast for some values
      std::string value;
   };
 
   struct selector{
      std::string name;
      std::vector<attribute> attributesList;
   };
  
   struct Point {
      int x,y;
   };

   struct PNGImageTrimData{
      Point topLeft;
      int width,height;
   };

   //TODO: make this take a filename string?
   std::vector<selector> parseCSS(std::string& filename);
   
   PNGImageTrimData parsePNGTrimData(std::string filename);

   void writeCSS(std::ifstream& ist, std::vector<selector> v);
}