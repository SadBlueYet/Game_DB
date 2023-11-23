#include "userInput.h"

//user input of a string value
std::string Input::input_string(){
    std::string input;
    do{
        std::getline(std::cin, input);
        if(input.empty())
            std::cout << "the string cannot be empty\n>>";
        
    }while(input.empty());
    
    return input;
}

//user input of an integer value
std::string Input::input_int(){
    std::string input;
    bool check;
    do{
        std::getline(std::cin, input);
        if(input.empty())
            std::cout << "the string cannot be empty\n>>";
        else {
            check = this->check_numbers(input);
            if(!check) std::cout << "the string must contain only numbers\n>>";
        }
    }while(!check);
    return input;
}

//check if a string contains only numbers
bool Input::check_numbers(const std::string& number){
    for (char const &c : number) {
        if (std::isdigit(c) == 0) return false;
    }

    return true;
}

Input::~Input(){}