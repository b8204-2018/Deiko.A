//
// Created by Тохандос on 13.06.2019.
//

#include <string>
#include <regex>

#include "token.h"

using namespace std;

#ifndef OPN_CLION_TOKEN_H
#define OPN_CLION_TOKEN_H

class TokenCheckerInterface{
public:
    virtual bool check(string) = 0;
    virtual TokenInterface* getToken(string) = 0;
};

class NumberChecker : public TokenCheckerInterface {
public:
    bool check(string str) override {
		return regex_match(str, regex("([0-9])+\.([0-9])+"));
    }
    TokenInterface* getToken(string str){
        return new NumberToken(str);
    }
};

class SumChecker : public TokenCheckerInterface{
public:
    bool check(string str){
        return str == "+";
    }
    TokenInterface* getToken(string str){
        return new SumToken(str);
    }
};

class DifChecker : public TokenCheckerInterface{
public:
    bool check(string str) override {
        return str == "-";
    }
    TokenInterface* getToken(string str){
        return new DifToken(str);
    }
};

class MulChecker : public TokenCheckerInterface{
public:
    bool check(string str) override {
        return str == "*";
    }
    TokenInterface* getToken(string str){
        return new MulToken(str);
    }
};

class DivChecker : public TokenCheckerInterface{
public:
    bool check(string str) override {
        return str == "/";
    }
    TokenInterface* getToken(string str){
        return new DivToken(str);
    }
};

class RoundOpenBrChecker : public TokenCheckerInterface{
public:
    bool check(string str) override {
        return str == "(";
    };
    TokenInterface* getToken(string str){
        return new RoundOpenBrToken(str);
    }
};

class RoundCloseBrChecker : public TokenCheckerInterface{
public:
    bool check(string str) override {
        return str == ")";
    };
    TokenInterface* getToken(string str){
        return new RoundCloseBrToken(str);
    }
};

class CheckerCollectionInterface{
public:
    virtual std::vector<TokenCheckerInterface*> getCheckers() = 0;
};

class MyCheckerCollection : public CheckerCollectionInterface{
public:
    vector<TokenCheckerInterface*> getCheckers() override {
        vector<TokenCheckerInterface*> temp;
        temp.push_back(new NumberChecker);
        temp.push_back(new SumChecker);
        temp.push_back(new DifChecker);
        temp.push_back(new MulChecker);
        temp.push_back(new DivChecker);
        temp.push_back(new RoundOpenBrChecker);
        temp.push_back(new RoundCloseBrChecker);
        return temp;
    }
};


class BigChecker{
    vector<TokenCheckerInterface*> checkers;
public:
	BigChecker() {}
    BigChecker(CheckerCollectionInterface* collection){
        checkers = collection->getCheckers();
    }
    ~BigChecker(){
        for (int i = 0; i < checkers.size(); ++i) {
            delete checkers[i];
        }
    }
    bool isToken(string str){
        for (int i = 0; i < checkers.size(); ++i) {
            if(checkers[i]->check(str)) return true;
        }
        return false;
    }
    TokenCheckerInterface* getChecker(string str){
        for (int i = 0; i < checkers.size(); ++i) {
            if(checkers[i]->check(str)) return checkers[i];
        }
        return nullptr;
    }

};


#endif //OPN_CLION_TOKEN_H
