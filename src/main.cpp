#include "SQL.h"

/**

g++ src/*.cpp -o database -std=c++11
./database

*/

int main(int argc, char const *argv[]){
    SQL database;
    database.run();
    return 0;
}
