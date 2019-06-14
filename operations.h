//
// Created by Тохандос on 12.06.2019.
//

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

#ifndef OPN_CLION_OPERATIONS_H
#define OPN_CLION_OPERATIONS_H

class OperationInterface {
protected:
    string value;
public:
    virtual int numbOfOperands() = 0;
    virtual string doOp(vector<string>) = 0;
    virtual string gerValue() = 0;
};


class Number : public OperationInterface{
public:
    Number(string _value){
        value = _value;
    }
    int numbOfOperands() override {
        return 0;
    }
    string doOp(vector<string> arg) override {
        if (arg.size() != numbOfOperands())
            throw invalid_argument("there is no zero arguments");
        return value;
    }
    string gerValue(){ return value;}
};

class TermOperation : public OperationInterface{
protected:
    int numbOfOperands() override { return 2;}
    string gerValue(){ return value;}
};

class SumOp : public TermOperation{
public:
    SumOp(string _value){
        value = _value;
    }
    string doOp(vector<string> arg) override {
        double A = stod(arg[1]);
        double B = stod(arg[0]);
        if (arg.size() != numbOfOperands())
            throw invalid_argument("there is no two arguments");
        double ans = A + B;
        ostringstream strm;
        strm << ans;
        return  strm.str();
    };
};

class DifOp : public TermOperation{
public:
    DifOp(string _value){
        value = _value;
    }
    string doOp(vector<string> arg) override {
		double A = stod(arg[1]);
		double B = stod(arg[0]);
        if (arg.size() != numbOfOperands())
            throw invalid_argument("there is no two arguments");
        double ans = A - B;
        ostringstream strm;
        strm << ans;
        return  strm.str();
    };
};

class MulOp : public TermOperation{
public:
    MulOp(string _value){
        value = _value;
    }
    string doOp(vector<string> arg) override {
		double A = stod(arg[1]);
		double B = stod(arg[0]);
        if (arg.size() != numbOfOperands())
            throw invalid_argument("there is no two arguments");
        double ans = A * B;
        ostringstream strm;
        strm << ans;
        return  strm.str();
    };
};

class DivOp : public TermOperation{
public:
    DivOp(string _value){
        value = _value;
    }
    string doOp(vector<string> arg) override {
		double A = stod(arg[1]);
		double B = stod(arg[0]);
        if (arg.size() != numbOfOperands())
            throw invalid_argument("there is no two arguments");
        double ans = A / B;
        ostringstream strm;
        strm << ans;
        return  strm.str();
    };
};

#endif //OPN_CLION_OPERATIONS_H
