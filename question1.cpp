#include<iostream>
#include<stdio.h>
#include<sstream>
#include<string>
#include<map>
#include<vector>

int main(){


    std:: string table;
    std:: cout << "Enter the encoding table" << std::endl;
    
    std:: getline(std:: cin,table);
    std:: stringstream ss(table);
    std:: string token, key, value;
    
    std:: vector<std::string> splitted, pairs;
    std:: map<std::string, std::string> encoding;
    



    while(std:: getline(ss, token, '|')){

        splitted.push_back(token);

    }

    for(std:: string word : splitted){

        std:: cout << "Splitted: " ;
        std:: cout << word << std:: endl; 
    }
    
    for(std:: string pair : splitted){

        std:: stringstream ss2(pair);
        int i = 0;
        while(std:: getline(ss2, token, '=')){

            if(i == 0){
                key = token;
                i++;
            }
            else{
                value = token;
                i++;
            }
        }

        std:: cout << "key: " << key << " value: " << value << std:: endl;
        encoding[key] = value;
        
        }

        
        return 0;
    
    }


