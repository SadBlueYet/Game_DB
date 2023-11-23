#ifndef DATABASE_H
#define DATABASE_H

#include "../include/sqlite3.h"
#include <iostream>
#include <string>
#include <vector>



class Database {
private:
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc;

    void addGameQuery(const char* query, std::string title, std::string publisher, std::string year);
    void editGameQuery(const char* query, std::string title, std::string editedParametr);
    void deleteGameQuery(const char* query, std::string title = "");
    std::string getGamesQuery(const char* query, std::string title = "");
public:
    Database();
    void connect();
    void reconnect();
    void createTable();
    void addGame(std::string title, std::string publisher, std::string year);
    void editGame(std::string columnName, std::string editedParametr, std::string title);
    void deleteGame(std::string title);
    std::string getAllGames();
    std::string getGame(std::string title);

};

#endif // DATABASE_H