#include "interface.h"

UserInterface::UserInterface(){
    this->input = new Input();
    this->action = new Actions();
}

//This method runs the user interface.
bool UserInterface::run(){
    const char* menu[] = {
        "[1] Add new game",
        "[2] Edit game",
        "[3] Delete game",
        "[4] Get games",
        "[5] Get game",
        "[6] Exit"
    };

    int choice;
    bool check = true;
    //This loop runs until the user chooses to exit.
    do{
        
        std::cout << "------------------" << std::endl;
        for(size_t i = 0; i < 6; i++){
            std::cout << menu[i] << std::endl;
        }
        std::cout << "------------------" << std::endl;
        std::cout << ">> ";

        choice = this->input->input_string()[0] - '0';
        if (choice == 1) check = this->action->addGame();
        else if (choice == 2) check = this->action->editGame();
        else if (choice == 3) check = this->action->deleteGame();
        else if (choice == 4) check = this->action->getAllGames();
        else if (choice == 5) check = this->action->getGame();
        if (!check){
            return false;
        }
        
    }while (choice != 6);
    return true;
    
}

UserInterface::~UserInterface(){
    delete this->action;
    delete this->input;
}