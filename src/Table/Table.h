#ifndef TABLE_H
#define TABLE_H
#define Map std::map

#include "Record.h"
#include "../Parser/Condition.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <map> // later include own implementation of b+tree

class Table{
    public:
        Table(std::string);
        Table(std::string, Map<std::string, std::string>&, std::vector<std::string>);

        void insert_row(std::vector<std::string> row);
        void save_info(Map<std::string, std::string>&);
        Map<std::string, std::string> get_info(long location);
        void display_contents(std::vector<Condition>);
        std::vector<long> query(std::vector<Condition>&);
        std::vector<long> filter(Condition& c);

        void debug();

    private: 
        // maps column names to the maps that map a value to a record(s)
        Map<std::string, Map<std::string, std::vector<long> > > columns;
        std::vector<std::string> order;
        // record will be a way to read and write the data on disk
        Record record;
        std::string table_name;
};
void Table::debug(){
    for(auto& x : columns){
        std::cout << "Column: " << x.first << std::endl;
        for(auto& y : x.second){
            std::cout << y.first << " - [";
            for(auto z = y.second.begin(); z != y.second.end(); z++){
                std::cout << " " << *z << " ";
            }
            std::cout << " ]" << std::endl;
        }
    }
}

Table::Table(std::string table_name){
    this->table_name = table_name;
}

Table::Table(std::string table_name, Map<std::string, std::string>& table_contents, std::vector<std::string> order){
    this->table_name = table_name;
    Map<std::string, EntryLocation> location_of;

    //creates individual record for this table's unique row size
    unsigned record_size = 0;

    // for each column, update record and column maps
    for( auto const& col_data : table_contents ){
        // create map for each column
        this->columns[col_data.first] = Map<std::string, std::vector<long> >();
        location_of[col_data.first].start = record_size;    // location start in record
        record_size += record.data_sizes[col_data.second];  // get size of record
        location_of[col_data.first].end = record_size;      // location end in record
    }
    this->order = order;
    this->record = Record(location_of, record_size, table_name);
}

void Table::insert_row(std::vector<std::string> row){
    Map<std::string, std::string> row_data;
    for(auto a = row.begin(), b = order.begin(); a != row.end() && b != order.end(); a++, b++){
        row_data[*b] = *a;
    }
    save_info(row_data);
}

void Table::save_info(Map<std::string, std::string>& row){
    long recno = this->record.write(row);
    /**
     * TODO : separate below for loop into separate function and pass function into
     * record.write to stop double for loops that can be combined
     */
    for( auto const& pair : row ){
        columns[pair.first][pair.second].push_back(recno);
    }
}
Map<std::string, std::string> Table::get_info(long location){
    return this->record.read(location);
}

void Table::display_contents(std::vector<Condition> conditions){
    std::vector<long> results = query(conditions);
    std::cout << "\n Table Name: " << table_name << ", Records: " << results.size() << "\n\n";
    std::cout << std::setw(20) << "record";
    for(auto a = order.begin(); a != order.end(); a++){
        std::cout << std::setw(20) << *a;
    }
    std::cout << std::endl << std::endl;
    int i = 0;
    for(auto a = results.begin(); a != results.end(); a++, i++){
        std::cout << std::setw(20) << i;
        Map<std::string, std::string> result = record.read(*a);
        for(auto b = order.begin(); b != order.end(); b++){
            std::cout << std::setw(20) << result[*b];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
std::vector<long> Table::query(std::vector<Condition>& conditions){
    std::vector<long> query;
    if(conditions.empty()){
        for(int i = 0; i <= record.recno; i++) query.push_back(i);
        return query;
    }
    return filter(conditions[0]);
}

std::vector<long> Table::filter(Condition& c){
    std::vector<long> query;
    switch(c.operand){
        case 2: // <=
            query.insert( query.end(), columns[c.column_name][c.value].begin(), columns[c.column_name][c.value].end());
        case 0: // <
            for(auto x = columns[c.column_name].begin(); x != --columns[c.column_name].upper_bound(c.value); x++){
                query.insert( query.end(), (*x).second.begin(), (*x).second.end());
            }
            break;
        case 3: // >=
            query.insert( query.end(), columns[c.column_name][c.value].begin(), columns[c.column_name][c.value].end());
        case 1: // >
            for(auto x = ++columns[c.column_name].lower_bound(c.value); x != columns[c.column_name].end(); x++){
                query.insert( query.end(), (*x).second.begin(), (*x).second.end());
            }
            break;
        case 4: // =
            query.insert( query.end(), columns[c.column_name][c.value].begin(), columns[c.column_name][c.value].end());
            break;
    }
    return query;
}

#endif /* TABLE_H */