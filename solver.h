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
public:
    RPNSolver(){
    }
    double GetSolution(vector<OperationInterface*> RPN){
		if (RPN.size() == 0)
			throw invalid_argument("empty rpn");
        vector<string> stack;
        vector<string> args;
        for (int i = 0; i < RPN.size(); ++i) {
            for (int j = 0; j < RPN[i]->numbOfOperands(); ++j) {
                if (stack.size() == 0) throw invalid_argument("stack out of range");
                string temp = stack.back();
                stack.pop_back();
                args.push_back(temp);
            }
            string temp = RPN[i]->doOp(args);
            stack.push_back(temp);
            args.clear();
        }
		double ans = stod(stack.back());
        return ans;
    }
    string gerRNP(vector<OperationInterface*> RPN){
        string temp = "";
        for (int i = 0; i < RPN.size(); ++i) {
            temp += RPN[i]->gerValue();
			temp += " ";
        }
        return temp;
    }
};

#endif //OPN_CLION_MYPARSER_H
