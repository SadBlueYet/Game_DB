#ifndef USERACTIONS_H
#define USERACTIONS_H

#include <string>
#include <map>
#include <cstdlib>
#include "../model/info.h"
#include "../model/database.h"
#include "../model/userInput.h"

class Actions{
private:
    GameInfo* gameInfo;
    Database* database;
    Input* input;
public:
    Actions();
    bool getGame();
    bool getAllGames();
    bool deleteGame();
    bool addGame();
    bool editGame();
};
#endif // USERACTIONS_H