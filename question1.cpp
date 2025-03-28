#include<iostream>
#include<stdio.h>
#include<sstream>
#include<string>
#include<map>
#include<vector>

std:: map<std::string, std::string> map_to(std:: string table){

    std:: stringstream ss(table);
    std:: string token, key, value;
    
    std:: vector<std::string> splitted, pairs;
    std:: map<std::string, std::string> encoding;
    



    while(std:: getline(ss, token, '|')){

        splitted.push_back(token);

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
        
        encoding[key] = value;
        
        }

    return encoding;

};


std::string encode(std:: map<std::string, std::string> encoding, std::string word){
    
    int len = word.length();
    std::string encoded_word, alphabet, temp;

    for(int i = 0; i < len; i++){
        temp = word[i];
        alphabet = encoding[temp];
        encoded_word += alphabet;
    }

    return encoded_word;


};


int main(){

    std::string table, word;
    std::getline(std::cin, table);
    std::getline(std::cin, word);
    std:: map<std::string, std:: string> encoding = map_to(table);
    std:: cout<< encode(encoding, word) << std::endl;
     
        return 0;
    
    }


