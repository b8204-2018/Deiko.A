#include <stdexcept>

using namespace std;

#ifndef MYSUBJECTAREA_TANK_H
#define MYSUBJECTAREA_TANK_H

typedef double liter;

class TankIntarface{
protected:
	liter capacity;
	liter balance;
public:
	virtual liter getCapacity() = 0;
	virtual liter getBalance() = 0;
	virtual void decBalance(liter) = 0;
};

class Tank : public TankIntarface {
public:
	Tank(liter cap = 100){ balance = capacity = cap; }
	Tank(TankIntarface& tank) {
		capacity = tank.getCapacity();
		balance = tank.getBalance();
	}
	liter getCapacity() override { return capacity; }
	liter getBalance() override { return balance; }
	void decBalance(liter expence) override {
		if (expence > balance)
			throw invalid_argument("expence is bigger than balance");
		balance -= expence;
	}
};

class SmallTank : public Tank {
public:
	SmallTank() { balance = capacity = 250; }
};

class MediumTank : public Tank {
public:
	MediumTank() { balance = capacity = 500; }
};

class HugeTank : public Tank {
public:
	HugeTank() { balance = capacity = 1000; }
};

#endif //MYSUBJECTAREA_TANK_H
