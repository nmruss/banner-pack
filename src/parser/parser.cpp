//Defines a parser for CSS files and other utility files as needed
#include <vector>
#include <fstream>
#include <iostream>

namespace Parser{
   struct attribute;
   struct selector;
   std::vector<attribute> parseAttributesList(std::ifstream& ist);
   std::ostream& operator<<(std::ostream& os,std::vector<attribute> v);

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
      attribute attr;
      std::string attributeName;
      std::string attributeValue;

      //hit ':', move to attribute value
      //hit ';', push to attributesList and reset
      //hit '}' putback into stream and return attribute list
      
      while(ist >> c){

         if(c == '}'){
            return attributesList;
         }

         if(!std::isalpha(c)){
            std::cout << "css syntax error, expected an alphanumeric character after {" << std::endl;
            return attributesList;
         }

         //read name
         while(std::isalpha(c) || c == '-'){
            attributeName+= c;
            ist >> c;
         }

         if(c == ':'){
            ist >> c;
            while(std::isalpha(c)){
               attributeValue += c;
               ist >> c;
            }
         }

//         std::cout << c << std::endl;
//         std::cout << "attribute1: " << attributeName << std::endl;
//         std::cout << "attribute1value: " << attributeValue << std::endl;
         attributeName = "";
         attributeValue = ""; 
      }
     
      return attributesList;
   }

   std::ostream& operator<<(std::ostream& os,std::vector<attribute> v){
      std::cout << v[0].name << std::endl; 
      return os;
   }
}