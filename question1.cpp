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
    std:: string token;
    
    std:: vector<std::string> splitted;



    while(std:: getline(ss, token, '|')){

        splitted.push_back(token);

    }

    for(std:: string word : splitted){

        std:: cout << "Splitted: " << std:: endl;
        std:: cout << word << std:: endl; 
    }


    return 0;
}