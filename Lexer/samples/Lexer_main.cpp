#include <iostream>
#include <regex>
#include<string>
#include "../Token/TokenLib/Token.h"
#include"../Lexer/LexerLib/Lexer.h"
#include "../Parser/ParserLib/Parser.h"
using namespace std;


int main() {
    string test_text =
        "var"
        "a: integer;"
        "b: real;"
        "begin"
        "a:=3;"
        "end.";
    Lexer lexer(test_text);
}