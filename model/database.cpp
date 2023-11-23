#include "database.h"


Database::Database(){
    this->connect();
    this->createTable();
}

/**
 * Adds a game query to the database.
 * 
 * query The query to be executed.
 */
void Database::addGameQuery(const char* query, std::string title, std::string publisher, std::string year) {
    // Prepare the SQL statement
    this->rc = sqlite3_prepare_v2(this->db, query, -1, &this->stmt, 0);
    if (this->rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        this->reconnect();
        return;
    }

    // Bind the game information to the prepared statement
    this->rc = sqlite3_bind_text(this->stmt, 1, title.c_str(), title.length(), SQLITE_STATIC);    
    if (this->rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    this->rc = sqlite3_bind_text(this->stmt, 2, publisher.c_str(), publisher.length(), SQLITE_STATIC);    
    if (this->rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    this->rc = sqlite3_bind_text(this->stmt, 3, year.c_str(), year.length(), SQLITE_STATIC);    
    if (this->rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Execute the prepared statement
    this->rc = sqlite3_step(this->stmt);

    // Check for execution errors
    if (this->rc != SQLITE_DONE) {
        std::cerr << "SQL execution error: " << sqlite3_errmsg(this->db) << std::endl;
        sqlite3_finalize(this->stmt);
        return;
    }
    
    // Finalize the statement
    sqlite3_finalize(this->stmt);
}
/**
 * This method executes a SQL query to edit a game in the database.
 *
 * query The SQL query to execute.
 */

void Database::editGameQuery(const char* query, std::string title, std::string editedParametr){
    // Prepare the SQL statement
    this->rc = sqlite3_prepare_v2(this->db, query, -1, &this->stmt, 0);
    if (this->rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(this->db) << std::endl;
        this->reconnect();
        return;
    }

    // Bind the edited parameter to the statement
    this->rc = sqlite3_bind_text(this->stmt, 1, editedParametr.c_str(), editedParametr.length(), SQLITE_STATIC);
    if (this->rc != SQLITE_OK) {
        std::cerr << "SQL bind error: " << sqlite3_errmsg(this->db) << std::endl;
        this->reconnect();
        return;
    }

    // Bind the game title to the statement
    this->rc = sqlite3_bind_text(this->stmt, 2, title.c_str(), title.length(), SQLITE_STATIC);
    if (this->rc != SQLITE_OK) {
        std::cerr << "SQL bind error: " << sqlite3_errmsg(this->db) << std::endl;
        this->reconnect();
        return;
    }

    // Execute the statement
    this->rc = sqlite3_step(this->stmt);
    if (this->rc != SQLITE_DONE) {
        std::cerr << "SQL execution error: " << sqlite3_errmsg(this->db) << std::endl;
        sqlite3_finalize(this->stmt);
        this->reconnect();
        return;
    }

    // Finalize the statement
    sqlite3_finalize(this->stmt);
}

/**
 * Deletes a game from the database based on the given query.
 *
 * @param query The query used to delete the game.
 */
void Database::deleteGameQuery(const char* query, std::string title) {
    // Prepare the SQL statement
    this->rc = sqlite3_prepare_v2(this->db, query, -1, &this->stmt, 0);
    if (this->rc != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(this->db) << std::endl;
        this->reconnect();
        return;
    }

    // Bind the game title parameter
    this->rc = sqlite3_bind_text(this->stmt, 1, title.c_str(), title.length(), SQLITE_STATIC);
    if (this->rc != SQLITE_OK) {
        std::cerr << "SQL bind error: " << sqlite3_errmsg(this->db) << std::endl;
        this->reconnect();
        return;
    }

    // Execute the statement
    this->rc = sqlite3_step(this->stmt);
    if (this->rc != SQLITE_DONE) {
        std::cerr << "SQL execution error: " << sqlite3_errmsg(this->db) << std::endl;
        sqlite3_finalize(this->stmt);
        this->reconnect();
        return;
    }

    // Finalize the statement
    sqlite3_finalize(this->stmt);
}

/**
 * Executes a query to retrieve games from the database.
 * 
 * query The SQL query to execute.
 */
std::string Database::getGamesQuery(const char* query, std::string title) {
    std::string game = "";
    
    // Prepare the SQL statement
    this->rc = sqlite3_prepare_v2(this->db, query, -1, &this->stmt, 0);
    if (this->rc != SQLITE_OK) {
        // Print error message if SQL prepare fails
        std::cout << "SQL prepare error: " << sqlite3_errmsg(this->db) << std::endl;
        this->reconnect();
        return "";
    }


    if (title != ""){
        // Bind the game title to the SQL statement
        this->rc = sqlite3_bind_text(this->stmt, 1, title.c_str(), title.length(), SQLITE_STATIC);
        if (this->rc != SQLITE_OK) {
            // Print error message if SQL bind fails
            std::cerr << "SQL bind error: " << sqlite3_errmsg(this->db) << std::endl;
            this->reconnect();
            return "";
        }
    }
    
    // Execute the SQL statement and process the results
    while ((this->rc = sqlite3_step(this->stmt)) == SQLITE_ROW) {
        // Get the game name, publisher, and year from the result set
        const char* gameName = reinterpret_cast<const char*>(sqlite3_column_text(this->stmt, 1));
        const char* publisher = reinterpret_cast<const char*>(sqlite3_column_text(this->stmt, 2));
        const char* year = reinterpret_cast<const char*>(sqlite3_column_text(this->stmt, 3));
        // Print the game information
        game += std::string(gameName) + " " + std::string(publisher) + " " + std::string(year) + "\n";
    }
    //std::cout <<game;
    return game;
}


void Database::reconnect(){
    //Closing a database file
    this->rc = sqlite3_close(this->db);
    if (rc != SQLITE_OK) {
        std::cout << "Error closing database: " << sqlite3_errmsg(this->db) << std::endl;
        return;
    }
    this->connect();
}

void Database::connect(){
    //Opening a database file
    this->rc = sqlite3_open("games.db", &this->db);
    if (rc != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(this->db) << std::endl;
        return;
    }
}

/**
 * Creates a table in the database if it does not already exist.
 */
void Database::createTable(){
    const char* query = "CREATE TABLE IF NOT EXISTS games (id INTEGER PRIMARY KEY, game_title TEXT, publisher TEXT, year_of_publication TEXT);";
    
    // Execute the query
    this->rc = sqlite3_exec(this->db, query, NULL, NULL, NULL);
    
    // Check if the query execution was successful
    if (this->rc != SQLITE_OK) {
        std::cout << "Request error: " << sqlite3_errmsg(this->db) << std::endl;
        return;
    }
}

/**
 * Adds a game to the database.
 * 
 * This function inserts a new game record into the "games" table in the database.
 * It uses the information provided by the gameInfo object to populate the fields.
 * 
 * The game information object containing the game's title, publisher, and year of publication.
 */
void Database::addGame(std::string title, std::string publisher, std::string year)
{      
    // SQL query to insert a new game record
    const char* query = "INSERT INTO games (game_title, publisher, year_of_publication) VALUES (?, ?, ?)";


    // Execute the add query
    this->addGameQuery(query, title, publisher, year);

}

/**
 * Updates the specified slot of the game in the database.
 * 
 * @param columnName The name of the column to be updated.
 */
void Database::editGame(std::string columnName, std::string editedParametr, std::string title) {
    // Create the SQL query
    std::string query = "UPDATE games SET " + columnName + " = ? WHERE game_title = ?";
    
    // Execute the query
    this->editGameQuery(query.c_str(), title, editedParametr);
    
    // Print success message
    std::cout << "Data edited to the database successfully." << std::endl;
}

// Delete a game from the database
void Database::deleteGame(std::string title) {
    // SQL query to delete a game based on game_title
    const char* query = "DELETE FROM games WHERE game_title = ?";
    // Execute the delete query
    this->deleteGameQuery(query, title);

}

//Retrieves all games from the database.
std::string Database::getAllGames() {
    const char* query = "SELECT * FROM games";
    return this->getGamesQuery(query);
}

// Retrieves game information from the database
std::string Database::getGame(std::string title) {
    // SQL query to select game based on title

    const char* query = "SELECT * FROM games WHERE game_title = ?";
    
    std::string game = this->getGamesQuery(query, title);
    return game;
}

