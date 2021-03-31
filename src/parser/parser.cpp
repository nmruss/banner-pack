//Defines a parser for CSS files and other utility files as needed
#include <vector>
#include <fstream>
#include <iostream>

namespace Parser{
   struct attribute;
   struct selector;
   std::vector<attribute> parseAttributesList(std::ifstream& ist);

   struct selector{
      std::string selection;
      std::vector<attribute> attrbutesList;
   };

   struct attribute{
      std::string name;
      //is this best stored as a string?
      //will likely need to be typecast for some values
      std::string value;
   };

   //read a css file and return a vector of selectors
   std::vector<selector> parseCSS(std::ifstream& ist){
      std::vector<selector> v;
      
      if(ist.fail()){
         //add error code output here
         std::cerr << "failed to read input stream";
      }

      char c;
      while(ist >> c){
         std::string selectorName;
         
         switch (c){
            case '#':
               ist >> c;
               while(std::isalpha(c)){
                  selectorName += c;         
                  ist >> c;
               }
               ist.putback(c);
               std::cout << selectorName << std::endl;
               break;
            case '{':
               parseAttributesList(ist);
               break;
         }
      }
      return v;
   }

   //helper function to parse a list of attributes
   std::vector<attribute> parseAttributesList(std::ifstream& ist){
      char c;
      std::vector<attribute> attributesList;
      std::string attributeName;
      //when you hit ':', move to attribute value
      //when you hit ';', push to attributesList and reset
      //when you hit '}' putback into stream and return
      
      ist >> c;
      while(std::isalpha(c)){
         attributeName+= c;
         ist >> c;
      }

      std::cout << c << std::endl;
      std::cout << "attribute1: " << attributeName << std::endl;
      
      return attributesList;
   }
}

