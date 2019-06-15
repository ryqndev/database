#ifndef PARSER_H
#define PARSER_H

#include "STokenizer.h"
#include "Command.h"
#include <map>
#include <iostream>
#include <iomanip>

struct Parser{
    Parser(std::string query);
    Command query_info;    
};

Parser::Parser(std::string query){
    //convert string query to char array for stokenizer
    int len = query.length();
    char str[len + 1];
    for(int i = 0; i < len; i++){
        str[i] = query[i];
    }
    str[len] = '\0';

    STokenizer stk(str);
    stk >> query_info;
    // std::cout << "table name: |" << query_info.table_name << '|' << std::endl;
    // for(auto const& x : query_info.command){
    //     std::cout << std::setw(10) << '|' << x.first << '|' << " - " <<  std::setw(10) << '|' <<  x.second << '|' << std::endl; 
    // }
}


#endif /* PARSER_H */
