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
    while(!stk.is_done()){
        Token t;
        stk >> t;   
        std::cout << std::setw(10) << t.type_string() << std::setw(10) << t << std::endl;
        query_info["type"] = t.type();
    }
}
unsigned Parser::getCommandType(){
    return std::stoi(query_info["type"]);
}

#endif /* PARSER_H */

//CREATE TABLE( last string, first string )