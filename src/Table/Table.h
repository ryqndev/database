#ifndef TABLE_H
#define TABLE_H

#include "Record.h"
#include <iostream>
#include <vector>
#include <map> // later include own implementation of b+tree

class Table{
    public:
        Table(std::string);
        Table(std::string, std::map<std::string, std::string>&);

        void save_info(std::map<std::string, std::string>&);
        std::map<std::string, std::string> get_info(long location);
        std::vector<long> query();

    private: 
        // maps column names to the maps that map a value to a record(s)
        std::map<std::string, std::map<std::string, std::vector<long> > > columns;

        // record will be a way to read and write the data on disk
        Record record;
        std::string table_name;
};

Table::Table(std::string table_name){
    this->table_name = table_name;
}

Table::Table(std::string table_name, std::map<std::string, std::string>& table_contents){
    this->table_name = table_name;
    std::map<std::string, EntryLocation> location_of;

    //creates individual record for this table's unique row size
    unsigned record_size = 0;

    // for each column, update record and column maps
    for( auto const& col_data : table_contents ){
        // create map for each column
        this->columns[col_data.first] = std::map<std::string, std::vector<long> >();
        location_of[col_data.first].start = record_size;    // location start in record
        record_size += record.data_sizes[col_data.second];  // get size of record
        location_of[col_data.first].end = record_size;      // location end in record
    }
    this->record = Record(location_of, record_size, table_name);
}

void Table::save_info(std::map<std::string, std::string>& row){
    long recno = this->record.write(row);
    /**
     * TODO : separate below for loop into separate function and pass function into
     * record.write to stop double for loops that can be combined
     */
    for( auto const& pair : row ){
        columns[pair.first][pair.second].push_back(recno);
    }
}
std::map<std::string, std::string> Table::get_info(long location){
    return this->record.read(location);
}

std::vector<long> Table::query(){
    return std::vector<long>();
}

#endif /* TABLE_H */