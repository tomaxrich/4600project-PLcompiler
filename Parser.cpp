#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Symbol.h"
#include "Token.h"

Parser(Scanner &a, SymbolTable &sym){
    symbolPointer = sym;
    scannerPointer = a;

};

~Parser(){
    delete symbolPointer;
    delete tokenPointer;
    delete scannerPointer;

};

void getToken(){
    sym.
};

