//#include <string>
#include "../Expression/include/Expression.h"
#include "../Expression/include/StatementExpression.h"
#include "../ListLinearTable/include/ListLinearTable.h"
#include "../Postfix/include/Postfix.h"

class Worker {
private:
    LinearListTable<string, double>* table;
    TPostfixCalc calc;
public:
    Worker() {
        table = nullptr;
    }
    Worker(LinearListTable<string, double>* table) {
        this->table = table;
    }

    bool DoWork(StatementExpression& stex) {
         vector<Token> vec = stex.getStatement();
         if (vec.front().getType() == "Write") {//3 варианта: текст, переменную, текст с переменной
             (vec[3].getType() == "COMMA") ?
                 cout << vec[2].getValue() << " " << vec[4].getValue() : cout << vec[2].getValue();
         }
         if (vec.front().getValue() == "Writeln") {
             vec[3].getType() == "СOMMA" ?
                 cout << vec[2].getValue() << " " << vec[4].getValue() : cout << vec[2].getValue();
             cout << endl;
         }
         if (vec.front().getValue() == "Read") { //
             //обращение к таблице, добавить в неё значение с клавиатуры
             double value;
             cin >> value;
             table->Insert(vec[2].getValue(), value);
         }
         if (vec.front().getValue() == "Readln") {
             //обращение к таблице, добавить в неё значение с клавиатуры
             double value;
             cin >> value;
             table->Insert(vec[2].getValue(), value);
             cout << endl;
         }
         else { // (vec[pos].getType() == "VARIABLE")
             TPostfixCalc calc(stex);
             calc.Build();
             double res = calc.GetRes();
             table->Insert(vec[2].getValue(), res);
         }
         return true;
    }

    

    bool DoWork(ConditionExpression& condex) {
        auto body = condex.getBody();
        vector<Token> condition = body.first;
        vector<Expression*> expList = body.second;
        // if (12 > 5) {}
        // if (12 <= 5) {} // else
        if (condition.front().getType() == "CONDITION") { // uncondition can be created by negating of origin condition
            
        }
        if (condition.front().getType() == "UNTIL") {

        }
        if (condition.front().getType() == "CYCLEFOR") {
            int left = std::stoi(condition[3].getValue());
            int right = std::stoi(condition[5].getValue());
            if (left < right) {
                for (int i = left; left < right; left++) {
                    for (auto expEl : expList)
                        this->DoWork(expEl);
                }
            }
            else {
                for (int i = left; left > right; left--) {

                }
            }


            while(expList[posofEndofIf].getType()!="ASSIGN"){  posofEndofIf++;  }
            i1=std::stoi(list[posofEndofIf+1].getValue());
            i2=std::stoi(list[posofEndofIf+3].getValue());
            posofEndofIf=posofEndofIf+6;
            if( list[posofEndofIf+2].getType()=="INC"){//или можно сделать if(i1<i2){} else{}, не знаю что быстрее,
                //но наверно второе потому что обратиться к локальной переменной всяко быстрее
                //чем лезть по индексу в вектор и у него брать поле
                for (i1;i1<i2;i1++){ //не усралось расшифровка цикла сейчас, надо потом
                    //либо добавить i2-i1 одинаковых строчек, либо париться с циклом потом, а сейчас сделать как с if
                    int  c=posofEndofIf;
                    if((list[c].getType()=="CONDITION")||(list[c].getType()=="CYCLEFOR")||
                       (list[c].getType()=="CYCLEWHILE")||(list[c].getType()=="CYCLEDOWHILE")){
                        ConditionExpression cx(c,list);
                    expressionList.push_back(&cx);}
                    while(list[posofEndofIf].getValue()!="SEMICOLON"){
                            localList.push_back(list[posofEndofIf]);
                            posofEndofIf++;}
                        StatementExpression ex(localList);
                        expressionList.push_back(&ex);
                        localList.clear();
                        posofEndofIf++;
                }
            }
            else{
                for (i1;i1>i2;i2--){
                    if((list[posofEndofIf].getType()=="CONDITION")||
                       (list[posofEndofIf].getType()=="CYCLEFOR")||
                       (list[posofEndofIf].getType()=="CYCLEWHILE")||
                       (list[posofEndofIf].getType()=="CYCLEDOWHILE")){
                        ConditionExpression ex(posofEndofIf,list);}
                    while(list[posofEndofIf].getValue()!="SEMICOLON"){
                        localList.push_back(list[posofEndofIf]);
                        posofEndofIf++;}
                    StatementExpression ex(localList);
                    expressionList.push_back(&ex);
                    localList.clear();
                    posofEndofIf++;
                }
            }
        }
        if (body.first.front().getType() == "CYCLEWHILE") {

        }
    }

};
