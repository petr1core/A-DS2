//
// Created by egorm on 21.04.2024.
//

#ifndef PARSER_H
#define PARSER_H
#include "stdc++.h"
#include "stdexcept"
#include "../Lexer/include/Lexer.h"
#include "../Token/include/Token.h"
#include "../HierarchyList/include/HierarchyList.h"
#include "../Expression/include/ExceptionAST.h"
#include "../Expression/include/Expression.h"
#include "../Expression/include/RunnableExpression.h"
#include "../Expression/include/ConditionExpression.h"
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
    //HierarchyList hierarchyList;
    int currentPos = 0;
public:
    explicit Parser(Lexer lexer) {
        this->tokenList = lexer.getTokenList();
    }
    void parse() {
        initDeclaration();
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
        //initBegin();
    }
    void print() {
        for (auto& item : expressionList) {
            //item->print();
            cout << "k";
        }
        // cout<<expressionList.size();
    }
    void initRowStatement() {//метод чтобы строчку кода (не условие и не цикл) переводить в RunnableExpression
        RunnableExpression rx;
        while (!isTypeToken("SEMICOLON")) {
            if (isTypeToken("VAR")) continue;
            rx.add(tokenList[currentPos]);
            currentPos++;
        }
        expressionList.push_back(&rx);
        currentPos++;
        return;
    }
    void initBegin() {
        std::vector<Token> condition;
        while (!isTypeToken("ENDofPROGRAM")) {
            if ((isTypeToken("CONDITION")) || (isTypeToken("CYCLEFOR")) ||
                (isTypeToken("CYCLEWHILE")) || (isTypeToken("CYCLEDOWHILE"))) {
                ConditionExpression cx(currentPos, tokenList);
                currentPos = cx.getGlobalPos();
                expressionList.push_back(&cx);
            }
            else {
                initRowStatement();
                initBegin();
                return;
            }
        }

        return;

    }
    /*void initVar() {
        if (isTypeToken("VAR")) {
            currentPos++;
            while (!isTypeToken("BEGIN")) {
                initVariables(); }
        }
        else { throw AgeException( "Don't exist VAR!"); }
    }
    void initVariables() {
        while(!isTypeToken("SEMICOLON")) {
            if(isTypeToken("SPACE")) continue;
            if(!isTypeToken("VARIABLE")) {
                throw AgeException("Var is expected!");}
            else { currentPos++; initAssign();}
        }
    }
    void initAssign(){
        while(!isTypeToken("SEMICOLON")){
            if(isTypeToken("SPACE")) continue;
            if (isTypeToken("COLON"))
            {currentPos++; initType(); }
            else{throw AgeException("assign is not present"); }
        }
    }
    void initType(){
        while(!isTypeToken("SEMICOLON")){
            if(isTypeToken("SPACE")) continue;
            if((isTypeToken("TYPEINTEGER"))||
            (isTypeToken("TYPEREAL"))||
            (isTypeToken("TYPECHAR"))||
            (isTypeToken("TYPESTRING")))
            {throw AgeException("type is present");}
            else{currentPos++;}
        }
    }*/
    bool isTypeToken(const string& typeToken) {
        return tokenList[currentPos].getType() == typeToken;
    }
};
#endif //PARSER_H
