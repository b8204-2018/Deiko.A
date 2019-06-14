#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

#include "converter.h"
#include "solver.h"

using  namespace std;

int main() {
	CheckerCollectionInterface* col = new MyCheckerCollection();
	//string expression = "(2+3-4+9)/(5*2)";
	string expression = "0.5 + 1.5";
	ConverterRPN myconverter(col, expression);
	vector<OperationInterface*> rpn = myconverter.getExpr();
	RPNSolver sol(rpn);
	cout << sol.gerRNP() << endl;
	cout << sol.GetSolution() << endl;
	return 0;
}
