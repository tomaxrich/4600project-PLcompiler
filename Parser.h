#ifndef PARSER_H
#define PARSER_H

class Parser {

public:
    Parser(Scanner &a, SymbolTable &sym);

    ~Parser();

private:
    Scanner &scannerPointer;

    Token *tokenPointer;

    SymbolTable *symbolPointer;

    void getToken();

};
#endif // PARSER_H
