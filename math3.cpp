// math.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include <cassert>

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
	virtual vector<double> solve(vector<int>) = 0;
};

class QuadraticEquationSolver : public SolverInterface {
public:
	vector<double> solve(vector<int> arg) {
		assert(arg.size() == 3);
		vector<double> ans;
		double dis = arg[1] * arg[1] - 4 * arg[0] * arg[2];
		if(dis > 0){
			ans.push_back((-1 * arg[1] + sqrt(dis)) / 2 * arg[0]);
			ans.push_back((-1 * arg[1] - sqrt(dis)) / 2 * arg[0]);
		}
		else if (dis == 0) {
			ans.push_back((-1 * arg[1]) / 2 * arg[0]);
		}
		return ans;
	};
};

class SumSolver : public SolverInterface {
public:
	vector<double> solve(vector<int> arg) {
		assert(arg.size() == 2);
		vector<double> ans;
		ans.push_back(arg[0] + arg[1]);
		return ans;
	};
};

class DifSolver : public SolverInterface {
public:
	vector<double> solve(vector<int> arg) {
		assert(arg.size() == 2);
		vector<double> ans;
		ans.push_back(arg[0] - arg[1]);
		return ans;
	};
};

class MulSolver : public SolverInterface {
public:
	vector<double> solve(vector<int> arg) {
		assert(arg.size() == 2);
		vector<double> ans;
		ans.push_back(arg[0] * arg[1]);
		return ans;
	};
};

class DivSolver : public SolverInterface {
public:
	vector<double> solve(vector<int> arg) {
		assert(arg.size() == 2);
		vector<double> ans;
		ans.push_back(arg[0] / arg[1]);
		return ans;
	};
};

class UnitInterface {
public:
	virtual ParserInterface* createParser() = 0;
	virtual SolverInterface* createSolver() = 0;
};

class QEUnit : public UnitInterface {
public:
	ParserInterface* createParser() {
		return new EquationParser;
	};
	SolverInterface* createSolver() {
		return new QuadraticEquationSolver;
	};
};

class SumUnit : public UnitInterface {
public:
	ParserInterface* createParser() {
		return new TermParser;
	};
	SolverInterface* createSolver() {
		return new SumSolver;
	};
};

class DifUnit : public SumUnit {
public:
	SolverInterface* createSolver() {
		return new DifSolver;
	};
};

class MulUnit : public SumUnit {
public:
	SolverInterface* createSolver() {
		return new MulSolver;
	};
};

class DivUnit : public SumUnit {
public:
	SolverInterface* createSolver() {
		return new DivSolver;
	};
};

class UnitFactoryInterface {
public:
	virtual vector<UnitInterface*> createUnits() = 0;
};

class MyUFactory : public UnitFactoryInterface {
public:
	vector<UnitInterface*> createUnits() {
		vector<UnitInterface*> temp;
		temp.push_back(new QEUnit);
		temp.push_back(new SumUnit);
		temp.push_back(new DifUnit);
		temp.push_back(new MulUnit);
		temp.push_back(new DivUnit);
		return temp;
	}
};

class TaskSolver {
	vector<UnitInterface*> units;
public:
	TaskSolver() {};
	TaskSolver(UnitFactoryInterface* unit) {
		units = unit->createUnits();
	};
	~TaskSolver() {
		for (int i = 0; i < units.size(); i++) {
			delete units[i];
		}
	}
	vector<double> getAnswerByType(size_t type, string str) {
		assert(type < units.size());
		ParserInterface* parser = units[type]->createParser();
		vector<int> arg = parser->parse(str);
		delete parser;

		SolverInterface* solver = units[type]->createSolver();
		vector<double> answer = solver->solve(arg);
		delete solver;

		return answer;
	};
};

class ExampleReader {
public:
	pair<int, string> read(string input) {
		int type;
		string example;
		ifstream fin(input);
		fin >> type;
		fin >> example;
		fin.close();
		return make_pair(type, example);
	}
};

class AnswerWriter {
public:
	void write(string output, vector<double> solution) {
		ofstream fout(output);
		for(size_t i = 0; i < solution.size(); i++)
			fout << solution[i] << " ";
		fout.close();
	}
};

int main()
{
	ExampleReader reader;
	pair<int, string> ex = reader.read("input.txt");

	UnitFactoryInterface* MyFact = new MyUFactory;
	TaskSolver mysolver(MyFact);

	vector<double> ans = mysolver.getAnswerByType(ex.first, ex.second);

	AnswerWriter writer;
	writer.write("output.txt", ans);
	return 0;
}
