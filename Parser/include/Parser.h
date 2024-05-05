#pragma once
#include "../Expression/include/Expression.h"
#include "../Expression/include/StatementExpression.h"
#include "../Expression/include/ConditionExpression.h"
#include "../ListLinearTable/include/ListLinearTable.h"
#include "../Parser/include/stdc++.h"
#include "../Lexer/include/Lexer.h"
#include "../Token/include/Token.h"
#include "../HierarchyList/include/HierarchyList.h"
#include "stdexcept"

using namespace std;
class AgeException : public std::exception
{
public:
    AgeException(const std::string& message) : message(message) {}
    std::string getMessage() const { std::cout << message; return message; }
private:
    std::string message;
};

class Parser {
private:
    std::vector<Token> tokenList;
    std::vector<Expression*> expressionList;
    std::vector<Token> localList;
    int currentPos = 0;
public:
    Parser() {
        this->currentPos = 0;
        this->expressionList = vector<Expression*>();
        this->localList = vector<Token>();
        this->tokenList = vector<Token>();
    }
    Parser(Lexer lexer) {
        this->tokenList = lexer.getTokenList();
    }
    Parser(vector<Token> t) { this->tokenList = t; }
    void parse() {
        initDeclaration();
        return;
    }
    void initDeclaration() {
        if (isTypeToken("TITLE")) {
            while (!isTypeToken("SEMICOLON")) {
                currentPos++;
            } //скип названия, чтобы дойти до разделов Const или Var
            currentPos++;
        }       //есть вариант вообще название не добавлять уже на стадии Lexer, но мб пригодится

        if ((isTypeToken("VAR")) || (isTypeToken("CONST"))) {
            currentPos++;
            while (!isTypeToken("BEGIN")) {
                initRowStatement();
            }
            currentPos++;
        }
        initBegin();
        return;
    }
    void print() {
        for (auto item : expressionList) {
            item->print();
            //cout<<"k";
        }
        // cout<<expressionList.size();
    }
    void initRowStatement() {//метод чтобы строчку кода (не условие и не цикл) переводить в StatementExpression
        while (!isTypeToken("SEMICOLON")) {
            if (isTypeToken("VAR")) currentPos++;
            localList.push_back(tokenList[currentPos]);
            currentPos++;
        }
        auto* rx = new StatementExpression(localList);
        expressionList.push_back(rx);
        localList.clear();
        currentPos++;
        return;
    }
    void initBegin() {
        std::vector<Token> condition;
        while (!isTypeToken("ENDofPROGRAM")) {
            if ((isTypeToken("CONDITION")) || (isTypeToken("UNCONDITION")) || (isTypeToken("CYCLEFOR")) ||
                (isTypeToken("CYCLEWHILE")) || (isTypeToken("CYCLEDOWHILE")))
            {
                ConditionExpression* cx = new ConditionExpression(currentPos, tokenList);
                currentPos = cx->getGlobalPos();
                expressionList.push_back(cx);

            }
            else
            {
                initRowStatement();
            }
        }
        return;
    }
    bool isTypeToken(const string& typeToken) {
        return tokenList[currentPos].getType() == typeToken;
    }
};
