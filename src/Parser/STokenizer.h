#ifndef STRING_TOKENIZER_H
#define STRING_TOKENIZER_H

#include "Command.h"

const int MAX_COLUMNS = 128;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 512;

class STokenizer{
    public:
        STokenizer();
        STokenizer(char str[]);
        bool is_done();
        friend STokenizer& operator >> (STokenizer& s, Command& t);
        void set_string(char str[]);
    private:
        void make_table(int _table[][MAX_COLUMNS]);
        void get_token(int start_state, Command& token);
        char _buffer[MAX_BUFFER];
        int _pos;
        static int _table[MAX_ROWS][MAX_COLUMNS];
};
int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer(){
    make_table(&_table[0]);
    _pos = 0;
}
STokenizer::STokenizer(char str[]){
    make_table(&_table[0]);
    set_string(str);
}
void STokenizer::set_string(char str[]){
    _pos = 0;
    memcpy(_buffer, str, sizeof(_buffer));
}
bool STokenizer::is_done(){
    return _pos > strlen(_buffer);
}
void STokenizer::get_token(int start_state, Command& t){
    std::map<std::string, std::string> command_properties;
    std::string table_name, key_holder;
    int cur_state = start_state,
        state_level = 0,
        token_type = -1;
    while( !(cur_state > strlen(_buffer)) && state_level != -1 ){
        switch(state_level){
            case 13:
                start_state = cur_state;
                break;
            case 14:
                token_type = 1; // is create command
                table_name = std::string(&_buffer[start_state], &_buffer[ cur_state]);
                break;
            case 22:
                start_state = cur_state;
                break;
            case 24:
                key_holder = std::string(&_buffer[start_state], &_buffer[ cur_state]);
                break;
            case 26:
            default:
                break;
        }
        state_level = _table[state_level][(int)_buffer[cur_state]];
        cur_state += 1;
    }
    cur_state += cur_state == start_state + 1 ? 1 : -1; // move on if invalid token
    // command_properties = std::string(&_buffer[start_state], &_buffer[cur_state]);
    _pos = cur_state;                   // move position
    t = Command(table_name, command_properties, token_type); // sets token
}
void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    //set all values to fail states
    for(int i = 0 ; i < MAX_ROWS; i++){
        std::fill_n(_table[i], MAX_COLUMNS, -1);
    }

    //create table
    _table[0][77] = 1;      // M
    _table[1][65] = 2;      // A
    _table[2][75] = 3;      // K
    _table[3][69] = 6;      // E

    _table[0][67] = 1;      // C
    _table[1][82] = 2;      // R
    _table[2][69] = 3;      // E
    _table[3][65] = 4;      // A
    _table[4][84] = 5;      // T
    _table[5][69] = 6;      // E
    _table[6][32] = 7;      // 
    _table[7][84] = 8;      // T
    _table[8][65] = 9;      // A
    _table[9][66] = 10;     // B
    _table[10][76] = 11;    // L
    _table[11][69] = 12;    // E

    _table[0][109] = 1;     // m
    _table[1][97] = 2;      // a
    _table[2][107] = 3;     // k
    _table[3][101] = 6;     // e

    _table[0][99] = 1;      // c
    _table[1][114] = 2;     // r
    _table[2][101] = 3;     // e
    _table[3][97] = 4;      // a
    _table[4][116] = 5;     // t
    _table[5][101] = 6;     // e
    _table[7][116] = 8;     // t
    _table[8][97] = 9;      // a
    _table[9][98] = 10;     // b
    _table[10][108] = 11;   // l
    _table[11][101] = 12;   // e
    _table[12][32] = 13;    // 

    // table name
    std::fill_n(&_table[13][65], 26, 14);
    std::fill_n(&_table[13][97], 26, 14);

    std::fill_n(&_table[14][65], 26, 14);
    std::fill_n(&_table[14][97], 26, 14);
    std::fill_n(&_table[14][48], 10, 14); //numbers after first letter
    _table[14][32] =  15;
    _table[15][32] =  15;

    _table[14][0] = 1; //success states, create table with name
    _table[15][0] = 1; //success states, create table with name

    _table[15][102] = 16;     // f
    _table[16][105] = 17;     // i
    _table[17][101] = 18;     // e
    _table[18][108] = 19;     // l
    _table[19][100] = 20;     // d
    _table[20][115] = 21;     // s

    _table[15][70] = 16;     // F
    _table[16][73] = 17;     // I
    _table[17][69] = 18;     // E
    _table[18][76] = 19;     // L
    _table[19][68] = 20;     // D
    _table[20][83] = 21;     // S

    _table[21][32] = 22;
    _table[22][32] = 22;

    std::fill_n(&_table[22][65], 26, 23);
    std::fill_n(&_table[22][97], 26, 23);

    std::fill_n(&_table[23][65], 26, 24);
    std::fill_n(&_table[23][97], 26, 24);
    std::fill_n(&_table[23][48], 10, 24); //numbers after first letter

    _table[23][32] = 24;
    _table[24][32] = 25;
    _table[25][32] = 25;

    std::fill_n(&_table[25][65], 26, 26);
    std::fill_n(&_table[25][97], 26, 26);

    _table[26][32] = 27;
    _table[26][32] = 27;

    _table[26][0] = 1;
    _table[27][0] = 1;
    // field type
    // std::fill_n(&_table[15][65], 26, 15);
    // std::fill_n(&_table[15][97], 26, 15);
    // _table[15][32] =  15;
    // _table[15][0] = 1;

    // _table[15][44] =  16;   // ,

}
STokenizer& operator >> (STokenizer& s, Command& t){
    s.get_token(s._pos, t);
    return s;
}

#endif /* STRING_TOKENIZER_H */