#ifndef RECORD_H
#define RECORD_H

#include "EntryLocation.h"
#include <map>
#include <iostream>
#include <fstream>

bool file_exists(const char filename[]);

void open_fileRW(std::fstream& f, const char filename[]) throw(char*);
void open_fileW(std::fstream& f, const char filename[]);

class Record{
    public:
        Record():max(0), recno(-1){}
        Record(std::map<std::string, EntryLocation> location_of, unsigned max, std::string table_name):recno(-1){
            this->location_of = location_of;
            this->max = max;
            file_name = table_name + ".bin";
            open_fileRW(this->f, file_name.c_str() );
        }

        std::map<std::string, std::string> read(long recno);
        long write(std::map<std::string, std::string>& entry);

        // TODO - a write specifically to a certain recno
        // void write(std::map<std::string, std::string> entry, long recno);

        friend std::ostream& operator<<(std::ostream& outs, const Record& r);
        static std::map<std::string, unsigned> data_sizes;

    private:
        int recno;
        unsigned max;
        std::fstream f;
        std::string file_name;
        std::map<std::string, EntryLocation> location_of; 

        long write(std::fstream& outs, char* data, unsigned size);
        long read(std::fstream& ins, long recno, char* data, unsigned size);
};
std::map<std::string, unsigned> Record::data_sizes = {
    { "string", 100 },
    { "unsigned", 20 }
};
long Record::write(std::fstream& outs, char* data, unsigned size){
    //write to the end of the file.
    long pos = outs.tellp();

    // outs.write(&record[0], sizeof(record));
    outs.write(data, size);

    return pos;
}
long Record::read(std::fstream& ins, long recno, char* data, unsigned size){
    long pos = recno * size;
    ins.seekg(pos, std::ios_base::beg);

    ins.read(data, size);
    return ins.gcount();
}
std::string extract(char* start, char* end){
    char* i;
    for(i = start; i < end && *i != '\0'; i++);
    return std::string(start, i - 1);
}
std::map<std::string, std::string> Record::read(long recno){
    char* raw_data = new char[max];
    read(f, recno, raw_data, max);
    std::map<std::string, std::string> parsed_data;
    for( auto const& pair : location_of){
        parsed_data[pair.first] = 
            extract(
                &raw_data[location_of[pair.first].start],
                &raw_data[location_of[pair.first].end]
            );
    }
    delete[] raw_data; // strange workaround to bug. may be a memory leak
    return parsed_data;
}


long Record::write(std::map<std::string, std::string>& entry){
    char data[max]; // doesn't need to be cstring as we already know size
    for( auto const& pair : entry ){
        const char* temp = pair.second.c_str();
        strncpy(data + location_of[pair.first].start, temp, strlen(temp));
        data[location_of[pair.first].start + strlen(temp) + 1 ] = '\0';
    }
    write(f, data, max);
    return ++recno;
}

// std::ostream& operator<<(std::ostream& outs, const Record& r){
//     outs<<r.record;
//     return outs;
// } 

bool file_exists(const char filename[]){
    const bool debug = false;
    std::fstream ff;
    ff.open (filename,
        std::fstream::in | std::fstream::binary );
    if (ff.fail()){
        if (debug) std::cout<<"file_exists(): File does NOT exist: "<<filename<<std::endl;
        return false;
    }
    if (debug) std::cout<<"file_exists(): File DOES exist: "<<filename<<std::endl;
    ff.close();
    return true;
}

void open_fileRW(std::fstream& f, const char filename[]) throw(char*){
    const bool debug = false;
    //openning a nonexistent file for in|out|app causes a fail()
    //  so, if the file does not exist, create it by openning it for
    //  output:
    if (!file_exists(filename)){
        f.open(filename, std::fstream::out|std::fstream::binary);
        if (f.fail()){
            std::cout << "file open (RW) failed: with out|" << filename << "]" << std::endl;
            throw("file RW failed  ");
        }
        else{
            if (debug) std::cout<<"open_fileRW: file created successfully: "<<filename<<std::endl;
        }
    }else{
        f.open (filename,
            std::fstream::in | std::fstream::out| std::fstream::binary );
        if (f.fail()){
            std::cout<<"file open (RW) failed. ["<<filename<<"]"<<std::endl;
            throw("file failed to open.");
        }
    }

}
void open_fileW(std::fstream& f, const char filename[]){
    f.open (filename,
            std::fstream::out| std::fstream::binary );
    if (f.fail()){
        std::cout<<"file open failed: "<<filename<<std::endl;
        throw("file failed to open.");
    }

}
// void save_list(Record list[], int count){
//     std::fstream f;
//     open_fileW(f, "record_list.bin");
//     for (int i= 0; i<count; i++){
//         list[i].write(f);
//     }
//     f.close();
// }

#endif /* RECORD_H */