#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <ostream>
#include <map>

class Command{
    public:
        Command();
        Command(std::string table, std::map<std::string, std::string> str, int type);
        int type();
        std::map<std::string, std::string> getCommand();
        
        friend std::ostream& operator << (std::ostream& outs, const Command& t){
            std::cout << "|" << t._type << "|";
            return outs;
        }

    private:
        std::string _table_name;
        std::map<std::string, std::string> _command;
        int _type;
};
Command::Command(){
    _command = std::map<std::string, std::string>();
    _type = -1;
}
Command::Command(std::string table, std::map<std::string, std::string> str, int type){
    _table_name = table;
    _command = str;
    _type = type;
}
int Command::type(){
    return _type;
}
std::map<std::string, std::string> Command::getCommand(){
    return _command;
}

#endif /* COMMAND_H */