#ifndef SQL_H
#define SQL_H

#include "Parser/Parser.h"
#include "Table/Table.h"
#include <iostream>
#include <vector>

class SQL{
    public:
        SQL();
        ~SQL();
        /** 
         * Starts the database and waits for user commands
         * 
         * @params: none
         */
        void run();

    private:

        /** 
         * Takes a string input and parses it as a SQL command.
         * If it cannot be parsed, will return false. 
         * If command runs into error (no more memory, etc.), will
         * throw appropriate exception
         * 
         * @params: query - command to be executed
         */
        bool transact(std::string query);
        std::vector<Table> tables;
        
};
SQL::SQL(){
    std::cout << "Database started." << std::endl;
}

SQL::~SQL(){
    std::cout << "Shutting down database." << std::endl;
}
void SQL::run(){
    while(true){
        std::string query;
        std::cout << "> ";  // prompt user command
        getline(std::cin, query);
        
        bool success = transact(query);
        if(!success){
            // quits database management
            // eventually call SQL class destructor
            break;
        };
    }
}
bool SQL::transact(std::string query){
    Parser parser(query);
    switch(parser.type){
        case 0: 
            // make/create table
            break;
        default:
            break;
    }
    return true;
}

#endif /* SQL_H */