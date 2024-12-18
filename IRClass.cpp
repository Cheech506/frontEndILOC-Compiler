#ifndef IRCLASS_CPP
#define IRCLASS_CPP

#include "IRClass.hpp"
#include "Constants.hpp"


IRClass::IRClass(string binFile)
{
    this->fileName = binFile;
    cout << "===========================================" << endl;
    cout << "Opening IR output file..." << endl;
  
    fout.open(fileName, ios::out | ios::binary | ios::trunc);

    if (fout.is_open()) 
    {
        cout << "Successfully opened IR file." << endl;
        isFileOpen = true;
    }
    else
    {
        perror ("Error opening IR file");
        isFileOpen = false;
    }
}

void IRClass::writeLine(struct threeAddressCode irStruct) {
    unsigned int irLine[5] = {irStruct.lineNumber, irStruct.opCode, irStruct.operand1, irStruct.operand2, irStruct.operand3 };
    fout.write((char*) &irLine, sizeof(irLine));        
}

bool IRClass::IsFileOpen()
{
    return isFileOpen;
}

IRClass::~IRClass()
{
    cout << "IRClass Destructor: Closing IR File..." << endl;
    fout.close();
}






#endif // IRCLASS_CPP