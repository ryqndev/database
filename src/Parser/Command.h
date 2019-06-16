#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <ostream>
#include <map>
#include <vector>

struct Command{
    Command();
    Command(std::string table, std::map<std::string, std::string> command, int type, std::vector<std::string> order);

    std::string table_name;
    std::map<std::string, std::string> command;
    std::vector<std::string> order;
    int type;
};
Command::Command(){
    table_name = "";
    command = std::map<std::string, std::string>();
    order = std::vector<std::string>();
    type = -1;
}
Command::Command(std::string table_name, std::map<std::string, std::string> command, int type, std::vector<std::string> order){
    this->table_name = table_name;
    this->command = command;
    this->type = type;
    this->order = order;
}
#endif /* COMMAND_H */