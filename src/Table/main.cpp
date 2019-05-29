#include "Record.h"


int main(int argc, char *argv[])
{
    std::cout <<std::endl<<std::endl<<std::endl<< "================================" << std::endl;
    Record list[10] = {"zero",
                       "one",
                       "two",
                       "three",
                       "four",
                       "five",
                       "six",
                       "seven",
                       "eight",
                       "nine"};
    for (int i = 0; i< 10; i++){
        std::cout<<list[i]<<std::endl;
    }
    save_list(list, 10);


    Record r;
    std::fstream f;
    open_fileRW(f, "record_list.bin" );
    r.read(f, 3);
    std::cout<<"record 3: "<<r<<std::endl;
    r.read(f, 6);
    std::cout<<"record 6: "<<r<<std::endl;

    std::cout <<std::endl<<std::endl<<std::endl<< "================================" << std::endl;
    return 0;
}
