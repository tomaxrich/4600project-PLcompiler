#include <iostream>
#include "SymbolTable.h"

using namespace std;

SymbolTable::SymbolTable():occupied(0), htable(TABLESIZE){

	for(int i = 0; i < TABLESIZE; i++){
		htable[i] = nullptr; //make sure everything is null until asigned
	}
loadReserve();

}

SymbolTable::~SymbolTable(){
	for(int i = 0; i < TABLESIZE; i++){
		delete htable[i];
		htable[i] = nullptr;
	}
}

//Inserts PL reserve words into the symbol table.
void SymbolTable::loadReserve(){
	insert(new NameToken(KW_BEGIN, -1, "begin"));
	insert(new NameToken(KW_END, -1, "end"));
	insert(new NameToken(KW_CONST, -1, "const"));
	insert(new NameToken(KW_ARRAY, -1, "array"));
	insert(new NameToken(KW_INTEGER, -1, "integer"));
	insert(new NameToken(KW_BOOLEAN, -1, "Boolean"));
	insert(new NameToken(KW_PROC, -1, "proc"));
	insert(new NameToken(KW_SKIP, -1, "skip"));
	insert(new NameToken(KW_READ, -1, "read"));
	insert(new NameToken(KW_WRITE, -1, "write"));
	insert(new NameToken(KW_CALL, -1, "call"));
	insert(new NameToken(KW_IF, -1, "if"));
	insert(new NameToken(KW_DO, -1, "do"));
	insert(new NameToken(KW_FI, -1, "fi"));
	insert(new NameToken(KW_OD, -1, "od"));
	insert(new NameToken(KW_FALSE, -1, "false"));
	insert(new NameToken(KW_TRUE, -1, "true"));
}

//search the symbol table for a given lexeme, return position if found, -1 if not
int SymbolTable::search(string lex){

	int hash = hashfunc(lex);
	int done = hash; //if the table is full, keep track of where the search started in case the lexeme is not found

	if(htable[hash]->getLexeme() == ""){ //not found
		return -1;
	} else if(htable[hash]->getLexeme() == lex){ //if the found token matches the given lexeme
		return hash;
	} else { //look at the next table entry
		++hash;
		if(hash == done) return -1; //finish search if the entire table has been looked at
		if(hash == TABLESIZE) hash = 0; //wrap to 0 if max size reached
	}

	return -1;
}

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

int SymbolTable::insert(NameToken *tok){

	if(full()) return search(tok->getLexeme()); //if the table is full, search for the token in table.

	int hash = hashfunc(tok->getLexeme());
	int done = hash;

	//find open cell for the lexeme
	while(htable[hash] != nullptr){
      if(htable[hash]->getLexeme() == tok->getLexeme()){
         return hash; }

		++hash;
		if(hash == done) return -1; //looked for spot in entire table, did not find space or a matching lexeme
		if(hash == TABLESIZE)
			hash = 0;
	}

	htable[hash] = tok;
	tok->setPosition(hash);
	++occupied;

	return hash;
}

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
		cout << i << " = ";
		if(htable[i] == nullptr)
			cout << "--NULL--" <<endl;
		else
			cout << htable[i]->getLexeme() << endl;
	}
	cout << endl;

}
