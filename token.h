//
// Created by Тохандос on 13.06.2019.
//
#include <string>
#include <vector>

#include "operations.h"

using namespace std;

#ifndef OPN_CLION_CHECKER_H
#define OPN_CLION_CHECKER_H

#define VLowPr 1;
#define LowPr 10;
#define MidPr 20;
#define HighPr 30;
#define VHighPr 40;


class TokenInterface{
protected:
    string value;
public:
    virtual int getPriority() = 0;
    virtual bool isNumber() = 0;
    virtual bool isPrefix() = 0;
    virtual bool isInfix() = 0;
    virtual bool isPostfix() = 0;
    virtual bool isOpenBr() = 0;
    virtual bool isCloseBr() = 0;
    virtual bool isVirgule() = 0;
    virtual OperationInterface* getOp() = 0;
};

class Numbers : public TokenInterface{
public:
    bool isNumber() override { return true;};
    bool isPrefix() override { return false;};
    bool isInfix() override { return false;};
    bool isPostfix() override { return false;};
    bool isOpenBr() override { return false;};
    bool isCloseBr() override { return false;};
    bool isVirgule() override { return false;};
};

class NumberToken : public Numbers{
public:
    NumberToken(string _value = ""){
        value = _value;
    }
    int getPriority() override { return LowPr};
    OperationInterface* getOp() override {
        return new Number(value);
    }
};

class BinaryOperations : public TokenInterface{
public:
    bool isNumber() override { return false;};
    bool isPrefix() override { return false;};
    bool isInfix() override { return true;};
    bool isPostfix() override { return false;};
    bool isOpenBr() override { return false;};
    bool isCloseBr() override { return false;};
    bool isVirgule() override { return false;};
};

class SumToken : public BinaryOperations{
public:
    SumToken(string _value = "+"){
        value = _value;
    }
    int getPriority() override { return MidPr};
    OperationInterface* getOp() override {
        return new SumOp(value);
    }
};

class DifToken : public BinaryOperations{
public:
    DifToken(string _value = "-"){
        value = _value;
    }
    int getPriority() override { return MidPr};
    OperationInterface* getOp() override {
        return new DifOp(value);
    }
};

class MulToken : public BinaryOperations{
public:
    MulToken(string _value = "*"){
        value = _value;
    }
    int getPriority() override { return HighPr};
    OperationInterface* getOp() override {
        return new MulOp(value);
    }
};

class DivToken : public BinaryOperations{
public:
    DivToken(string _value = "/"){
        value = _value;
    }
    int getPriority() override { return HighPr};
    OperationInterface* getOp() override {
        return new DivOp(value);
    }
};

class Brackets : public TokenInterface{
public:
    bool isNumber() override { return false;};
    bool isPrefix() override { return false;};
    bool isInfix() override { return true;};
    bool isPostfix() override { return false;}
    bool isVirgule() override { return false;};
};

class RoundBrackets : public Brackets{
public:
    int getPriority() override { return VLowPr};
};

class RoundOpenBrToken : public RoundBrackets{
public:
    RoundOpenBrToken(string _value = "("){
        value = _value;
    }
    bool isOpenBr() override { return true;};
    bool isCloseBr() override { return false;};
    OperationInterface* getOp() override {
        return nullptr;
    }
};

class RoundCloseBrToken : public RoundBrackets{
public:
    RoundCloseBrToken(string _value = ")"){
        value = _value;
    }
    bool isOpenBr() override { return false;};
    bool isCloseBr() override { return true;};
    int getPriority() override { return VLowPr};
    OperationInterface* getOp() override {
        return nullptr;
    }
};

class PostfixFunc : public TokenInterface {
public:
	bool isNumber() override { return false; };
	bool isPrefix() override { return false; };
	bool isInfix() override { return false; };
	bool isPostfix() override { return true; };
	bool isOpenBr() override { return false; };
	bool isCloseBr() override { return false; };
	bool isVirgule() override { return false; };
};

#endif //OPN_CLION_CHECKER_H
