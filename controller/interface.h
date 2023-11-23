#ifndef INTERFACE_H
#define INTERFACE_H


#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "userActions.h"
#include "../model/userInput.h"



class UserInterface {
private:
    Actions* action;
    Input* input;
public:
    UserInterface();
    ~UserInterface();
    bool run();

};

#endif // INTERFACE_H