#include "pch.h"

#include "../../solver.h"
#include "../../converter.h"

TEST(InvalidExpr, EmptyString) {
	CheckerCollectionInterface* col = new MyCheckerCollection();
	string expr = "";
	ConverterRPN conv(col);
	ASSERT_NO_THROW(conv.getExpr(expr));
	vector<OperationInterface*> rpn = conv.getExpr(expr);
	RPNSolver sol;
	ASSERT_THROW(sol.GetSolution(rpn), invalid_argument);
}

TEST(InvalidExpr, InvalidSymbol) {
	CheckerCollectionInterface* col = new MyCheckerCollection();
	string expr = "25#13"; 
	ConverterRPN conv(col);
	ASSERT_THROW(conv.getExpr(expr), invalid_argument);
}

TEST(InvalidExpr, ExtraBrackets) {
	CheckerCollectionInterface* col = new MyCheckerCollection();
	string expr = "25+13)";
	ConverterRPN conv(col);
	ASSERT_THROW(conv.getExpr(expr), invalid_argument);
	expr = "(25+13";
	ASSERT_THROW(conv.getExpr(expr), invalid_argument);
}

TEST(Calculation, RealNumbers) {
	CheckerCollectionInterface* col = new MyCheckerCollection();
	string expr = "(2.3+2.7-4.0+9.00)/(5*0.2)";
	ConverterRPN conv(col);
	ASSERT_NO_THROW(conv.getExpr(expr));
	vector<OperationInterface*> rpn = conv.getExpr(expr);
	RPNSolver sol;
	ASSERT_NO_THROW(sol.GetSolution(rpn));
	EXPECT_EQ(sol.GetSolution(rpn), 10);
}

TEST(Calculation, NoBrackets_EqualPriorities) {
	CheckerCollectionInterface* col = new MyCheckerCollection();
	string expr = "15-10+5";
	ConverterRPN conv(col);
	ASSERT_NO_THROW(conv.getExpr(expr));
	vector<OperationInterface*> rpn = conv.getExpr(expr);
	RPNSolver sol;
	ASSERT_NO_THROW(sol.GetSolution(rpn));
	EXPECT_EQ(sol.GetSolution(rpn), 10);
}


TEST(Calculation, NoBrackets_NotEqualPriorities) {
	CheckerCollectionInterface* col = new MyCheckerCollection();
	string expr = "2+2*2";
	ConverterRPN conv(col);
	ASSERT_NO_THROW(conv.getExpr(expr));
	vector<OperationInterface*> rpn = conv.getExpr(expr);
	RPNSolver sol;
	ASSERT_NO_THROW(sol.GetSolution(rpn));
	EXPECT_EQ(sol.GetSolution(rpn), 6);

	expr = "2*2+2";
	ASSERT_NO_THROW(conv.getExpr(expr));
	rpn = conv.getExpr(expr);
	ASSERT_NO_THROW(sol.GetSolution(rpn));
	EXPECT_EQ(sol.GetSolution(rpn), 6);
}

TEST(Calculation, Brackets_EqualPriorities) {
	CheckerCollectionInterface* col = new MyCheckerCollection();
	string expr = "15-(10+5)";
	ConverterRPN conv(col);
	ASSERT_NO_THROW(conv.getExpr(expr));
	vector<OperationInterface*> rpn = conv.getExpr(expr);
	RPNSolver sol;
	ASSERT_NO_THROW(sol.GetSolution(rpn));
	EXPECT_EQ(sol.GetSolution(rpn), 0);

	expr = "(15-10)+5";
	ASSERT_NO_THROW(conv.getExpr(expr));
	rpn = conv.getExpr(expr);
	ASSERT_NO_THROW(sol.GetSolution(rpn));
	EXPECT_EQ(sol.GetSolution(rpn), 10);
}

TEST(Calculation, Brackets_NotEqualPriorities) {
	CheckerCollectionInterface* col = new MyCheckerCollection();
	string expr = "(2+2)*2";
	ConverterRPN conv(col);
	ASSERT_NO_THROW(conv.getExpr(expr));
	vector<OperationInterface*> rpn = conv.getExpr(expr);
	RPNSolver sol;
	ASSERT_NO_THROW(sol.GetSolution(rpn));
	EXPECT_EQ(sol.GetSolution(rpn), 8);

	expr = "2+(2*2)";
	ASSERT_NO_THROW(conv.getExpr(expr));
	rpn = conv.getExpr(expr);
	ASSERT_NO_THROW(sol.GetSolution(rpn));
	EXPECT_EQ(sol.GetSolution(rpn), 6);
}

TEST(Calculation, DivisionByZero) {
	CheckerCollectionInterface* col = new MyCheckerCollection();
	string expr = "(25+13)/0";
	ConverterRPN conv(col);
	ASSERT_NO_THROW(conv.getExpr(expr));
	vector<OperationInterface*> rpn = conv.getExpr(expr);
	RPNSolver sol;
	ASSERT_THROW(sol.GetSolution(rpn), invalid_argument);
}

TEST(AddNewOp, DegreeOp) {

	class DegOp : public OperationInterface {
	public:
		DegOp(string _value) {
			value = _value;
		}
		int numbOfOperands() override {
			return 2;
		};
		string doOp(vector<string> arg) override {
			double A = stod(arg[1]);
			double B = stod(arg[0]);
			if (arg.size() != numbOfOperands())
				throw invalid_argument("there is no two arguments");
			double ans;
			ans = pow(A, B);
			ostringstream strm;
			strm << ans;
			return  strm.str();
		};
		string gerValue() override {
			return value;
		};
	};

	class DegToken : public BinaryOperations {
	public:
		DegToken(string _value = "^") {
			value = _value;
		}
		int getPriority() override { return VHighPr };
		OperationInterface* getOp() override {
			return new DegOp(value);
		}
	};

	class DegChecker : public TokenCheckerInterface {
	public:
		bool check(string str) override {
			return str == "^";
		}
		TokenInterface* getToken(string str) {
			return new DegToken(str);
		}
	};

	class MyCheckerCollection_2 : public CheckerCollectionInterface {
	public:
		vector<TokenCheckerInterface*> getCheckers() override {
			vector<TokenCheckerInterface*> temp;
			temp.push_back(new NumberChecker);
			temp.push_back(new SumChecker);
			temp.push_back(new DifChecker);
			temp.push_back(new MulChecker);
			temp.push_back(new DivChecker);
			temp.push_back(new RoundOpenBrChecker);
			temp.push_back(new RoundCloseBrChecker);
			temp.push_back(new DegChecker);
			return temp;
		}
	};

	CheckerCollectionInterface* col = new MyCheckerCollection_2();
	string expr = "3+3*3^3";
	ConverterRPN conv(col);
	ASSERT_NO_THROW(conv.getExpr(expr));
	vector<OperationInterface*> rpn = conv.getExpr(expr);
	RPNSolver sol;
	ASSERT_NO_THROW(sol.GetSolution(rpn));
	EXPECT_EQ(sol.GetSolution(rpn), 84);
}