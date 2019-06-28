#include "engine.h"
#include "tank.h"

#include <stdexcept>
#include <vector>

using namespace std;

#ifndef MYSUBJECTAREA_PLANE_H
#define MYSUBJECTAREA_PLANE_H

typedef double kilometer;

class PlaneInterface {
public:
	virtual liter getBalance() = 0;
	virtual kilometer getRange() = 0;
	virtual void doFly(kilometer) = 0;
};

class SimplePlane : public PlaneInterface{
	EngineInterface* engine;
	TankIntarface* tank;
public:
	SimplePlane(voracity power, liter capacity) {
		engine = new Engine(power);
		tank = new Tank(capacity);
	}
	SimplePlane(EngineInterface* _engine = new SlowEngine, TankIntarface* _tank = new SmallTank){
		engine = _engine;
		tank = _tank;
	}
	SimplePlane(SimplePlane& plane) {
		engine = new Engine(*plane.engine);
		tank = new Tank(*plane.tank);
	}
	~SimplePlane() {
		delete engine;
		delete tank;
	}
	liter getBalance() override { return tank->getBalance(); }
	void doFly(kilometer distance) override {
		kilometer range = getRange();
		if (distance > range)
			throw invalid_argument("out of range");
		tank->decBalance(distance * engine->getPower());
	}
	kilometer getRange() override { 
		return tank->getBalance() / engine->getPower();
	}
};

#endif //MYSUBJECTAREA_PLANE_H