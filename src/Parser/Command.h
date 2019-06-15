#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <ostream>
#include <map>

struct Command{
    Command();
    Command(std::string table, std::map<std::string, std::string> str, int type);

    std::string table_name;
    std::map<std::string, std::string> command;
    int type;
};
Command::Command(){
    command = std::map<std::string, std::string>();
    type = -1;
}
Command::Command(std::string table, std::map<std::string, std::string> str, int type){
    table_name = table;
    command = str;
    this->type = type;
}
#endif /* COMMAND_H */