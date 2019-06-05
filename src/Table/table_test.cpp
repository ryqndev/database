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

    std::map<std::string, std::string> test_student_1 = {
        { "firstName", "Ryan" },
        { "lastName", "Yang" },
        { "major", "Computer Science" },
        { "graduationYear", "2021" }
    };
    std::map<std::string, std::string> test_student_2 = {
        { "firstName", "John" },
        { "lastName", "Doe" },
        { "major", "Economics" },
        { "graduationYear", "2022" }
    };

    students.save_info(test_student_1);
    students.save_info(test_student_2);
    students.get_info(0);
    std::cout << std::endl;
    students.get_info(1);

}

int main(int argc, char const *argv[]){
    test_constructor();
    return 0;
}
