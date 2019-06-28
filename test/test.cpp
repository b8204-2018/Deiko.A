#include "pch.h"

#include "../../solver.h"
#include "../../converter.h"

CheckerCollection* col = CheckerCollection::getBasics();
ConverterRPN conv(col);
RPNSolver sol;
vector<OperationInterface*> rpn;
string expr;

TEST(InvalidExpr, EmptyString) {
	expr = "";
	rpn = conv.getExpr(expr);
	ASSERT_THROW(sol.GetSolution(rpn), invalid_argument);
}

TEST(InvalidExpr, InvalidSymbol) {
	expr = "25#13"; 
	ASSERT_THROW(conv.getExpr(expr), invalid_argument);
}

TEST(InvalidExpr, ExtraBrackets) {
	expr = "25+13)";
	ASSERT_THROW(conv.getExpr(expr), invalid_argument);
	expr = "(25+13";
	ASSERT_THROW(conv.getExpr(expr), invalid_argument);
}

TEST(Calculation, RealNumbers) {
	expr = "(2.3+2.7-4.0+9.00)/(5*0.2)";
	rpn = conv.getExpr(expr);
	EXPECT_EQ(sol.GetSolution(rpn), 10);
}

TEST(Calculation, NoBrackets_EqualPriorities) {
	expr = "15-10+5";
	rpn = conv.getExpr(expr);
	EXPECT_EQ(sol.GetSolution(rpn), 10);
}


TEST(Calculation, NoBrackets_NotEqualPriorities) {
	expr = "2+2*2";
	rpn = conv.getExpr(expr);
	EXPECT_EQ(sol.GetSolution(rpn), 6);

	expr = "2*2+2";
	rpn = conv.getExpr(expr);
	EXPECT_EQ(sol.GetSolution(rpn), 6);
}

TEST(Calculation, Brackets_EqualPriorities) {
	expr = "15-(10+5)";
	rpn = conv.getExpr(expr);
	EXPECT_EQ(sol.GetSolution(rpn), 0);

	expr = "(15-10)+5";
	rpn = conv.getExpr(expr);
	EXPECT_EQ(sol.GetSolution(rpn), 10);
}

TEST(Calculation, Brackets_NotEqualPriorities) {
	expr = "(2+2)*2";
	rpn = conv.getExpr(expr);
	EXPECT_EQ(sol.GetSolution(rpn), 8);

	expr = "2+(2*2)";
	rpn = conv.getExpr(expr);
	EXPECT_EQ(sol.GetSolution(rpn), 6);
}

TEST(Calculation, DivisionByZero) {
	expr = "(25+13)/0";
	rpn = conv.getExpr(expr);
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

	class DegToken : public TokenInterface {
	public:
		DegToken(string _value = "^") {
			value = _value;
			type = INFIX;
		}
		int getPriority() override { return VERY_HIGH_PRIORITY; };
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

	CheckerCollection* col_2 = CheckerCollection::getBasics();
	col_2->add(new DegChecker);
	
	expr = "3+3*3^3";
	ConverterRPN conv_2(col_2);
	rpn = conv_2.getExpr(expr);
	EXPECT_EQ(sol.GetSolution(rpn), 84);
}