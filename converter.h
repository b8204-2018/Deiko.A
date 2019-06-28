//
// Created by Тохандос on 12.06.2019.
//

#include <iostream>
#include <string>
#include <vector>

#include "tokenchecker.h"

using namespace std;

#ifndef OPN_CLION_MYCONVERTER_H
#define OPN_CLION_MYCONVERTER_H

class ConverterInterface {
public:
    virtual vector<OperationInterface*> getExpr(string) = 0;
};

class ConverterRPN : public ConverterInterface {
    BigChecker* RPNChecker;
    vector<TokenInterface*> splitThis(string);
    vector<OperationInterface*> convertToRPN(vector<TokenInterface*>);
    string deleteSpaces(string);
public:
	ConverterRPN(CheckerCollection* checkers = CheckerCollection::getBasics()) {
        RPNChecker = new BigChecker(checkers);
    };
    vector<OperationInterface*> getExpr(string input) override {
		vector<TokenInterface*> exp;
		vector<OperationInterface*> RPN;
		exp = splitThis(input);
		RPN = convertToRPN(exp);
        return RPN;
    }
};

string ConverterRPN::deleteSpaces(string str) {
    int index = 0;
    string temp = str;
    while (index < temp.size()){
        if (temp[index] == ' ') temp.erase(index, 1);
        else index++;
    }
    return temp;
}

vector<TokenInterface*> ConverterRPN::splitThis(string str) {
    str = deleteSpaces(str);
    vector<TokenInterface*> temp;
    int i = 0;
    while (i < str.size()){
        int j = i;
        string tmpToken = str.substr(i, j - i + 1);
        while (!RPNChecker->isToken(tmpToken)){
            j++;
            if (j == str.size())
                throw invalid_argument("incorrect string");
            tmpToken = str.substr(i, j - i + 1);
        }
        int cur_j = j;
        while (RPNChecker->isToken(tmpToken) && j < str.size()){
            j++;
            tmpToken = str.substr(i, j - i + 1);
        }
        if (cur_j != j){
            j--;
            tmpToken = str.substr(i, j - i + 1);
        }
        TokenCheckerInterface* cur_checker = RPNChecker->getChecker(tmpToken);
        temp.push_back(cur_checker->getToken(tmpToken));
        i = j+1;
    }
    return temp;
}

vector<OperationInterface*> ConverterRPN::convertToRPN(vector<TokenInterface*> expr){
    vector<TokenInterface*> stack;
    vector<OperationInterface*> out;
    for (int i = 0; i < expr.size(); ++i) {
        if(expr[i]->isNumber() || expr[i]->isPostfix()){
            out.push_back(expr[i]->getOp());
        }
        else if (expr[i]->isPrefix() || expr[i]->isOpenBr()){
            stack.push_back(expr[i]);
        }
        else if (expr[i]->isVirgule()){
            //int brecetPriority = expr[i]->getPriority();
            while (stack.size() >= 0){
                if (stack.size() == 0)
                    throw invalid_argument("incorrect string, OpenBrecet is missied");
                TokenInterface* temp = stack.back();
                stack.pop_back();
                if (temp->isOpenBr()) {
                    stack.push_back(temp);
                    break;
                }
                OperationInterface* otemp = temp->getOp();
                delete temp;
                out.push_back(otemp);
            }
        }
        else if (expr[i]->isCloseBr()){
            int brecetPriority = expr[i]->getPriority();
            while (stack.size() >= 0){
                if (stack.size() == 0)
                    throw invalid_argument("incorrect string, OpenBrecet is missied");
                TokenInterface* temp = stack.back();
                stack.pop_back();
                if (temp->isOpenBr() && temp->getPriority() == brecetPriority){
                    delete temp;
                    break;
                }
                out.push_back(temp->getOp());
                delete temp;
            }
        }
        else if (expr[i]->isInfix()){
            int operPriority = expr[i]->getPriority();
            while (stack.size() > 0 && (stack.back()->getPriority() >= operPriority || stack.back()->isPrefix())){
                TokenInterface* temp = stack.back();
                stack.pop_back();
                out.push_back(temp->getOp());
                delete temp;
            }
            stack.push_back(expr[i]);
        }
    }
    while (stack.size() > 0){
        TokenInterface* temp = stack.back();
        stack.pop_back();
        OperationInterface* otemp = temp->getOp();
        if (otemp != nullptr){
            out.push_back(otemp);
        } else{
            throw invalid_argument("incorrect string: brackets are not matched in expression");
        }
        delete temp;
    }
    return out;
}

#endif //OPN_CLION_MYCONVERTER_H
