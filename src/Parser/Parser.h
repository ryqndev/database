#ifndef PARSER_H
#define PARSER_H

#include "STokenizer.h"
#include <iostream>
#include <iomanip>

struct Parser{
    Parser(std::string query);

    unsigned type;
};
Parser::Parser(std::string query){
    int len = query.length() + 1;
    char str[len];
    for(int i = 0; i < len; i++){
        str[i] = query[i];
    }
    STokenizer stk(str);
    while(!stk.is_done()){
        Token t;
        stk >> t;   
        std::cout << std::setw(10) << t.type_string() << std::setw(10) << t << std::endl;
    }
}
#endif /* PARSER_H */

//CREATE TABLE( last string, first string )