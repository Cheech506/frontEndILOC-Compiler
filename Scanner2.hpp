#ifndef Scanner2_HPP
#define Scanner2_HPP
#include <string>
#include <fstream>
#include <vector>
#include "Constants.hpp"

using namespace std;

class Scanner {
protected:
    FILE * pFile;
    Pos position;
    char getChar();
    char nextChar(Token &t);
    char peekChar(Token &t);
    void pushChar(char argC, Token &t);
    bool isNewLine(char c);
    bool isWhiteSpace(char argC);
public:
    const int LF = 10;
    Scanner(string fileName);
    ~Scanner();
    Token getNextToken(Token &t, char &c);
    Token getNextNextToken(Token &t, char &c);
    void readFileByChar(string fileName);
    void scanRegister(Token &t, char &c);
    void scanOpCode(Token &t, char &c);
    void outputTokenLexAndOPCode(Token &t);
};
#endif /* Scanner2_HPP */