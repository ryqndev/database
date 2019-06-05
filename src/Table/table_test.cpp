/** run command:

g++ -std=c++11 table_test.cpp -o table_test 
./table_test

*/

#include "Table.h"
#include <iostream>

void test_constructor(bool isPublic = true){
    // testing table constructor without columns
    Table students("students");

    if(isPublic){
        std::cout << "Table name: " << students.table_name << std::endl;        
    }

    // manually set up table info as if it were a sql query
    std::map<std::string, std::string> table_setup = {
        { "firstName", "string" },
        { "lastName", "string" },
        { "major", "string" },
        { "graduationYear", "unsigned" }
    };

    students = Table("students", table_setup);

    
}

int main(int argc, char const *argv[]){
    test_constructor();
    return 0;
}
