// SubjArea_vs.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>

//#include "src/engine.h"
#include "src/area.h"

using namespace std;


int main()
{
	AreaReader reader;
	vector<Airport> ports = reader.read("input.txt");
	Dispatcher dis(ports);
	dis.run(0, 3);
	//B mb;
	//mb.doSmthg();
}


/*
class A {
	int t;
public:
	A(int _t = 0) {
		t = _t;
	}
void add() { t++; }
int get() { return t; }
};

class B {
	A* Atemp;
	void doth(int k, A att) {
		if (k > 3) {
			cout << endl;
			return;
		}
		att.add();
		cout << att.get();
		for (size_t j = 0; j < 2; j++) {
			doth(k + 1, att);
		}
	}
public:
	B() {
		Atemp = new  A(2);
	}
	void doSmthg() {
		for (size_t i = 0; i < 5; i++)
		{
			doth(1, *Atemp);
		}
	}
};
*/