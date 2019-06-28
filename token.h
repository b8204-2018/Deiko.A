//
// Created by Тохандос on 13.06.2019.
//
#include <string>
#include <vector>

#include "operations.h"

using namespace std;

#ifndef OPN_CLION_CHECKER_H
#define OPN_CLION_CHECKER_H

#define VERY_LOW_PRIORITY 1;
#define LOW_PRIORITY 10;
#define MIDDLE_PRIORITY 20;
#define HIGH_PRIORITY 30;
#define VERY_HIGH_PRIORITY 40;


class TokenInterface {
protected:
	enum TokenType { NUMBER = 1, PREFIX, INFIX, POSTFIX, OPEN_BRACKET, CLOSE_BRACKET, VIRGULE };
	TokenType type;
	string value;
public:
	virtual int getPriority() = 0;
	virtual OperationInterface* getOp() = 0;
	bool isNumber() { return type == NUMBER; };
	bool isPrefix() { return type == PREFIX; };
	bool isInfix() { return type == INFIX; };
	bool isPostfix() { return type == POSTFIX; };
	bool isOpenBr() { return type == OPEN_BRACKET; };
	bool isCloseBr() { return type == CLOSE_BRACKET; };
	bool isVirgule() { return type == VIRGULE; };
};

class NumberToken : public TokenInterface{
public:
    NumberToken(string _value = "0"){
        value = _value;
		type = NUMBER;
    }
    int getPriority() override { return LOW_PRIORITY};
    OperationInterface* getOp() override {
        return new Number(value);
    }
};

class SumToken : public TokenInterface{
public:
    SumToken(string _value = "+"){
        value = _value;
		type = INFIX;
    }
    int getPriority() override { return MIDDLE_PRIORITY};
    OperationInterface* getOp() override {
        return new SumOp(value);
    }
};

class DifToken : public TokenInterface{
public:
    DifToken(string _value = "-"){
        value = _value;
		type = INFIX;
    }
    int getPriority() override { return MIDDLE_PRIORITY};
    OperationInterface* getOp() override {
        return new DifOp(value);
    }
};

class MulToken : public TokenInterface{
public:
    MulToken(string _value = "*"){
        value = _value;
		type = INFIX;
    }
    int getPriority() override { return HIGH_PRIORITY};
    OperationInterface* getOp() override {
        return new MulOp(value);
    }
};

class DivToken : public TokenInterface{
public:
    DivToken(string _value = "/"){
        value = _value;
		type = INFIX;
    }
    int getPriority() override { return HIGH_PRIORITY};
    OperationInterface* getOp() override {
        return new DivOp(value);
    }
};

class RoundBrackets : public TokenInterface{
public:
    int getPriority() override { return VERY_LOW_PRIORITY};
};

class RoundOpenBrToken : public RoundBrackets{
public:
    RoundOpenBrToken(string _value = "("){
        value = _value;
		type = OPEN_BRACKET;
    }
    OperationInterface* getOp() override {
        return nullptr;
    }
};

class RoundCloseBrToken : public RoundBrackets{
public:
    RoundCloseBrToken(string _value = ")"){
        value = _value;
		type = CLOSE_BRACKET;
    }
    int getPriority() override { return VERY_LOW_PRIORITY};
    OperationInterface* getOp() override {
        return nullptr;
    }
};

#endif //OPN_CLION_CHECKER_H
