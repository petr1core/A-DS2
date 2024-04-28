#include <iostream>
#include <regex>
#include<string>
#include "../Token/TokenLib/Token.h"
#include"../Lexer/LexerLib/Lexer.h"
#include "../Parser/ParserLib/Parser.h"
using namespace std;


int main() {
    string test_text =
        "program qq;"
        "const"
        "Pi: real = 3.1415926;"
        "var"
        "num1, num2, i: integer;"
        "Res, d: real;"
        "res2: string;"
        "begin"
        "res2 := 'Hello world';"
        "num1:=2;"
        "Write('Reader ', res2);"
        "if Pi=num1 then begin"
        "Write('Yes');"
        "end"
        "else begin"
        "Write('No');"
        "end;"
        "num1:= num1 div 2;"
        "for i:=1 to 8 do begin"
        "Write(i);"
        "end;"
        "end.";
    Lexer lexer(test_text);
}