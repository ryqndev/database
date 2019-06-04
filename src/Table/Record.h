#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <fstream>

bool file_exists(const char filename[]);

void open_fileRW(std::fstream& f, const char filename[]) throw(char*);
void open_fileW(std::fstream& f, const char filename[]);

class Record{
    public:
        Record(){
            MAX = 0;
            recno = -1;
        }
        Record(char str[]){
            strcpy(record, str);
        }
        long write(std::fstream& outs);
        long read(std::fstream& ins, long recno);

        friend std::ostream& operator<<(std::ostream& outs, const Record& r);
    private:
        unsigned MAX;
        int recno;
        char record[MAX];
};
long Record::write(std::fstream &outs){
    //write to the end of the file.
    long pos = outs.tellp();

    outs.write(&record[0], sizeof(record));
    // outs.write(record, sizeof(record));

    return pos;
}
long Record::read(std::fstream &ins, long recno){
    long pos = recno * sizeof(record);
    ins.seekg(pos, std::ios_base::beg);

    ins.read(record, sizeof(record));
    return ins.gcount();
}
std::ostream& operator<<(std::ostream& outs, const Record& r){
    outs<<r.record;
    return outs;
}

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
void save_list(Record list[], int count){
    std::fstream f;
    open_fileW(f, "record_list.bin");
    for (int i= 0; i<count; i++){
        list[i].write(f);
    }
    f.close();

}

#endif /* RECORD_H */