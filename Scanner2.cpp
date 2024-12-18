#ifndef SCANNER2_CPP
#define SCANNER2_CPP
#include "Scanner2.hpp"
#include "Constants.hpp"
#include <iostream>
#include <cstring>

Scanner::Scanner(string fileName) {
    cout << "Scanner Constructor" << endl;
    position.line = 1;
    position.col = 0;
    pFile=fopen ("/Users/coreycicci/Downloads/Scanner_Project/t2.i","r");
    //pFile=fopen ("Users\\cboss\\Downloads\\Scanner_Project\\t2.i","r");
    //pFile=fopen (fileName,"r");
    if (pFile==NULL) perror ("Error opening file");
    else
    {
        cout << "File opened successfully" << endl;
    }
    
}

Scanner::~Scanner() {
    cout << "Scanner Destructor" << endl;
    fclose(pFile);
}

void Scanner::readFileByChar(string fileName) {
    cout << "===========================================" << endl;
    cout << "readFileByChar Filename: " << fileName << endl;
    FILE * pFile;
    char c;
    // This should use the filename parameter, but just a demo...
    pFile=fopen ("/Users/coreycicci/Downloads/Downloads_Files_for_Mac/Scanner_Project/t2.i","r");
    // pFile=fopen (fileName,"r");
    if (pFile==NULL) perror ("Error opening file");
    else
    {
        do {
            c = getc (pFile);
            
            if (int(c) == LF) {
                cout << endl;
            } else if (int(c) == EOF) {
                cout << endl;
            } else {
                // cout << "(" << c << "," << int(c) << ")";
                cout << c;
            }
            } while (c != EOF);
        fclose (pFile);
    }
}

bool Scanner::isWhiteSpace(char argC) {
    int cInt = int(argC);
    return (cInt == CHAR_SPACE || cInt == CHAR_TAB) ? true : false;
}

char Scanner::getChar() {
    char c = getc(pFile);
    c = ungetc(c, pFile);
    return c;
}

char Scanner::nextChar(Token &t) {
    char c = getc(pFile);
    t.position.col++;
    return c;
}

char Scanner::peekChar(Token &t) {
    char c = getc(pFile);
    ungetc(c, pFile);
    t.position.col--;
    return c;
}

void Scanner::pushChar(char c, Token &t) {
    c = ungetc(c, pFile);
    t.position.col--;
}

Token Scanner::getNextNextToken(Token &t, char &c) {

    //char c;
    
    t.lex = 0;
    
    // Remove leading white space
    do {
        c = nextChar(t);
        cout << "Processing char(" << c << "," << int(c) << ")" << endl;
    } while ((isWhiteSpace(c)) && (c != EOF));
    c = nextChar(t);
    c = nextChar(t);
    cout << "Processing char(" << c << "," << int(c) << ")" << endl;
    if (c == EOF) {
            t.category = CAT_EOF;
            t.position.line++;
            t.position.col = 0;
            return t;
        } 
        
    else if (c == 'r') {
        if (peekChar(t) == 's') {
            pushChar(c,t);
            cout << "Found Possible RShift" << endl;
            scanOpCode(t, c);
        } else {
            cout << "Found Possible Register" << endl;
            scanRegister(t,c);
            return t;
        }
    }
    else if (c == 1 || c == 2 || c == 3 || c == 4 || c == 5 || c == 6 || c == 7 || c == 8 || c == 9) {
        t.category = CAT_CONSTANT;
        t.lex = c - '0';
    }
    else if (c == EOF) {
            t.category = CAT_EOF;
            t.position.line++;
            t.position.col = 0;
            return t;
        } 
    scanOpCode(t, c);
    //cout << c << endl;
    return t;
    /* 
    char c;
    t.lex = 0;

    while (true) {
        c = nextChar();

        if (isspace(c)) {
            c = peekChar();
            if (isNewLine(c)) {
            position.line++;
            position.col = 0;
            } else if (isspace(c)) {
            continue;
            }
        } else if (isdigit(c)) {
            pushChar(c);
            scanRegister(t);
            t.position = position;
            return t;
        } else if (isalpha(c)) {
            pushChar(c);
            scanOpCode(t);
            t.position = position;
            return t;
        } else if (c == EOF) {
            t.category = CAT_EOF;
            t.lex = 0;
            t.position = position;
            return t;
        } else {
            t.category = CAT_ERR;
            t.lex = 0;
            t.position = position;
            return t;
        }
    } */
}

