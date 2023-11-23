#include "userActions.h"

Actions::Actions(){
    this->gameInfo = new GameInfo();
    this->database = new Database();
    this->input = new Input();
}

/*
    this method gets a game from the database and prints it to the console
*/
bool Actions::getGame(){
    system("cls");
    this->gameInfo->setTitle();
    std::string game = this->database->getGame(this->gameInfo->getTitle());
    if (game == "") {
        std::cout << "Game not found." << std::endl;
        return true;
    }
    this->gameInfo->clearFields();
    std::cout << game << std::endl;
    return true;
}

/*
    this method gets all games from the database and prints them to the console
*/
bool Actions::getAllGames(){
    system("cls");
    std::string games = this->database->getAllGames();
    if (games == "") {
        std::cout << "No games found." << std::endl;
        return true;
    }
    std::cout << games << std::endl;
    return true;
}

/*
    this method deletes a game from the database
*/
bool Actions::deleteGame(){
    system("cls");
    std::string game;
    int counter = 0;
    do{
        this->gameInfo->setTitle();
        game = this->database->getGame(this->gameInfo->getTitle());
        if (game == "" && counter < 3) {
            
            std::cout << "Game not found. remained attempts: " << 3 -counter << std::endl;
            counter++;
            continue;
        }
        if(counter == 3) return true;
        this->database->deleteGame(this->gameInfo->getTitle());
        this->gameInfo->clearFields();
        break;
    }while(true);

    std::cout << "Game deleted successfully." << std::endl;
    return true;
}


/*
    this method adds a new game to the database
*/
bool Actions::addGame(){
    system("cls");
    this->gameInfo->setTitle();
    this->gameInfo->setPublisher();
    this->gameInfo->setYear();
    this->database->addGame(this->gameInfo->getTitle(), this->gameInfo->getPublisher(), this->gameInfo->getYear());
    this->gameInfo->clearFields();
    std::cout << "Game added successfully." << std::endl;
    return true;
}

/*
    this method edits a game in the database
*/
bool Actions::editGame(){
    system("cls");
    std::map <int, std::string> userChoice;
    userChoice[1] = "game_title";
    userChoice[2] = "publisher";
    userChoice[3] = "year_of_publication";

    const char* menu[] = {
        "[1] Edit title",
        "[2] Edit publisher",
        "[3] Edit year",
        "[4] Exit"

    };
    int choice = 0;
    do{
        std::cout << "------------------" << std::endl;
        for(size_t i = 0; i < 4; i++){
            std::cout << menu[i] << std::endl;
        }
        std::cout << "------------------" << std::endl;
        std::cout << ">> ";
        choice = this->input->input_string()[0] - '0';
        
        
        
        if(choice < 4 && choice > 0){
            this->gameInfo->setTitle();
            std::string game = this->database->getGame(this->gameInfo->getTitle());
            if (game == "") {
                std::cout << "Game not found." << std::endl;
                continue;
            }
            if (choice == 1) {
                this->gameInfo->setEditedParametr();
                this->database->editGame(userChoice[choice], this->gameInfo->getEditedParametr(), this->gameInfo->getTitle());
            }
            else if (choice == 2) {
                this->gameInfo->setPublisher();
                this->database->editGame(userChoice[choice], this->gameInfo->getPublisher(), this->gameInfo->getTitle());
            }
            else if (choice == 3) {
                this->gameInfo->setYear();
                this->database->editGame(userChoice[choice], this->gameInfo->getYear(), this->gameInfo->getTitle());
            }
            
            this->gameInfo->clearFields();
            break;
        }
        
    }while(choice != 4);
    return true;
}