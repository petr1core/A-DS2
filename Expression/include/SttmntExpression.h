//
// Created by egorm on 20.04.2024.
//

#ifndef RUNNABLEEXPRESSION_H
#define RUNNABLEEXPRESSION_H
#include <utility>
#include <vector>
#include "Expression.h"
#include "../Parser/include/Parser.h"
#include "../Parser/include/stdc++.h"
#include "stdexcept"
#include "../Lexer/include/Lexer.h"
#include "../Token/include/Token.h"
#include "../Postfix/include/Postfix.h"

static int i = 1;
class SttmntExpression : public Expression {
private:
    std::vector<Token> list;
public:
    SttmntExpression() { cout << list.size(); }
    SttmntExpression(std::vector<Token> _list)
    {
        list = std::move(_list);
    }
    void add(Token t) { list.push_back(t); }
    void print() override {
        std::cout << "StateExpression " << i << " = ";
        for (auto token : list) {
            std::cout << token.getValue() << " ";
        }
        i++;
        std::cout << endl;

    }
    void toSolve() {
        int i = 0;
        if (list.front().getValue() == "Write") {//3 варианта: текст, переменную, текст с переменной
            list[i + 3].getType() == "СOMMA" ?
                cout << list[i + 2].getValue() << list[i + 4].getValue() :
                cout << list[i + 2].getValue();
        }
        if (list.front().getValue() == "Writeln") {
            list[i + 3].getType() == "СOMMA" ?
                cout << list[i + 2].getValue() << list[i + 4].getValue() :
                cout << list[i + 2].getValue();
            cout << endl;
        }
        if (list.front().getValue() == "Read") {
            //обращение к таблице, добавить в неё значение с клавиатуры
        }
        if (list.front().getValue() == "Readln") {
            //обращение к таблице, добавить в неё значение с клавиатуры
            cout << endl;
        }
        else { TPostfixCalc p(list); }//происходит выражение с присвоением
    }

    /*void run() override {
        //for (auto Expression: expressionList) {
          //  Expression->run();
        //}
    }*/
};
#endif //RUNNABLEEXPRESSION_H
