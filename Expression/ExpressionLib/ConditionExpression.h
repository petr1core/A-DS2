//
// Created by shuri on 26.04.2024.
//

#ifndef CONDITIONEXPRESSION_H
#define CONDITIONEXPRESSION_H
#include <vector>
#include "Expression.h"
#include "../Parser/ParserLib/Parser.h"
//#include <bits/stdc++.h>
#include "stdexcept"
#include "../Lexer/LexerLib/Lexer.h"
#include "../Token/TokenLib/Token.h"
#include "../Postfix/PostfixLib/Postfix.h"

using namespace std;

class ConditionExpression: public Expression{
private:
    std::vector<Expression*> expressionList;
    std::vector<Token> condition;
public:
    ConditionExpression(std::vector<Token>_condition, std::vector<Token>_list){
        RunnableExpression re(_list);
        TPostfixCalc p(_condition);
    }
    void run() override {
       // for (auto Expression: expressionList) {
         //   Expression.run();
        //}
    }
};


#endif //CONDITIONEXPRESSION_H
