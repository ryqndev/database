#ifndef COMMAND_H
#define COMMAND_H

// TODO : remove
#define Map std::map

#include "Condition.h"
#include <iostream>
#include <ostream>
#include <map>
#include <vector>

struct Command{
    Command();
    Command(std::string, Map<std::string, std::string>, int, std::vector<std::string>, std::vector<Condition>);

    std::string table_name;
    Map<std::string, std::string> command;
    std::vector<std::string> order;
    std::vector<Condition> conditions;
    int type;
};
Command::Command(){
    table_name = "";
    command = Map<std::string, std::string>();
    order = std::vector<std::string>();
    type = -1;
}
Command::Command(
    std::string table_name,
    Map<std::string,
    std::string> command,
    int type,
    std::vector<std::string> order,
    std::vector<Condition> conditions
){
    this->table_name = table_name;
    this->command = command;
    this->type = type;
    this->order = order;
    this->conditions = conditions;
}
#endif /* COMMAND_H */