
#include <iostream>
#include "../Expression/include/StatementExpression.h"
#include "../Token/include/Token.h"
#include "../Lexer/include/Lexer.h"
#include "../ListLinearTable/include/List.h"
#include "../Postfix/include/Postfix.h"
#include "../Parser/include/Worker.h"
using namespace std;
template <class Priority, class Value>
class HierarchyList {
private:
    struct Node {
        Worker* worker;
        Node* nextDescription;
        Value value;
        Node(Value v, Worker* worker) {
            this->nextDescription = nullptr;
            this->value = v;
            this->worker = worker;
        }
        Node(Node* d, Value v) {
            this->nextDescription = d;
            this->value = v;
            this->worker = d->worker;
        }
        void toSolve() {
            if (this == nullptr)return;
            this->worker->DoWork(value);
            this->nextDescription->toSolve();
        }
    };
    struct Chapter {
        Priority chapter;
        Chapter* nextChapter;
        Node* description;
        Chapter(Priority p) {
            chapter = p;
            nextChapter = nullptr;
            description = nullptr;
        }
        void toSolve() {
            if (this == nullptr) return;
            this->description->toSolve();
            this->nextChapter->toSolve();
        }
    };
    Chapter* root;
    LinearListTable<string, string> table;

public:
    HierarchyList() {
        root = new Chapter("Const");
        root->nextChapter = new Chapter("Var");
        (root->nextChapter)->nextChapter = new Chapter("Body");
    }
    void toAddNext(Value val, Priority pr) {
        Node* new_node = new Node(val);
        Chapter* currentChapter = this->root;
        while (currentChapter->chapter != pr) {
            currentChapter = currentChapter->nextChapter;
        }
        Node* currentNode = currentChapter->description;
        while (currentNode != nullptr) {
            currentNode = currentNode->nextDescription;
        }
        currentNode = new_node;
    }
    void toSolve() {
        root->toSolve();
    }
};
