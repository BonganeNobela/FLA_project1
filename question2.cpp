#include <iostream>
#include <stdio.h>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <array> 
#include <map>
#include <bitset>

//  Split the input string into 2-character symbols
//  and store them in a vector
//  Example: "010110" -> ["01", "01", "10"]

std::vector<std::string> getSymbols(std::string transition) {
    std::vector<std::string> symbols;
    std::string symbol;
    int len = transition.length();
    int x = 0;

    while (x + 2 <= len) { // Ensure we don't go out of bounds
        symbol = transition.substr(x, 2); // Extract 2 characters
        symbols.push_back(symbol); // Add to vector
        x += 2;
    }

    return symbols;
}

// Decode the symbols using the mapping and incatenate them in  the string decoded_word
//  Example: ["01", "10", "11"] -> "1#0;1"
//  The decoded_word is then split into transitions, each transition is stored in a vector of arrays


std:: vector<std::array<std:: string,5>> decode(std::vector<std::string> symbols, std::map<std::string, std::string> mapping) {
    std::string decoded_word;

    // Iterate through the symbols and decode them
    // using the mapping provided
    // Example: "01" -> "1", "10" -> "#", "11" -> ";"
    // Concatenate the decoded symbols into a single string
    for (const std::string& symbol : symbols) {
      
      if(mapping.find(symbol) != mapping.end()){
        
        std::string decoded_symbol = mapping[symbol];
        decoded_word += decoded_symbol;
      }
      else{
        //std:: cout<<"Error mapping has no such key" << std::endl;
        break;
      }
        
      }
        
      //split the decoded_word into transitions
      //store them in a vector of arrays :transitions
      //return the vector of arrays
    std:: stringstream ss(decoded_word);
    std:: string token;
    std:: vector<std:: array<std:: string,5>> transitions;
    std:: array<std:: string, 5>transition = {" "," "," "," "," "};
    
  
    while(std::getline(ss,token, ';')){
      
      std:: stringstream ss2(token);
      std:: string temp;
      int i = 0;
      
      while(std:: getline(ss2, temp, '#' )){
        if(i < 5){

          transition.at(i) = temp;
        }

        else{
          //std:: cout << "Error, too many elements in the transition" << std:: endl;
          break;
        }
        i++;
      }
       
      transitions.push_back(transition);
     
    }
    return transitions;

}

// Create a mapping of the transitions
// where the key is the concatenation of the first two elements, the state and the read symbol
// and the value is the transition array
// Example: "00" -> ["0", "0", "#", "1", "0"]
std:: map<std:: string, std:: array<std::string,5>> transitions_map (std:: vector<std:: array <std:: string, 5>> transitions){
  std:: map<std:: string,std:: array<std:: string,5>> mapping;
  for(std:: array<std:: string, 5> transition : transitions){
    std::  string curr_trans = transition.at(0)+ transition.at(1);
    mapping[curr_trans] = transition;
  }
  
  return mapping;
}

// Encode the input string into a vector of strings
//  Example: "0123456789" -> ["0", "1", "10", "11", "100", "101", "110", "111", "1000", "1001", "1010", "0"]
std:: vector<std:: string>  encodeInput(std:: string input){

  std:: vector<std:: string> encodedInput;
  std:: string temp;
  encodedInput.push_back("0");
  for(char ch : input){

    if(ch == '0'){
      temp = "1";
      encodedInput.push_back(temp);
      continue;
    }
    else if(ch == '1'){
      temp = "10";
      encodedInput.push_back(temp);
      continue;
    }
    else if(ch == '2'){
      temp = "11";
      encodedInput.push_back(temp);
      continue;
    }
    else if(ch == '3'){
      temp = "100";
      encodedInput.push_back(temp);
      continue;
    }
    else if(ch == '4'){
      temp = "101";
      encodedInput.push_back(temp);
      continue;
    }
    else if(ch == '5'){
      temp = "110";
      encodedInput.push_back(temp);
      continue;
    }
    else if(ch == '6'){
      temp = "111";
      encodedInput.push_back(temp);
      continue;
    }
    else if(ch == '7'){
      temp = "1000";
      encodedInput.push_back(temp);
      continue;
    }
    else if(ch == '8'){
      temp = "1001";
      encodedInput.push_back(temp);
      continue;
    }
    else if(ch == '9'){
      temp = "1010";
      encodedInput.push_back(temp);
      continue;
    }
    else{
      //std:: cout << "Error, invalid character in input" << std:: endl;
      break;
    }
  }

  encodedInput.push_back("0");
  return encodedInput;

}

// Simulate the tape using the mapping and the encoded input

