#ifndef IRClass_HPP
#define IRClass_HPP

#include "Scanner2.hpp"
#include "Parser.hpp"
#include "Constants.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class IRClass {
    private:
        ofstream fout;
        string fileName;
        bool isFileOpen = false;
    public:
        IRClass(string fileName);
        bool IsFileOpen();
        void writeLine(struct threeAddressCode irStruct);
        ~IRClass();

};

#endif /* IRClass.hpp */