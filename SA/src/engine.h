//
// Created by Тохандос on 13.06.2019.
//

#ifndef MYSUBJECTAREA_ENGINE_H
#define MYSUBJECTAREA_ENGINE_H

typedef double voracity; //how many liters need for a one kilometer;
typedef int speed;

class EngineInterface {
public:
	virtual voracity getPower() = 0;
};

class Engine : public EngineInterface {
protected:
	voracity power;
public:
	Engine(voracity p = 0) { power = p; }
	Engine(EngineInterface& engine) {
		power = engine.getPower();
	}
	voracity getPower() override { return power; };
};

class SlowEngine : public Engine{
public:
	SlowEngine() { power = 5; }
};

class MidEngine : public Engine{
public:
	MidEngine() { power = 10; }
};

class TurboEngine : public Engine{
public:
	TurboEngine() { power = 50; }
};

#endif //MYSUBJECTAREA_ENGINE_H