std:: string tape(std:: map<std:: string, std:: array<std::string,5>> mapping, std:: vector<std:: string>  encodedInput){

// initialize the variables
  std:: string state = "0";  int i = 1;
  std:: string read, write, D, nex_state, output;
  int count = 0;  // to cap the number of iterations and avoid infinite loops  

  // getting the key for the first transition
  std:: string curr= state + encodedInput.at(i);
  
  // checking each key in the mapping
 /* std:: cout << "all transition keys: " << std:: endl;
  for (const auto& pair : mapping) {
        std::cout << pair.first << std::endl;  
    } */
  
  // checking if the key exists in the mapping
   // std:: cout << "key: " << curr<< std::endl;
  if (mapping.find(curr) == mapping.end()) {
    //return "Error, transition does not exist";
    return "Error";
  }


  // getting the first transition from the first key
  std:: array<std:: string, 5> trans = mapping[curr];
  
  // printing the transition
  /*for(std:: string el: trans){
    std:: cout << "el: "<< el << std:: endl;
  }*/

  // simulating the tape
  // while the state is not "1" or "2"
  // the state "1" is the accept state 
  // the state "2" is the reject state
  // the state "0" is the initial state
  while( state != "1" && state !="2"){
    
    // Getting the initial state, next state and write symbol from the first transition
    state = trans.at(0);
    nex_state = trans.at(2);
    write = trans.at(3);
    /*
    std:: cout <<"state: "  << state << std::endl;
    std:: cout <<"next state: "  << nex_state << std::endl;
    std:: cout <<"write: "  << write << std::endl;
    */

    
    int len = encodedInput.size();

    //if the index is out of range, we are reading a blank space therefore read = "0"
    if(i >= len){
      read = "0";
      encodedInput.push_back(write);
      encodedInput.push_back("0");
    }

    else if(i < 0){
      read = "0";
      encodedInput.insert(encodedInput.begin(), write);
      encodedInput.insert(encodedInput.begin(), "0");
      //encodedInput.push_back("0");
    }
    else{

      // if the index is in range, we are reading a character and changing it to the write symbol
      read = encodedInput.at(i);  
      encodedInput.at(i) = write;
      /*
      std:: cout << "read: " << read << std:: endl;
      std:: cout << "changed the input at encodedInput[" << i << "] : " << encodedInput.at(i) << std:: endl;
      */
      }
    
    //getting and printing out the direction

    D = trans.at(4);
    //std:: cout << "D(trans[4]) :" << D << std:: endl;
    
    // moving the index according to the direction
    if( D == "0"){
      
      i --;
    }
    
    else{
      i++;
    }
  // checking if the next state is "1" or "2"
  // if it is, we are in the accept or reject state
  if(nex_state== "1"){
    
    output = "Accept";
    return output;
  }
  
  if(nex_state == "10"){
    output = "Reject";
    return output;
  }
  
      //if the index is out of range, we are reading a blank space therefore read = "0"
      if(i >= len || i < 0){
        read = "0";
      }
      else{

        // if the index is in range, we are reading the next character
        read = encodedInput.at(i);  
      }
  // checking if the next transition exists in the mapping
  if(mapping.find(nex_state + read) == mapping.end()){
    //std:: cout << "new key :" << nex_state+read <<  std::endl;
    //return "Error, trans don't exist";
    return "Error";
  }

  // checking which transition we are using by printing out the key
  //std:: cout << "new key :" << nex_state+read << std:: endl;
  // getting the next transition from the mapping
  // and printing it out
  trans = mapping[nex_state+read];
  /*std:: cout << "new transition: " << std:: endl;
  for(const std:: string& str: trans){
    std:: cout << str << std:: endl;
       }
  std:: cout << "*****************"<<std:: endl; */

  //checking if reached max iterations
  if(count > 1000){
    //std:: cout << "Error, too many iterations" << std:: endl;
    return "Accept";
  
  }

  count++; // increment the count

  }
  
  return output;
  }


int main() {

  // define the mapping of the symbols to their corresponding values
    std::map<std::string, std::string> mapping = {
        {"00", "0"},
        {"01", "1"},
        {"10", "#"},
        {"11", ";"}
    };
    //getting the input string
    std::string transStr;
    std:: string input;
    std:: vector<std:: string> encodedInput;
    
    std::getline(std::cin, transStr);
    std::getline(std:: cin,input);

    //encioding the input string
    encodedInput = encodeInput(input);

    //printing the encoded input
   // std:: cout << "encoded input: " << std:: endl;
   // for(std:: string str: encodedInput){
    //  std:: cout << str << std:: endl;
  //  }
    //getting the symbols from the input string
    std::vector<std::string> symbols = getSymbols(transStr);

    //getting the transitions from the symbols
    std:: vector<std::array<std:: string,5>> transitions = decode(symbols, mapping);

    // mapping the transitions to a map
    // where the key is the concatenation of the first two elements, the state and the read symbol
    std:: map<std:: string, std:: array<std::string,5>> trans_map = transitions_map(transitions);

    //getting the output from the tape simulation
    std:: string output = tape(trans_map, encodedInput);
    
    //printing the output
    std:: cout << output << std:: endl;

    return 0;
}