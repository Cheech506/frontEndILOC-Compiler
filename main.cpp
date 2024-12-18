#include <iostream>
#include "Scanner2.hpp"
#include "Parser.hpp"
#include "IRClass.hpp"

using namespace std;

int main() {
    
    string fileName2 = "/Users/coreycicci/Downloads/Scanner_Project/t2.i";
    string binFile = "/Users/coreycicci/Downloads/Scanner_Project/IROutputFile.bin";
    Parser parser(fileName2);
    parser.Parse();

    return 0;
}

/*

If you see in this code, if you go to the debugg console, I made it so that it outputs the IR
struct to the console so  you  don't have to open the binary file to see the output.
You can still on in the bin file and see the output but it just made is easier to debug and for you
to check the output. I don't know if you would want to keep that in the final version of the code but
I just left it there. 
you can always go in line 89 of Parser.cpp and comment out the cout statement if you don't want to see the output

// Why is this outputing a bunch of f and x's?

*/