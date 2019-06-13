#ifndef PARSER_H
#define PARSER_H

#include "STokenizer.h"
#include <map>
#include <iostream>
#include <iomanip>

struct Parser{
    Parser(std::string query);
    unsigned getCommandType();
    std::map<std::string, std::string> query_info;
};

Parser::Parser(std::string query){
    //convert string query to char array
    int len = query.length();
    char str[len + 1];
    for(int i = 0; i < len; i++){
        str[i] = query[i];
    }
    str[len] = '\0';

    STokenizer stk(str);
    Command t;
    stk >> t;
    for(auto const& x : t.getCommand()){
        std::cout << std::setw(10) << x.first << " - " <<  std::setw(10) << '|' <<  x.second << '|' << std::endl; 
    }
}
unsigned Parser::getCommandType(){
    return std::stoi(query_info["type"]);
}

#endif /* PARSER_H */

//CREATE TABLE( last string, first string )