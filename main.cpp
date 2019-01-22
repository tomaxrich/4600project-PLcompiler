//Author: Thomas Richardson

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "Administration.h"
#include "Token.h"
#include "Scanner.h"

using namespace std;

int main(int argc, char* argv[]){
   cout << "Welcome to Our 4600 compiler!\n";

   ifstream ifs;
   ofstream ofs;
   string infile, outfile;

   infile = argv[1];
   outfile = argv[2];

   cout << "input from : " << infile << "  output to : " << outfile << endl;

   ofs.open(outfile, ofstream::out);
   ifs.open(infile, ifstream::in);

   SymbolTable symtab;

   Scanner sc(ifs, symtab);

   Administration compiler(ifs, ofs, sc);

   compiler.scan();

   cout << "Total Line count" << compiler.getLinecount() << '\n';

   cout << "done\n";


return 0;
}
