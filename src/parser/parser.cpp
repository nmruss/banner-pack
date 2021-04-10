//Defines a parser for CSS files and other utility files as needed
#include <vector>
#include <fstream>
#include <iostream>
#include <lodepng.h>
#include <parser.h>

namespace Parser{

   std::vector<attribute> parseAttributesList(std::ifstream& ist);
   std::ostream& operator<<(std::ostream& os,std::vector<attribute> v);
   std::ostream& operator<<(std::ostream& os,std::vector<selector> v);

   //does this change per system? possibly
   const int BYTES_PER_PX = 4;

   //parses a png image and returns some data for trimming
   PNGImageTrimData parsePNGTrimData(std::string filename){
      std::vector <unsigned char> image;
      unsigned width,height;
      unsigned error = lodepng::decode(image,width,height,filename);
      if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
      
      PNGImageTrimData trimData;

      int x = 0;
      int y = 0;
      int onPixel = 1;
      const int zero = 0;

      for(unsigned int i=3;i<image.size();i+=BYTES_PER_PX){
         if((int)image[i] != zero){
            std::cout << "found a non transparent px" << std::endl;
            break;
         }

         if((onPixel % width) == 0){
            x=0;
            y+=1;
         } else{
            x+=1;
         }

         ++onPixel;
      }
      Point topLeftPoint { x, y};
      trimData.topLeft = topLeftPoint;
     
      return trimData;
   }

   //read a css file and return a vector of selectors
   //only reads basic #,. selectors at the moment
   std::vector<selector> parseCSS(std::string& filename){
      std::ifstream ist(filename);
      std::vector<selector> v;
      
      if(ist.fail()){
         //add error code output here
         std::cerr << "failed to read input stream";
      }

      char c;
      while(ist >> c){
         std::vector<attribute> attr_list;
         std::string selectorName;
       
         switch (c){
            case '#':
            case '.':
               //keep searching for a { and fill attr_list
               ist >> c;
               while(std::isalpha(c)){
                  selectorName += c;         
                  ist >> c;
               }
               ist.putback(c);
               //pretty ugly here
               //look into doing this recursively
               ist >> c;
               if(c == '{'){
                  attr_list = parseAttributesList(ist);
               }
               break;
        }

        if(attr_list.size() > 0 && selectorName != ""){
            selector s {}; 
            s.name = selectorName;
            s.attributesList = attr_list;
            v.push_back(s);
         }
      }
      ist.close();
      std::cout << v;
      return v;
   }

   //helper function to parse a list of attributes
   //returns parsed vector of attribute k:v pairs
   std::vector<attribute> parseAttributesList(std::ifstream& ist){
      char c;
      std::vector<attribute> attributesList;
      attribute attr;
      std::string attributeName;
      std::string attributeValue;

      if(ist.fail()){
         std::cout << "failed to open css file" << std::endl;
         //returns empty on fail
         return attributesList;
      }

      //hit ':', move to attribute value
      //hit ';', push to attributesList and reset
      //hit '}' putback into stream and return attribute list
      
      while(ist >> c){

         if(c == '}'){
            return attributesList;
         }

         if(!std::isalpha(c) && !(c == '-')){
            std::cout << "css syntax error, expected an alphanumeric character after {" << std::endl;
            return attributesList;
         }

         //read name
         while(std::isalpha(c) || c == '-'){
            attributeName+= c;
            ist >> c;
         }

         //read attribute
         if(c == ':'){
            ist >> c;
            while(std::isalpha(c)){
               attributeValue += c;
               ist >> c;
            }
         }
         attr.name = attributeName;
         attr.value = attributeValue;
         attributesList.push_back(attr);

         attributeName = "";
         attributeValue = ""; 
      }
     
      return attributesList;
   }
 
   //attributes print list of k:v pairs 
   std::ostream& operator<<(std::ostream& os,std::vector<attribute> attribute_list){ 
      for(long unsigned int i=0;i<attribute_list.size();i++){
         std::cout << attribute_list[i].name << ':' << attribute_list[i].value << std::endl; 
      }
      return os;
   }

   //selectors print list of attributes 
   std::ostream& operator<<(std::ostream& os,std::vector<selector> selector_list){
      for(long unsigned int i=0;i<selector_list.size();i++){
         std::cout << "__" << selector_list[i].name << "__" << std::endl;
         std::cout << selector_list[i].attributesList << std::endl;
         
      }
      return os;
   }
}