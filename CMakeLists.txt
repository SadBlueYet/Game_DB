cmake_minimum_required(VERSION 3.10)
project(GameDatabase)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(lib)

add_executable(GameDatabase main.cpp model/database.cpp model/info.cpp controller/interface.cpp controller/userActions.cpp model/userInput.cpp)

target_link_libraries(GameDatabase sqlite3)
