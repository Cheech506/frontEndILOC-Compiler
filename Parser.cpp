#ifndef PARSER_CPP
#define PARSER_CPP
#include <iostream>

#include "Parser.hpp"
#include "Scanner2.hpp"
#include "IRClass.hpp"

using namespace std;
//char c;

Parser::Parser(string fileName)
{
    this->fileName = fileName;
}


void Parser::Parse()
{
    string binFile = "/Users/coreycicci/Downloads/Scanner_Project/IROutputFile.bin";
    IRClass irClass(binFile);
    Token t(0, 0, 1, 0);
    threeAddressCode irStruct(1, 0, 0, 0, 0);
    int triggerCat;

    cout << "===========================================" << endl;
    cout << "Parser Executing..." << endl;
    cout << "===========================================" << endl;

    int lcv = 0;
    bool isError = false;
    char c;
    do
    {
        irStruct.opCode = 0;
        irStruct.operand1 = 0;
        irStruct.operand2 = 0;
        irStruct.operand3 = 0;
        t = scanner->getNextToken(t, c);
        printToken(t);
        irStruct.opCode = t.lex;
        triggerCat = t.category;
        switch (t.category)
        {
            case CAT_MEMOP:
                isError = finishMEMOP(t, c, irStruct);
                break;
            case CAT_LOADI:
                isError = finishLOADI(t, c, irStruct);
                break;
            case CAT_ARITHOP:
                isError = finishARITHOP(t, c, irStruct);
                break;
            case CAT_OUTPUT:
                isError = finishOUTPUT(t, c, irStruct);
                break;
            case CAT_NOP:
                isError = finishNOP(t, c, irStruct);
                break;
            case CAT_COMMENT:
                t.category = CAT_EOL;
                break;
            case CAT_ERR:
            case CAT_EOL:
            case CAT_EOF:
                cout << "Skipping WHITE space" << endl;
                break;
            default:
                cout << "UNKNOWN Category" << endl;
                isError = true;
            break;
        }
        if (isError) {
            cout << "FAILURE validated syntax for category " << endl;
        } 
        else {
            cout << "SUCCESSfully validated syntax for category " << endl;
            ///*
            if (triggerCat == CAT_COMMENT) {
                cout << "Its a comment....." << endl;
            } else if (triggerCat == CAT_EOF) {
                cout << "Its the end of the file....." << endl;
            } else if (triggerCat == CAT_EOL) {
                cout << "Its the end of the line....." << endl;
            } else if (triggerCat == CAT_ERR) {
                cout << "Its an error....." << endl;
            } else {
                irClass.writeLine(irStruct);
                cout << "the IR struct is: " << irStruct.lineNumber << " " 
                                                << irStruct.opCode << " " 
                                                << irStruct.operand1 << " " 
                                                << irStruct.operand2 << " " 
                                                << irStruct.operand3 << endl;
            }
            //*/

             /*irClass.writeLine(irStruct);
                cout << "the IR struct is: " << irStruct.lineNumber << " " 
                                                << irStruct.opCode << " " 
                                                << irStruct.operand1 << " " 
                                                << irStruct.operand2 << " " 
                                                << irStruct.operand3 << endl;
        }*/
        }
        irStruct.lineNumber++;
        lcv++;
        printToken(t);
    } while ((t.category != CAT_EOF) && (!isError));
    cout << "===========================================" << endl;

    // Clean up
    delete scanner;
}

void Parser::printToken(Token &t)
{
    if (t.category == CAT_ERR)
    {
        cout << "ERROR: " << t.lex << endl;

    }
    else if (t.category == CAT_REGISTER)
    {
        cout << "Register: " << t.lex << endl;
        
    } 
    else if (t.category == CAT_CONSTANT)
    {
        cout << "Constant: " << t.lex << endl;
    }
    else if (t.category == CAT_MEMOP)
    {
        cout << "MEMOP: " << t.lex << endl;
    }
    else if (t.category == CAT_LOADI)
    {
        cout << "LOADI: " << t.lex << endl;
    }
    else if (t.category == CAT_OUTPUT) {
        cout << "OUTPUT: " << t.lex << endl;
    }
    else if (t.category == CAT_NOP) {
        cout << "NOP: " << t.lex << endl;
    }
    else if (t.category == CAT_ARITHOP) {
        cout << "ARITHOP: " << t.lex << endl;
    }
    else if (t.category == CAT_COMMA)
    {
        cout << "COMMA" << endl;
    }
    else if (t.category == CAT_INTO)
    {
        cout << "INTO" << endl;
    }
    else if (t.category == CAT_COMMENT)
    {

    }
    else if (t.category == CAT_EOL)
    {
        cout << "EOL" << endl;
    }
    else if (t.category == CAT_EOF)
    {
        cout << "EOF" << endl;
    }
    else
    {
        cout << "UNKNOWN: " << t.category << endl;
    }

}

