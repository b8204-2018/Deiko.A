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
		//return regex_match(str, regex("([0-9])+\\.([0-9])*")) || regex_match(str, regex("([0-9])+"));
		return regex_match(str, regex("\\d+(?:\\.\\d*)?"));
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

/*
class CheckerCollectionInterface{
public:
    virtual std::vector<TokenCheckerInterface*> getCheckers() = 0;
};
*/

class CheckerCollection{
	vector<TokenCheckerInterface*> collection;
public:
	void add(TokenCheckerInterface* token) {
		collection.push_back(token);
	}
	static CheckerCollection* getBasics() {
		CheckerCollection* temp = new CheckerCollection;
		temp->add(new NumberChecker);
		temp->add(new SumChecker);
		temp->add(new DifChecker);
		temp->add(new MulChecker);
		temp->add(new DivChecker);
		temp->add(new RoundOpenBrChecker);
		temp->add(new RoundCloseBrChecker);
		return temp;
	}
	vector<TokenCheckerInterface*> getCheckers() {
		return collection;
	}
};

class BigChecker{
    vector<TokenCheckerInterface*> checkers;
public:
	BigChecker() {}
    BigChecker(CheckerCollection* collection = CheckerCollection::getBasics()){
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