Token Scanner::getNextToken(Token &t, char &c) {

    //char c;
    t.lex = 0;
    
    // Remove leading white space
    do {
        c = nextChar(t);
        //cout << "Processing char(" << c << "," << int(c) << ")" << endl;
    } while ((isWhiteSpace(c)) && (c != EOF));

    if (c == EOF) {
            t.category = CAT_EOF;
            t.position.line++;
            t.position.col = 0;
            return t;
        } 
        
    else if (c == 'r') {
        //c = nextChar(t);
        if (peekChar(t) == 's') {
            pushChar(c,t);
            cout << "Found Possible RShift" << endl;
            scanOpCode(t, c);
            return t;
        } else {
            //cout << "Found Possible Register" << endl;
            //pushChar(c,t);
            scanRegister(t, c);
            return t;
        }
    } else if (c == EOF) {
            t.category = CAT_EOF;
            t.position.line++;
            t.position.col = 0;
            return t;
        } else if (c == '/') {
        t.category = CAT_COMMENT;
        t.lex = 0;
        cout << "COMMENT: " << t.lex << endl;
        int cInt = int(c);
        do {
            c = nextChar(t);
            cInt = int(c);
            if (cInt == -1) {
                cout << endl;
                return t;
            }
            cout << c;
            //cInt = int(c);
        } while (!isNewLine(c) && cInt != -1);

        cout << endl;
        
        return t;
        }

    scanOpCode(t, c);
    return t;
    
}

void Scanner::scanRegister(Token &t, char &c) {
    //char c;
    bool isNumber = false;
    bool isError = true;
    
    t.lex = 0;
    do {
        isNumber = false;
        c = nextChar(t);
        //c = peekChar(t);
        if (c >= '0' && c <= '9')
        {
            isError = false;
            isNumber = true;
            int cInt = int(c);
            cout << "ASCII Value: " << c << ", " << cInt << endl;
            int integerC = cInt - '0';
            t.lex = t.lex * 10 + integerC;
            cout << "INT Value: " << t.lex << endl;
            //c = peekChar(t);
            
        }
    } while (isNumber && !isNewLine(c));

    pushChar(c,t);
        
    if (isError)
    {
        t.category = CAT_ERR;
        t.lex = 0;
    }
    else 
    {
        t.category = CAT_REGISTER;
    }
    
}


bool Scanner::isNewLine(char argC) {
    int cInt = int(argC);
    return (cInt == CHAR_LF || cInt == CHAR_CR) ? true : false;
}

