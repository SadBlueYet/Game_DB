#include <iostream>
#include "controller/interface.h"


int main(){
    setlocale(LC_ALL, "");
    UserInterface* interface = new UserInterface();
    bool result;

    do{
        result = interface->run();
        std::cout << result;
        if(!result){
            interface->~UserInterface();
            interface = new UserInterface();
            result = false;
        }
    }while(!result);
    
    
}