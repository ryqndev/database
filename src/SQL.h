#ifndef SQL_H
#define SQL_H

#include "Parser/Parser.h"
#include "Table/Table.h"
#include <iostream>

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
        Map<std::string, Table*> tables;
        
};
SQL::SQL(){
    // std::cout << "Database started." << std::endl;
}

SQL::~SQL(){
    // std::cout << "Shutting down database." << std::endl;
}
void SQL::run(){
    while(true){
        std::string query;
        // std::cout << "> ";  // prompt user command
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
    if(query == "debug"){
        for(auto& x : tables){
            std::cout << "Table: " << x.first << std::endl;
            x.second->debug();
        }
        return true;
    }else if(query == "" || query[0] == '/' || query[1] == '/'){
        return true;
    }
    std::cout << query << std::endl;
    Command* c = &parser.query_info;
    switch(c->type){
        case 0: // make table w/ only name
            tables[c->table_name] = new Table(c->table_name); 
            break;
        case 1: // make table w/ fields
            tables[c->table_name] = new Table(c->table_name, c->command, c->order); 
            break;
        case 2: // insert object
            tables[c->table_name]->insert_row(c->order);
            break;
        case 3: //display
            tables[c->table_name]->display_contents(c->conditions);
            break;
        default:
            // std::cout << "Incorrect command" << std::endl;
            break;
    }
    return true;
}

#endif /* SQL_H */