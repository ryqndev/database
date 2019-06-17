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
    Map<std::string, std::string> command_properties;
    std::vector<std::string> order;
    std::vector<Condition> conditions;
    std::string table_name, key_holder;
    Condition c_temp;
    int cur_state = start_state,
        prev_state = -1,
        state_level = 0,
        token_type = -1;
    while( !(cur_state > strlen(_buffer)) && state_level != -1 ){
        switch(state_level){
            case 13:
                start_state = cur_state;
                break;
            case 14:
                token_type = 0; // is create command
                table_name = std::string(&_buffer[start_state], &_buffer[ cur_state]);
                break;
            case 22: // start of field
                token_type = -1;
                if(prev_state == 25 || prev_state == 26){
                    command_properties[key_holder] = std::string(&_buffer[start_state], &_buffer[cur_state - 1]);
                }
                start_state = cur_state;
                break;
            case 24:
                token_type = 1;
                if(prev_state != 24) key_holder = std::string(&_buffer[start_state], &_buffer[ cur_state - 1]);
                order.push_back(key_holder);
                start_state = cur_state;
                break;
            case 25:
                command_properties[key_holder] = std::string(&_buffer[start_state], &_buffer[cur_state]);
                break;


            case 41:
                start_state = cur_state;
                break;
            case 42:
                token_type = 2;
                table_name = std::string(&_buffer[start_state], &_buffer[ cur_state ]);
                break;
            case 50: // FIXME : cannot have spaces after insert values
                start_state = cur_state;
                break;
            case 51:
                token_type = 2;
                if(prev_state == 51) order.pop_back(); // super hacky - please fix when writing new string tokenizer
                order.push_back(std::string(&_buffer[start_state], &_buffer[cur_state]));
                break;
            case 52:
                if(prev_state == 54 || prev_state == 55){
                    order.push_back(std::string(&_buffer[start_state], &_buffer[cur_state - 1]));
                }
                break;
            case 54:
                start_state = cur_state;
                break;

            case 73:
                start_state = cur_state;
                break;
            case 74:
                token_type = 3;
                table_name = std::string(&_buffer[start_state], &_buffer[cur_state]);
                break;
            case 81:
                start_state = cur_state;
                break;
            case 82:
                c_temp.column_name = std::string(&_buffer[start_state], &_buffer[cur_state]);
                break;
            case 84:
                start_state = cur_state;
                c_temp.operand = 0;
                break;
            case 85:
                start_state = cur_state;
                c_temp.operand = 4;
                break;
            case 86:
                start_state = cur_state;
                c_temp.operand = 1;
                break;
            case 87:
                start_state = cur_state;
                c_temp.operand = 2;
                break;
            case 88:
                start_state = cur_state;
                c_temp.operand = 3;
                break;
            case 89:
                if(prev_state == 89) conditions.pop_back();
                c_temp.value = std::string(&_buffer[start_state], &_buffer[cur_state]);
                conditions.push_back(c_temp);
                break;
            case 90:
                if(prev_state == 98 || prev_state == 99){
                    c_temp.value = std::string(&_buffer[start_state], &_buffer[cur_state]);
                    std::cout << c_temp.value << std::endl;
                    conditions.push_back(c_temp);
                } 
                break;
            case 93:
                c_temp.connector = 1;
                conditions.pop_back();
                conditions.push_back(c_temp);
                break;
            case 95:
                c_temp.connector = 2;
                conditions.pop_back();
                conditions.push_back(c_temp);
                break;
            case 98:
                start_state = cur_state;
                break;
            default:
                break;
        }
        prev_state = state_level;
        state_level = _table[state_level][(int)_buffer[cur_state]];
        cur_state += 1;
    }
    if(!conditions.empty()) std::cout << conditions[0] << std::endl;
    cur_state += cur_state == start_state + 1 ? 1 : -1; // move on if invalid token
    _pos = cur_state;                   // move position
    t = Command(table_name, command_properties, token_type, order, conditions); // sets token
}
void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    //set all values to fail states
    for(int i = 0 ; i < MAX_ROWS; i++){
        std::fill_n(_table[i], MAX_COLUMNS, -1);
    }
    //create table
    _table[0][32] = 0;      // M

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
    _table[7][32] = 7;
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
    _table[13][32] = 13;    // 

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

    std::fill_n(&_table[23][65], 26, 23);
    std::fill_n(&_table[23][97], 26, 23);
    std::fill_n(&_table[23][48], 10, 23); //numbers after first letter

    _table[23][32] = 24;
    _table[24][32] = 24;

    std::fill_n(&_table[24][65], 26, 25);
    std::fill_n(&_table[24][97], 26, 25);

    std::fill_n(&_table[25][65], 26, 25);
    std::fill_n(&_table[25][97], 26, 25);

    _table[25][32] = 26;

    _table[25][44] = 22;
    _table[26][44] = 22;

    _table[25][0] = 1;
    _table[26][0] = 1;

    // insert into

    _table[0][105] = 30;    // i
    _table[30][110] = 31;   // n
    _table[31][115] = 32;   // s
    _table[32][101] = 33;   // e
    _table[33][114] = 34;   // r
    _table[34][116] = 35;   // t
    _table[35][32] = 36;    // 
    _table[36][32] = 36;    // 
    _table[36][105] = 37;   // i
    _table[37][110] = 38;   // n
    _table[38][116] = 39;   // t
    _table[39][111] = 40;   // o
    _table[40][32] = 41;    // 
    _table[41][32] = 41;    // 

    _table[0][73] = 30;    // I
    _table[30][78] = 31;   // N
    _table[31][83] = 32;   // S
    _table[32][69] = 33;   // E
    _table[33][82] = 34;   // R
    _table[34][84] = 35;   // T
    _table[36][73] = 37;   // I
    _table[37][78] = 38;   // N
    _table[38][84] = 39;   // T
    _table[39][79] = 40;   // O

    std::fill_n(&_table[41][65], 26, 42);
    std::fill_n(&_table[41][97], 26, 42);

    std::fill_n(&_table[42][65], 26, 42);
    std::fill_n(&_table[42][97], 26, 42);
    std::fill_n(&_table[42][48], 10, 42); //numbers after first letter

    _table[42][32] = 43; 
    _table[43][32] = 43; 

    _table[43][118] = 44;   // v
    _table[44][97] = 45;    // a
    _table[45][108] = 46;   // l
    _table[46][117] = 47;   // u
    _table[47][101] = 48;   // e
    _table[48][115] = 49;   // s

    _table[43][86] = 44;   // V
    _table[44][65] = 45;   // A
    _table[45][76] = 46;   // L
    _table[46][85] = 47;   // U
    _table[47][69] = 48;   // E
    _table[48][83] = 49;   // S

    _table[49][32] = 50; 
    _table[50][32] = 50;

    _table[50][34] = 54;
    std::fill_n(&_table[54][32], 93, 55);
    std::fill_n(&_table[55][32], 93, 55);
    _table[54][34] = 52;
    _table[55][34] = 52;


    std::fill_n(&_table[50][65], 26, 51);
    std::fill_n(&_table[50][97], 26, 51);
    std::fill_n(&_table[50][48], 10, 51);

    std::fill_n(&_table[51][65], 26, 51);
    std::fill_n(&_table[51][97], 26, 51);
    std::fill_n(&_table[51][48], 10, 51);

    _table[51][44] = 50; //comma 
    _table[51][0] = 1;

    _table[51][32] = 52;
    _table[52][32] = 52;
    _table[52][44] = 50;

    //select command

    _table[0][115] = 60;    // s
    _table[60][101] = 61;   // e
    _table[61][108] = 62;   // l
    _table[62][101] = 63;   // e
    _table[63][99] = 64;    // c
    _table[64][116] = 65;   // t
    _table[65][32] = 66;    // 
    _table[66][32] = 66;    // 
    _table[66][42] = 67;    // *
    _table[67][32] = 68;    // 
    _table[68][32] = 68;    // 
    _table[68][102] = 69;   // f
    _table[69][114] = 70;   // r
    _table[70][111] = 71;   // o
    _table[71][109] = 72;   // m
    _table[72][32] = 73;    // 
    _table[73][32] = 73;    // 

    std::fill_n(&_table[73][65], 26, 74);
    std::fill_n(&_table[73][97], 26, 74);

    std::fill_n(&_table[74][65], 26, 74);
    std::fill_n(&_table[74][97], 26, 74);
    std::fill_n(&_table[74][48], 10, 74); //numbers after first letter

    _table[74][32] = 75;  
    _table[75][32] = 75;  

    _table[75][119] = 76;   // w
    _table[76][104] = 77;   // h
    _table[77][101] = 78;   // e
    _table[78][114] = 79;   // r
    _table[79][101] = 80;   // e

    _table[80][32] = 81;  
    _table[81][32] = 81;  

    // column name
    std::fill_n(&_table[81][65], 26, 82);
    std::fill_n(&_table[81][97], 26, 82);

    std::fill_n(&_table[82][65], 26, 82);
    std::fill_n(&_table[82][97], 26, 82);
    std::fill_n(&_table[82][48], 10, 82); //numbers after first letter

    _table[82][32] = 83;  
    _table[83][32] = 83;

    _table[82][60] = 84;  // < 
    _table[82][61] = 85;  // =
    _table[82][62] = 86;  // > 

    _table[83][60] = 84;  
    _table[83][61] = 85;  
    _table[83][62] = 86;  

    _table[84][61] = 87;  // <=
    _table[86][61] = 88;  // >=

    _table[84][32] = 84;  
    _table[85][32] = 85;
    _table[86][32] = 86;
    _table[87][32] = 87;
    _table[88][32] = 88;

    _table[84][34] = 98;
    std::fill_n(&_table[98][32], 93, 99);
    std::fill_n(&_table[99][32], 93, 99);
    _table[99][34] = 90;

    std::fill_n(&_table[84][65], 26, 89);
    std::fill_n(&_table[84][97], 26, 89);
    std::fill_n(&_table[84][48], 10, 89);

    std::fill_n(&_table[85][65], 26, 89);
    std::fill_n(&_table[85][97], 26, 89);
    std::fill_n(&_table[85][48], 10, 89);

    std::fill_n(&_table[85][65], 26, 89);
    std::fill_n(&_table[85][97], 26, 89);
    std::fill_n(&_table[85][48], 10, 89);

    std::fill_n(&_table[86][65], 26, 89);
    std::fill_n(&_table[86][97], 26, 89);
    std::fill_n(&_table[86][48], 10, 89);

    std::fill_n(&_table[87][65], 26, 89);
    std::fill_n(&_table[87][97], 26, 89);
    std::fill_n(&_table[87][48], 10, 89);

    std::fill_n(&_table[88][65], 26, 89);
    std::fill_n(&_table[88][97], 26, 89);
    std::fill_n(&_table[88][48], 10, 89);

    std::fill_n(&_table[89][65], 26, 89);
    std::fill_n(&_table[89][97], 26, 89);
    std::fill_n(&_table[89][48], 10, 89);

    _table[89][32] = 90;
    _table[90][32] = 90;

    _table[90][97] = 91; // a
    _table[91][32] = 92; // n
    _table[92][32] = 93; // d

    _table[90][97] = 94; // o
    _table[94][32] = 95; // r

    _table[93][32] = 81;
    _table[95][32] = 81;

}
STokenizer& operator >> (STokenizer& s, Command& t){
    s.get_token(s._pos, t);
    return s;
}

#endif /* STRING_TOKENIZER_H */