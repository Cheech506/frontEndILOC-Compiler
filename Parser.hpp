#ifndef Parser_HPP
#define Parser_HPP

#include "Scanner2.hpp"

class Parser {
    private:
        string fileName = "/Users/coreycicci/Downloads/Scanner_Project/t2.i";
        bool  isFileOpen = false;
        Scanner *scanner = new Scanner(fileName);
        void printToken(Token &t);
        bool finishMEMOP(Token &t, char &c, threeAddressCode &irStruct);
        bool finishLOADI(Token &t, char &c, threeAddressCode &irStruct);
        bool finishARITHOP(Token &t, char &c, threeAddressCode &irStruct);
        bool finishOUTPUT(Token &t, char &c, threeAddressCode &irStruct);
        bool finishNOP(Token &t, char &c, threeAddressCode &irStruct);
        bool finishCOMMENT(Token &t, char &c, threeAddressCode &irStruct);
        bool isEndOfLine(Token &t);
    public:
        Parser(string fileName);
        ~Parser();
        void Parse();   
};

#endif /* Parser_HPP */