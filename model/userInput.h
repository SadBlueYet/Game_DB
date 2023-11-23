#ifndef USERINPUT_H
#define USERINPUT_H

#include <string>
#include <iostream>
#include <cstdlib>



class Input{
public:
    std::string input_string();
    std::string input_int();
    bool check_numbers(const std::string& number);
    ~Input();
};
#endif // USERINPUT_H