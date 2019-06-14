//
// Created by Тохандос on 12.06.2019.
//
#include <iostream>
#include <vector>
#include <string>

#include "operations.h"

using namespace std;

#ifndef OPN_CLION_MYPARSER_H
#define OPN_CLION_MYPARSER_H

class RPNSolver {
    vector<OperationInterface*> RPN;
public:
    RPNSolver(vector<OperationInterface*> _RPN = {}){
        RPN = _RPN;
    }
    string GetSolution(){
        vector<string> stack;
        vector<string> args;
        for (int i = 0; i < RPN.size(); ++i) {
            for (int j = 0; j < RPN[i]->numbOfOperands(); ++j) {
                if (stack.size() == 0) throw logic_error("something went wrong; out of range");
                string temp = stack.back();
                stack.pop_back();
                args.push_back(temp);
            }
            string temp = RPN[i]->doOp(args);
            stack.push_back(temp);
            args.clear();
        }
        return stack.back();
    }
    string gerRNP(){
        string temp;
        for (int i = 0; i < RPN.size(); ++i) {
            temp += RPN[i]->gerValue();
			temp += " ";
        }
        return temp;
    }
};

#endif //OPN_CLION_MYPARSER_H
