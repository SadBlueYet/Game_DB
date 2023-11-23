g++ -std=c++17 -I ./include -L ./lib model/database.cpp controller/interface.cpp model/info.cpp main.cpp model/userInput.cpp controller/userActions.cpp -lsqlite3.dll -o program
program

