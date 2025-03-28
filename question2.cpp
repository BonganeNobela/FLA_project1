#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
#include<sstream>
#include<vector>

std:: vector<std:: string> getSymbols(std:: string transition){

    std:: vector<std:: string> symbols;
    std:: string symbol;
    int len = transition.length();
    int x, y = 0;

    while(x + 2 <= len){
        
        
        symbol = transition.substr(x,2);
        symbols.push_back(symbol);
        x += 2;
    }

    return symbols;

}
void decode(std:: vector<std:: string> symbols, std:: map<std:: string, std:: string> mapping){

    std:: string decoded_word;

    for(std:: string symbol : symbols){

        std:: string decoded_symbol = mapping[symbol];
        decoded_word += decoded_symbol;
    }

    std:: cout << decoded_word << std:: endl;

}

int main(){
    
std:: map<std:: string, std:: string> mapping = {
    {"00", "0"},
    {"01", "1"},
    {"10", "#"},
    {"11", ";"}
};
    std:: string str;
    std:: getline(std:: cin, str);

    std:: vector<std:: string> symbols = getSymbols(str);
    decode(symbols, mapping);

    
    return 0;
}