bool Parser::finishMEMOP(Token &t,char &c,threeAddressCode &irStruct) 
{
    bool retValue = true;
    t = scanner->getNextToken(t, c);
    if (t.category == CAT_REGISTER)
    {
        // output to irStruct
        irStruct.operand1 = t.lex;
        t = scanner->getNextToken(t, c);
        if (t.category == CAT_INTO)
        {
            t = scanner->getNextToken(t, c);
            if (t.category == CAT_REGISTER)
            {
                // output to irStruct
                irStruct.operand3 = t.lex;
                t = scanner->getNextToken(t, c);
                if (t.category == CAT_EOL || t.category == CAT_EOF) {
                    retValue = false;
                }
            }
        }
    }

    return retValue;
}
bool Parser::finishLOADI(Token &t, char &c, threeAddressCode &irStruct)
{
    bool retValue = true;
    t = scanner->getNextNextToken(t, c);
    if (t.category == CAT_CONSTANT)
    {
        // output to irStruct
        irStruct.operand1 = t.lex;
        t = scanner->getNextToken(t, c);
        if (t.category == CAT_INTO)
        {
            t = scanner->getNextToken(t, c);
            if (t.category == CAT_REGISTER)
            {
                // output to irStruct
                irStruct.operand3 = t.lex;
                t = scanner->getNextToken(t, c);
                if (t.category == CAT_EOL || t.category == CAT_EOF) {
                    retValue = false;
                }
            }
        }
    }
    
    return retValue;
}

bool Parser::finishARITHOP(Token &t, char &c, threeAddressCode &irStruct)
{
    bool retValue = true;
    t = scanner->getNextToken(t, c);
    if (t.category == CAT_REGISTER)
    {
        // output to irStruct
        irStruct.operand1 = t.lex;
        t = scanner->getNextToken(t, c);
        if (t.category == CAT_COMMA)
        {
            t = scanner->getNextToken(t, c);
            if (t.category == CAT_REGISTER)
            {
                // output to irStruct
                irStruct.operand2 = t.lex;
                t = scanner->getNextToken(t, c);
                if (t.category == CAT_INTO)
                {
                    t = scanner->getNextToken(t, c);
                    if (t.category == CAT_REGISTER)
                    {
                        // output to irStruct
                        irStruct.operand3 = t.lex;
                        t = scanner->getNextToken(t, c);
                        if (t.category == CAT_EOL || t.category == CAT_EOF) {
                            retValue = false;
                        }
                    }
                }
            }
        }
    }

    return retValue;
}

bool Parser::finishOUTPUT(Token &t, char &c, threeAddressCode &irStruct)
{
    bool retValue = true;
    t = scanner->getNextToken(t, c);
    if (t.category == CAT_CONSTANT)
    {
        // output to irStruct
        irStruct.operand1 = t.lex;
        t = scanner->getNextToken(t, c);
        if (t.category == CAT_EOL || t.category == CAT_EOF) {
            retValue = false;
        }
    }

    return retValue;
}

bool Parser::finishNOP(Token &t, char &c, threeAddressCode &irStruct)
{
    bool retValue = true;
    t = scanner->getNextToken(t, c);
    if (t.category == CAT_EOL || t.category == CAT_EOF) {
        retValue = false;
    }

    return retValue;
}

bool Parser::finishCOMMENT(Token &t, char &c,threeAddressCode &irStruct)
{
    bool retValue = true;
    t = scanner->getNextToken(t, c);
    if (t.category == CAT_EOL || t.category == CAT_EOF) {
        retValue = false;
    }

    return retValue;
}

bool Parser::isEndOfLine(Token &t)
{
    return (t.category == CAT_EOL || t.category == CAT_EOF);
}

Parser::~Parser()
{
    cout << "Parser Destructor: Adios..." << endl;
}


#endif // PARSER_CPP
