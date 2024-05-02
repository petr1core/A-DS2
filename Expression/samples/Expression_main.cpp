#include <iostream>
#include <regex>
#include<string>
#include "../Lexer/include/Lexer.h"
#include "../Parser/include/Parser.h"
using namespace std;

void forTestRegex(const string& str);
class A {
public:
    virtual void print() = 0;
};
class B :public A {
    vector<Token>v;
public:
    void add(Token t) { v.push_back(t); }
    void print() override {
        for (auto token : v) {
            std::cout << token.getValue() << " ";
        }
        std::cout << endl;
    }
};
class C {
public:
    vector<A*> vec;
    void print() {
        for (auto item : vec) {
            item->print();
        }
    }
};
std::vector<std::string> tokenizeString(const std::string& input) {
    std::vector<std::string> tokens;
    std::regex rgx("\\s+"); // Регулярное выражение для разделения по пробелам
    std::sregex_token_iterator iter(input.begin(), input.end(), rgx, -1);
    std::sregex_token_iterator end;

    while (iter != end) {
        tokens.push_back(*iter);
        ++iter;
    }

    return tokens;
}

int main() {
    std::string input = "Hello World, this is a test";
    std::vector<std::string> tokens = tokenizeString(input);

    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}

void forTestRegex(const string& str) {
    const std::string& s = str;
    std::regex rgx("^[ \n\t]");
    std::smatch match;
    if (std::regex_search(s.begin(), s.end(), match, rgx)) {
        string str2 = static_cast<string>(match[0]);
        // cout << str2.length()<<endl;
    }
}