void Scanner::scanOpCode(Token &t, char &c) {
        if (c == 'r') {
            c = nextChar(t);
            c = nextChar(t);
            if (c == 's') {
                c = nextChar(t);
                if (c == 'h') {
                    c = nextChar(t);
                    if (c == 'i') {
                        c = nextChar(t);
                        if (c == 'f') {
                            c = nextChar(t);
                            if (c == 't') {
                                t.category = CAT_ARITHOP;
                                t.lex = OP_RSHIFT;

                            }
                        }
                    }
                }
            } 
        } else if (c == 's') {
            c = nextChar(t);
            if (c == 't') {
                c = nextChar(t);
                if (c == 'o') {
                    c = nextChar(t);
                    if (c == 'r') {
                        c = nextChar(t);
                        if (c == 'e') {
                            t.category = CAT_MEMOP;
                            t.lex = OP_STORE;
                        }
                    }
                }
            } else if (c == 'u') {
            c = nextChar(t);
            if (c == 'b') {
                t.category = CAT_ARITHOP;
                t.lex = OP_SUB;
            } else {
                t.category = CAT_ERR;
                t.lex = 0;
            }
        }
        } else if (c == 'l') {
            c = nextChar(t);
                if (c == 'o') {
                    c = nextChar(t);
                    if (c == 'a') {
                        c = nextChar(t);
                        if (c == 'd') {
                            t.category = CAT_MEMOP;
                            t.lex = OP_LOAD;
                            c = peekChar(t);
                            if (c == 'i' || c == 'I') {
                                t.category = CAT_LOADI;
                                t.lex = OP_LOADI;
                            } 
                        } 
                    }
                }
                if (c == 's') {
                    c = nextChar(t);
                    if (c == 'h') {
                        c = nextChar(t);
                        if (c == 'i') {
                            c = nextChar(t);
                            if (c == 'f') {
                                c = nextChar(t);
                                if (c == 't') {
                                    t.category = CAT_ARITHOP;
                                    t.lex = OP_LSHIFT;
                                }
                            }
                        }
                    }
                }
        } else if (c == 's') {
            c = nextChar(t);
                if (c == 'h') {
                    c = nextChar(t);
                        if (c == 'i') {
                            c = nextChar(t);
                            if (c == 'f') {
                                c = nextChar(t);
                                if (c == 't') {
                                    t.category = CAT_ARITHOP;
                                    t.lex = OP_LSHIFT;
                                }
                            }
                        }
                    }
        } else if (c == 'a') {
                c = nextChar(t);
                if (c == 'd') {
                    c = nextChar(t);
                    if (c == 'd') {
                        t.category = CAT_ARITHOP;
                        t.lex = OP_ADD;
                    } 
            }
        } else if (c == 'm') {
            c = nextChar(t);
            if (c == 'u') {
                c = nextChar(t);
                if (c == 'l') {
                    c = nextChar(t);
                    if (c == 't') {
                        t.category = CAT_ARITHOP;
                        t.lex = OP_MULT;
                    } 
                }
            }
        } else if (c == 'o') {
            c = nextChar(t);
            if (c == 'u') {
                c = nextChar(t);
                if (c == 't') {
                    c = nextChar(t);
                    if (c == 'p') {
                        c = nextChar(t);
                        if (c == 'u') {
                            c = nextChar(t);
                            if (c == 't') {
                                t.category = CAT_OUTPUT;
                                t.lex = OP_OUTPUT;
                            }
                        }
                    }
                }
            }
        } else if (c == 'n') {
            c = nextChar(t);
            if (c == 'o') {
                c = nextChar(t);
                if (c == 'p') {
                    t.category = CAT_NOP;
                    t.lex = OP_NOP;
                }
            }
        } else if (c == ',') {
            t.category = CAT_COMMA;
            t.lex = 0;
        } else if (c == '/') {
            t.category = CAT_COMMENT;
            t.lex = 0;
        } else if (c == '=') {
            c = nextChar(t);
            if (c == '>') {
                t.category = CAT_INTO;
                t.lex = 0;
            }
        } else if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
            //char c;
            t.lex = c - '0';
            bool isNumber = false;
            bool isError = true;
            int cInt = int(c);
            cout << "ASCII Value: " << c << ", " << cInt << endl;
            cout << "INT Value: " << t.lex << endl;

            do {
            isNumber = false;
            c = nextChar(t);
            if (c >= '0' && c <= '9')
            {
            isError = false;
            isNumber = true;
            int cInt = int(c);
            cout << "ASCII Value: " << c << ", " << cInt << endl;
            int integerC = cInt - '0';
            t.lex = t.lex * 10 + integerC;
            cout << "INT Value: " << t.lex << endl;
            
        }
    } while (isNumber && !isNewLine(c));
            t.category = CAT_CONSTANT;
            //t.lex = c - '0'; 
            pushChar(c,t);

        } else if (c == EOF) {
        t.category = CAT_EOF;
        t.lex = 0;
    } else if (c == LF) {
        t.category = CAT_EOL;
        t.lex = 0;
    } else if (c == '\n') {
        t.category = CAT_EOL;
        t.lex = 0;
    }
    else {
        t.category = CAT_ERR;
        t.lex = 0;
    }
}


void Scanner::outputTokenLexAndOPCode(Token &t) {
    cout << "Token: " << t.category << endl;
    cout << "Position: " << t.position.line << "," << t.position.col << endl;
    cout << "OP Code: " << t.lex << endl;
}



#endif // SCANNER.CPP
