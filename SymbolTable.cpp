#include <iostream>
#include "SymbolTable.h"

using namespace std;
SymbolTable::~SymbolTable(){}
///to do : call this in admin instead of constructor
//Inserts PL reserve words into the symbol table.
void SymbolTable::loadReserve(){

	insert("begin");
	insert("end");
	insert("const");
	insert("array");
	insert("integer");
	insert("Boolean");
	insert("proc");
	insert("skip");
	insert("read");
	insert("write");
	insert("call");
    insert("if");
	insert("do");
	insert("fi");
	insert("od");
	insert("false");
	insert("true");

}

//search the symbol table for a given lexeme, return position if found, -1 if not
int SymbolTable::search(string lex){

	int hash = hashfunc(lex);
	int done = hash; //if the table is full, keep track of where the search started in case the lexeme is not found

	if(htable[hash] == ""){ //not found
		return -1;
	} else if(htable[hash] == lex){
		return hash;
	} else { //look at the next table entry
		++hash;
		if(hash == done) return -1; //finish search if the entire table has been looked at
		if(hash == TABLESIZE) hash = 0; //wrap to 0 if max size reached
	}
	/*
	//for using full tokens
	if(htable[hash]->getLexeme() == ""){ //not found
		return -1;
	} else if(htable[hash]->getLexeme() == lex){ //found
		return hash;
	} else { //look at the next table entry
		++hash;
		if(hash == done) return -1; //finish search if the entire table has been looked at
		if(hash == TABLESIZE) hash = 0; //wrap to 0 if max size reached
	}
	*/
	return -1;
}

//insert a given lexeme into the table
//this is mostly for the initial scanning phase, will insert tokens in future phases
int SymbolTable::insert(string lex){

	int hash = hashfunc(lex);

	while(htable[hash] != ""){
		if(htable[hash] == lex) //if the lexeme matches (in the scope) then don't add it to the table but return
         return hash;
      ++hash;
		if(hash == TABLESIZE)
			hash = 0;
	}

   //insert into the table
   htable[hash] = lex;
   ++occupied;
   return hash;
}

/// TOKENS ///
//
//int SymbolTable::search(NameToken *tok){
//
//	int hash = hashfunc(tok->getLexeme());
//
//	if(htable[hash]->getLexeme() == ""){
//		return -1;
//	}
//	else
//		return hash;
//
//}
//
//int SymbolTable::insert(NameToken *tok){
//
//	int hash = hashfunc(tok->getLexeme());
//
//	while(htable[hash]->getLexeme() != ""){
//      if(htable[hash]->getLexeme() == tok->getLexeme())
//         return hash;
//		++hash;
//		if(hash == TABLESIZE)
//			hash = 0;
//	}
//	htable[hash] = tok;
//
//	++occupied;
//	return hash;
//}

/// tokens done ///

//djb2 hash function
int SymbolTable::hashfunc(string lexeme){

    unsigned long hash = 5381;
    for (char c : lexeme) {
        hash = (hash << 5) + hash + c;
    }
	hash = hash%TABLESIZE; //adjust the given hash to fit into the table
    return hash;
}

//print the symbol table to the console, for testing/debugging purposes only
void SymbolTable::printTable(){

	for(int i = 0; i < TABLESIZE; ++i){
		cout << i << " = " << htable[i] << endl;
	}

}
