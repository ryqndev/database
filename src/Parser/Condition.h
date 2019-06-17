#ifndef CONDITION_H
#define CONDITION_H

#include <iostream>

struct Condition{
    std::string column_name;    //name of column
    unsigned operand;           // < > <= >= = !=
    std::string value;          // value to be compared with
    unsigned connector = 0;             // and/or

    friend std::ostream& operator<<(std::ostream& outs, Condition& c){
        outs << c.column_name << " " << c.operand << " " << c.value << " " << c.connector << " ";
        return outs;
    }
};
/**
 * 0 : <
 * 1 : >
 * 2 : <=
 * 3 : >=
 * 4 : = 
 */
/**
 * If the connector is "and" isFirst, immediately execute query and set that as current
 * If is "or" and isFirst, fulfill first condition 
 * 
 */

#endif /* CONDITION_H */