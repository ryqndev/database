#ifndef STRING_TOKENIZER_H
#define STRING_TOKENIZER_H

#include "Token.h"
#include "Command.h"

const int MAX_COLUMNS = 128;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 512;

class STokenizer{
    public:
        STokenizer();
        STokenizer(char str[]);
        bool is_done();
        friend STokenizer& operator >> (STokenizer& s, Token& t);
        void set_string(char str[]);
    private:
        void make_table(int _table[][MAX_COLUMNS]);
        void get_token(int start_state, Token& token);
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
void STokenizer::get_token(int start_state, Token& t){
    std::string token_value;
    int cur_state = start_state,
        state_level = 0,
        token_type = -1;
    while( !(cur_state > strlen(_buffer)) && state_level != -1 ){
        switch(state_level){
            case 14:
                token_type = 1; // is create command
                break;
            default:
                break;
        }
        state_level = _table[state_level][(int)_buffer[cur_state]];
        cur_state += 1;
    }
    cur_state += cur_state == start_state + 1 ? 1 : -1; // move on if invalid token
    token_value = std::string(&_buffer[start_state], &_buffer[cur_state]);
    _pos = cur_state;                   // move position
    t = Token(token_value, token_type); // sets token
}
void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    //set all values to fail states
    for(int i = 0 ; i < MAX_ROWS; i++){
        std::fill_n(_table[i], MAX_COLUMNS, -1);
    }
    // //spaces
    // _table[0][32] = 9;  //init
    // _table[9][0] = 1;   //success state
    // _table[9][32] = 9; 

    // //alpha
    // _table[5][0] = 1;   //success state
    // std::fill_n(&_table[0][65], 26, 5);
    // std::fill_n(&_table[0][97], 26, 5);
    // std::fill_n(&_table[5][65], 26, 5);
    // std::fill_n(&_table[5][97], 26, 5);

    // // //numbers
    // _table[1][0] = 1;   //success state
    // _table[2][0] = 0;   //not yet success
    // _table[3][0] = 1;   //success

    // std::fill_n(&_table[0][48], 10, 1);
    // std::fill_n(&_table[1][48], 10, 1);
    // std::fill_n(&_table[2][48], 10, 3);
    // std::fill_n(&_table[3][48], 10, 3);
    
    // _table[1][46] = 3;

    //create table
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

    _table[14][0] = 1; //success states, create table with name

    // field type
    // std::fill_n(&_table[15][65], 26, 15);
    // std::fill_n(&_table[15][97], 26, 15);
    // _table[15][32] =  15;
    // _table[15][0] = 1;

    // _table[15][44] =  16;   // ,

}
STokenizer& operator >> (STokenizer& s, Token& t){
    s.get_token(s._pos, t);
    return s;
}

#endif /* STRING_TOKENIZER_H */