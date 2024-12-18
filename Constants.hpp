#ifndef Constants_HPP
#define Constants_HPP

#include <string>
using namespace std; 

// EOL 
static const int CHAR_LF = 10; 
static const int CHAR_CR = 13; 

// WHITE SPACE
static const int CHAR_SPACE = 32; 
static const int CHAR_TAB = 9; 

// SLIDE: 04-Lab1-Scanner, Page 5 
// >>> ILOC OPeration Codes <<<
enum
{
    OP_LOAD,
    OP_STORE,
    OP_LOADI,
    OP_ADD,
    OP_SUB,
    OP_MULT,
    OP_LSHIFT,
    OP_RSHIFT,
    OP_OUTPUT,
    OP_NOP
};

// SLIDE: 04-Lab1-Scanner, Page 6 
// >>> ILOC Syntactic CATEGORIES <<<
enum
{
    CAT_MEMOP,
    CAT_LOADI,
    CAT_ARITHOP,
    CAT_OUTPUT,
    CAT_NOP,
    CAT_CONSTANT,
    CAT_REGISTER,
    CAT_COMMA,
    CAT_INTO,
    CAT_EOL,
    CAT_EOF,
    CAT_COMMENT,
    CAT_ERR
};

struct Pos {
    int line;
    int col;
};

struct Token {
    int category;
    int lex;
    //int opCode;
    Pos position;

    Token(int cat, int lex, int line, int col) {
        this->category = cat;
        this->lex = lex;
        this->position.line = line;
        this->position.col = col;
    }
};

struct threeAddressCode {
    unsigned int lineNumber;
    unsigned int opCode;
    unsigned int operand1;
    unsigned int operand2;
    unsigned int operand3;

    threeAddressCode(unsigned int lineNumber, unsigned int opCode, unsigned int operand1, unsigned int operand2, unsigned int operand3) {
        this->lineNumber = lineNumber;
        this->opCode = opCode;
        this->operand1 = operand1;
        this->operand2 = operand2;
        this->operand3 = operand3;
    }
};



#endif /* Constants_HPP */