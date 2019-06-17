#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
//---------------------------------------------------------------------
// normal run:
//---------------------------------------------------------------------
Database started.
> make table employee fields  last string,       first string,                 dep string,  salary unsigned,    year unsigned
insert into employee values Blow,       Joe,             CS,         100000,    2018
insert into employee values Blow,       JoAnn,                 Physics, 200000,    2016
insert into employee values Johnson,    Jack,                  HR, 150000,    2014
insert into employee values Johnson,    "Jimmy",         Chemistry,140000,    2018
insert into employee values Yao,        Jimmy,                 Math,145000,    2014
insert into employee values "Yao",            Flo,             CS,147000,    2012
insert into employee values Yang,       Bo,              CS,160000,    2013
insert into employee values Jackson,    "Flo",                 Math,165000,    2017
insert into employee values Jackson,    Bo,                    Chemistry,130000,    2011
insert into employee values "Jackson",  Billy,                 Math,  170000,    2017
insert into employee values Johnson,    "Mary Ann> > > > > > > > > > > ath,165000,    2014
insert into employee values Johnson,    "Billy Bob",     Physics,142000,    2014
insert into employee values Johnson,    Billy,                 "Phys Ed",102000,    2014
insert into employee values "Van Gogh", Vincent,         Art,240000,    2015
insert into employee values "Van Gogh", Vincent,         CS,245000,    2015
insert into employee values "Van Gogh", "Jim Bob",       "Phys Ed",230000,    2010
select * from employee
make table student fields fname string, lname string, major string, age unsigned, company string
insert into student values Flo,               Yao,       CS, 20,   Google
insert into student values Bo,                     Yang,            CS, 28,        Microsoft
insert into student values "Sammuel L.",      Jackson,   CS, 40,        Uber
insert into student values "Flo",             "Jackson",  Math,  21,        Google
insert into student values "Greg",                 "Pearson",  Physics,20,        Amazon
in> > > > > > 
 Table Name: employee, Records: 16

              record                last               first                 dep              salary                year

                   0                Blow                 Joe                  CS              100000                2018
                   1                Blow               JoAnn             Physics              200000                2016
                   2             Johnson                Jack                  HR              150000                2014
                   3             Johnson               Jimmy           Chemistry              140000                2018
                   4                 Yao               Jimmy                Math              145000                2014
                   5                 Yao                 Flo                  CS              147000                2012
                   6                Yang                  Bo                  CS              160000                2013
                   7             Jackson                 Flo                Math              165000                2017
                   8             Jackson                  Bo           Chemistry              130000                2011
                   9             Jackson               Billy                Math              170000                2017
                  10             Johnson            Mary Ann                Math              165000                2014
                  11             Johnson           Billy Bob             Physics              142000                2014
                  12             Johnson               Billy             Phys Ed              102000                2014
                  13            Van Gogh             Vincent                 Art              240000                2015
                  14            Van Gogh             Vincent                  CS              245000                2015
                  15            Van Gogh             Jim Bob             Phys Ed              230000                2010

> > > > > > > sert into student values "Jim Bob",         Smith,           Math,  23,        Verizon
insert into student values Calvin,                 Woo,       Physics,22,        Uber
insert into student values "Anna Grace",      "Del Rio",  CS,    22,        USAF
insert into student values "Teresa Mae",      Gowers,    Chemistry,22,        Verizon
insert into student values Alex,              Smith,           "Gender Studies",  53,        Amazon
select * from student> > > > > 

 Table Name: student, Records: 10

              record               fname               lname               major                 age             company

                   0                 Flo                 Yao                  CS                  20              Google
                   1                  Bo                Yang                  CS                  28           Microsoft
                   2          Sammuel L.             Jackson                  CS                  40                Uber
                   3                 Flo             Jackson                Math                  21              Google
                   4                Greg             Pearson             Physics                  20              Amazon
                   5             Jim Bob               Smith                Math                  23             Verizon
                   6              Calvin                 Woo             Physics                  22                Uber
                   7          Anna Grace             Del Rio                  CS                  22                USAF
                   8          Teresa Mae              Gowers           Chemistry                  22             Verizon
                   9                Alex               Smith      Gender Studies                  53              Amazon


*/
#endif // Z_OUTPUT_H