#ifndef PARSER_H
#define PARSER_H

#include "STokenizer.h"
#include "Command.h"
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
    for(int i = 0; i < len; i++) str[i] = query[i];
    str[len] = '\0';

    STokenizer stk(str);
    stk >> query_info;
}

#endif /* PARSER_H */
