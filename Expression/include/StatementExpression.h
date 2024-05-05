#pragma once
#include "Expression.h"
#include "../Parser/include/Parser.h"
#include "../Parser/include/stdc++.h"
#include "../Lexer/include/Lexer.h"
#include "../Token/include/Token.h"
#include "stdexcept"
#include <vector>
#include <utility>

class StatementExpression : public Expression {
private:
    int i = 1;
    std::vector<Token> list;
public:
    StatementExpression() {
        cout << list.size();
    }
    StatementExpression(std::vector<Token> _list) {
        list = std::move(_list);
    }
    StatementExpression(const StatementExpression& ex) {
        this->i = ex.i;
        this->list = ex.list;
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
        //
    }
    vector<Token> getStatement() {
        return this->list;
    }

    string getStringExpression() {
        string exp;
        for (auto item : list) {
            exp += item.getValue();
        }
        return exp;
    }

    bool isEmpty() {
        return list.empty();
    }
};
