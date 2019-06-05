#ifndef TABLE_H
#define TABLE_H

#include "Record.h"
#include <iostream>
#include <vector>
#include <map> // later include own implementation of b+tree

class Table{
    public:
        Table(std::string);
        Table(std::string, std::map<std::string, std::string>);

        bool insert_row(std::map<std::string, std::string>);

    // TODO - uncomment private after testing
    // private: 
        static std::map<std::string, unsigned> data_sizes;
        // maps column names to the maps that map a value to a record(s)
        std::map<std::string, std::map<std::string, std::vector<int> > > columns;

        // record will be a way to read and write the data on disk
        Record record;
        std::string table_name;
        
};

std::map<std::string, unsigned> Table::data_sizes = {
    { "string", 100 },
    { "unsigned", 20 },
};

Table::Table(std::string table_name){
    this->table_name = table_name;
}

Table::Table(std::string table_name, std::map<std::string, std::string> table_contents){
    this->table_name = table_name;
    
    //creates individual record for this table's unique row size
    unsigned record_size = 0;

    // for each column, update record and column maps
    for( auto const& col_data : table_contents ){
        // create map for each column
        this->columns[col_data.first] = std::map<std::string, std::vector<int> >();

        // get size of record
        record_size += data_sizes[col_data.second];
    }

    this->record = Record(record_size);
}

bool Table::insert_row(std::map<std::string, std::string>){

}

#endif /* TABLE_H */