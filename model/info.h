#ifndef INFO_H
#define INFO_H
#include "userInput.h"

class GameInfo {
private:
    Input* input;
    std::string game_name;
    std::string publisher;
    std::string year_of_publication; 
    std::string edited_parametr; 

public:
    GameInfo();
    ~GameInfo();
    void setTitle(); 
    void setYear();
    void setPublisher();
    void setEditedParametr();
    std::string getTitle();
    std::string getYear();
    std::string getPublisher();
    std::string getEditedParametr();
    void clearFields();
};

#endif // INFO_H