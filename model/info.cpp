#include "info.h"



GameInfo::GameInfo() {
  this->input = new Input();
  this->game_name = "";
  this->publisher = "";
  this->year_of_publication = ""; 
  this->edited_parametr = ""; 
}

//Sets the name of the game.
void GameInfo::setTitle() {
  std::cout << "Enter the name of the game: ";
  this->game_name = input->input_string();
}

//Sets the year of publication of the game.
void GameInfo::setYear() {
  std::string year;
  do{
    std::cout << "Enter the year of publication: ";
    year = input->input_int();
    if(stoi(year) <  0 || stoi(year) > 2023)
      std::cout << "The year must be between 0 and 2023\n>>";
  }while(stoi(year) <  0 || stoi(year) > 2023);
  
  this->year_of_publication = year;
}

//Sets the publisher of the game.
void GameInfo::setPublisher() {
  std::cout << "Enter the publisher: ";
  this->publisher = input->input_string();
}

//Sets the edited parameter of the game.
void GameInfo::setEditedParametr() {
  std::cout << "Enter the edited parameter: ";
  this->edited_parametr = input->input_string();
}

//Returns the name of the game.
std::string GameInfo::getTitle() {
  return this->game_name;
}

//Returns the year of publication of the game.
std::string GameInfo::getYear() {
  return this->year_of_publication;
}

//Returns the publisher of the game.
std::string GameInfo::getPublisher() {
  return this->publisher;
}


//Returns the edited parameter of the game.
std::string GameInfo::getEditedParametr() {
  return this->edited_parametr;
}

//Clears all the fields of the GameInfo object.
void GameInfo::clearFields() {
  this->game_name = "";
  this->publisher = "";
  this->year_of_publication = "";
  this->edited_parametr = "";
}

GameInfo::~GameInfo() {
  delete this->input;
}
