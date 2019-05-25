// math.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <functional>
#include <fstream>

using namespace std;

class ParserInterface {
public:
	virtual vector<int> parse(string) = 0;
};

class EquationParser : public ParserInterface {
	bool isX(char c) { return c == 'x'; }
	bool isEqual(char c) { return c == '='; }
	bool isNumb(char c) { return isdigit(c); }
public:
	vector<int> parse(string str) {
		vector<int> temp;
		string numb;
		int j = 0;
		while (j < str.size()) {
			int i = j;
			while (!isX(str[i]) && !isEqual(str[i])) {
				numb.push_back(str[i]);
				i++;
			}
			if (numb.empty() || (numb.size() == 1) && !isdigit(numb[0])) {
				numb.push_back('1');
			}
			temp.push_back(stoi(numb));
			numb.clear();
			if (isNumb(str[i + 1])) i++;
			j = i + 1;
		}
		return temp;
	}
};

class TermParser : public ParserInterface {
public:
	vector<int> parse(string str) {
		vector<int> temp;
		string numb;
		for (int i = 0; i < str.size(); i++) {
			if (!isdigit(str[i]) && !numb.empty()) {
				temp.push_back(stoi(numb));
				numb.clear();
			}
			else {
				numb.push_back(str[i]);
			}
		}
		temp.push_back(stoi(numb));
		return temp;
	}
};

class SolverInterface {
public:
	virtual double solve(vector<int>) = 0;
};

class QuadraticEquationSolver : public SolverInterface {
public:
	double solve(vector<int> arg) {
		double ans = sqrt(arg[1] * arg[1] - 4 * arg[0] * arg[2]);
		ans = (-1 * arg[1] + ans) / 2 * arg[0];
		return ans;
	};
};

class SumSolver : public SolverInterface {
public:
	double solve(vector<int> arg) {
		return arg[0] + arg[1];
	};
};

class DifSolver : public SolverInterface {
public:
	double solve(vector<int> arg) {
		return arg[0] - arg[1];
	};
};

class MulSolver : public SolverInterface {
public:
	double solve(vector<int> arg) {
		return arg[0] * arg[1];
	};
};

class DivSolver : public SolverInterface {
public:
	double solve(vector<int> arg) {
		return arg[0] / arg[1];
	};
};

class SolverBuilderInterface {
public:
	virtual vector<SolverInterface*> createSolvers() = 0;
	virtual vector<ParserInterface*> createParsers() = 0;
};

class MyBuilder : public SolverBuilderInterface {
public:
	vector<SolverInterface*> createSolvers() {
		vector<SolverInterface*> temp;
		temp.push_back(new QuadraticEquationSolver);
		temp.push_back(new SumSolver);
		temp.push_back(new DifSolver);
		temp.push_back(new MulSolver);
		temp.push_back(new DivSolver);
		return temp;
	};
	vector<ParserInterface*> createParsers() {
		vector<ParserInterface*> temp;
		temp.push_back(new EquationParser);
		temp.push_back(new TermParser);
		temp.push_back(new TermParser);
		temp.push_back(new TermParser);
		temp.push_back(new TermParser);
		return temp;
	}
};

class TaskSolver {
	SolverBuilderInterface* builder;
	vector<SolverInterface*> solvers;
	vector<ParserInterface*> parsers;
public:
	TaskSolver() {};
	TaskSolver(SolverBuilderInterface* _builder) {
		builder = _builder;
		solvers = builder->createSolvers();
		parsers = builder->createParsers();
	};
	~TaskSolver() {
		for (int i = 0; i < solvers.size(); i++) {
			delete solvers[i];
		}
		for (int i = 0; i < parsers.size(); i++) {
			delete parsers[i];
		}
	}
	double getAnswerByType(int type, string str) {
		if (type >= solvers.size()) {
			//exeption
			return 0;
		}
		vector<int> arg = parsers[type]->parse(str);
		double answer = solvers[type]->solve(arg);
		return answer;
	};
};

class Reader {
	string input;
	int type;
	string example;
public:
	Reader() {};
	Reader(string fileName) {
		setFile(fileName);
	}
	void setFile(string fileName) {
		input = fileName;
	}
	void read() {
		ifstream fin(input);
		fin >> type;
		fin >> example;
		fin.close();
	}
	int getType() {
		return type;
	}
	string getString() {
		return example;
	}
};

class Writer {
	string output;
	double solution;
public:
	Writer() {};
	Writer(string fileName) {
		setFile(fileName);
	}
	void setFile(string fileName) {
		output = fileName;
	}
	void setSolution(double _solution) {
		solution = _solution;
	}
	void write() {
		ofstream fout(output);
		fout << solution;
		fout.close();
	}
};

int main()
{
	Reader reader("input.txt");
	reader.read();

	SolverBuilderInterface* mybuilder = new MyBuilder;
	TaskSolver mysolver(mybuilder);

	double ans = mysolver.getAnswerByType(reader.getType(), reader.getString());

	Writer writer("output.txt");
	writer.setSolution(ans);
	writer.write();
	return 0;
}
