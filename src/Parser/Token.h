#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <ostream>

class Token{
    public:
        Token();
        Token(std::string str, int type);
        friend std::ostream& operator << (std::ostream& outs, const Token& t){
            std::cout << "|" << t._token << "|";
            return outs;
        }
        int type();
        std::string type_string();
        std::string token_str();
    private:
        std::string _token;
        int _type;
};
Token::Token(){
    _token = "";
    _type = -1;
}
Token::Token(std::string str, int type){
    _token = str;
    _type = type;
}
int Token::type(){
    return _type;
}
std::string Token::type_string(){
    switch(_type){
        case 0:
            return "SPACE";
        case 1:
            return "ALPHA";
        case 2:
            return "NUMBER";
        default:
            return "UNKNOWN";
    }
}
std::string Token::token_str(){
    return _token;
}

#endif /* TOKEN_H */-0