//
// Created by egorm on 20.04.2024.
//

#ifndef RUNNABLEEXPRESSION_H
#define RUNNABLEEXPRESSION_H
#include <vector>
#include "Expression.h"
#include "../Parser/ParserLib/Parser.h"
// #include "stdexcept"
#include "../Lexer/LexerLib/Lexer.h"
#include "../Token/TokenLib/Token.h"
#include "../Postfix/PostfixLib/Postfix.h"

class RunnableExpression : public Expression {
private:
    std::vector<Token> list;
public:
    RunnableExpression(std::vector<Token> _list){
        TPostfixCalc p(list);
    }


    void run() override {
        //for (auto Expression: expressionList) {
          //  Expression->run();
        //}
    }
};
#endif //RUNNABLEEXPRESSION_H
