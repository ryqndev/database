#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <map> // later include own implementation of b+tree

class Table{
    public:
        Table(std::string);
        Table(std::string, std::map<std::string, std::string>);

    private: 
        static std::map<std::string, unsigned> data_sizes;
        std::string table_name;
        
};

std::map<std::string, unsigned> Table::data_sizes = {
    { "string", 100 }
};

Table::Table(std::string table_name){
    this->table_name = table_name;
}

Table::Table(std::string table_name, std::map<std::string, std::string> table_contents){
    this->table_name = table_name;

}


#endif /* TABLE_H */