#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

#include "plane.h"

using namespace std;

typedef vector<PlaneInterface*> Hangar;
typedef vector<vector<int>> Map;

const int INF(100000);

class Airport {
	vector<PlaneInterface*> hangar;
	vector<kilometer> links;
	friend class Dispatcher;
public:
	Airport(vector<PlaneInterface*> _hangar, vector<kilometer> _links) {
		//if (_hangar.size() != _links.size())
		//	throw invalid_argument("sizes of hangars and map isn't same");
		hangar = _hangar;
		links = _links;
	}
};

class Pylot {
	vector<int> ports;
	kilometer dist;
	size_t changes;
	int target;
	PlaneInterface* plane;
public:
	Pylot(int _target = 0) {
		target = _target;
		dist = 0;
		changes = 0;
		plane = nullptr;
	}
	Pylot(Pylot& p) {
		ports = p.ports;
		dist = p.dist;
		changes = p.changes;
		target = p.target;
		plane = p.plane;
	}
	void changePlane(PlaneInterface* newPlane) {
		plane = newPlane;
		changes++;
	}
	int getTarget() { return target; }
	kilometer getDistance() { return dist; }
	size_t getChanges() { return changes; }
	vector<int> getPoints() { return ports; }
	PlaneInterface* landPlane() {
		PlaneInterface* temp = plane;
		plane = nullptr;
		return temp;
	}
	bool canFly(kilometer distance) {
		if (plane == nullptr)
			throw logic_error("there is no plane");
		return distance <= plane->getRange();
	}
	void doFly(kilometer distance, int point) {
		if (plane == nullptr)
			throw logic_error("there is no plane");
		ports.push_back(point);
		dist += distance;
		plane->doFly(distance);
	}
};

class Dispatcher {
	vector<Airport> airports;
	vector<bool> used;
	Pylot* pylot;
public:
	Dispatcher(vector<Airport> _airports) {
		airports = _airports;
		used = vector<bool>(airports.size());
		pylot = nullptr;
	}
	void rec_run(Pylot p, int A) {
		if (p.getTarget() == A) {
			
			vector<int> ppo = p.getPoints();
			for (int i = 0; i < ppo.size(); i++)
				cout << ppo[i] << " ";
			cout << endl;
			cout << p.getDistance()  << " --- " << p.getChanges() << endl;
			
			if (pylot == nullptr || p.getDistance() < pylot->getDistance() ||
				(p.getDistance() == pylot->getDistance() && p.getChanges() < pylot->getChanges()))
				pylot = new Pylot(p);
			return;
		}
		used[A] = true;
		Pylot pyl;
		if (p.getChanges() != 0) {
			for (size_t i = 0; i < airports[A].links.size(); i++) {
				if (used[i]) continue;
				pyl = Pylot(p);
				if (!pyl.canFly(airports[A].links[i]))
					continue;
				pyl.doFly(airports[A].links[i], i);
				rec_run(pyl, i);
			}
		}
		for (size_t i = 0; i < airports[A].links.size(); i++) {
			if (used[i] || airports[A].links[i] == INF) continue;
			for (size_t j = 0; j < airports[A].hangar.size(); j++) {
				pyl = Pylot(p);
				pyl.changePlane(airports[A].hangar[j]);
				if (!pyl.canFly(airports[A].links[i]))
					continue;
				pyl.doFly(airports[A].links[i], i);
				rec_run(pyl, i);
			}
		}
		used[A] = false;
	}
	void run(int A, int B) {
		Pylot pyl;
		pyl = Pylot(B);
		rec_run(pyl, A);
		/*
		for (size_t j = 0; j < airports[A].hangar.size(); j++) {
			pyl = Pylot(B);
			pyl.changePlane(airports[A].hangar[j]);
			if (!pyl.canFly(airports[A].links[i]))
				continue;
			pyl.doFly(airports[A].links[i], A);
			rec_run(pyl, A);
		}
		*/
		/*
		for (size_t i = 0; i < airports[A].links.size(); i++){
			for (size_t j = 0; j < airports[A].hangar.size(); j++){
				pyl = Pylot(B);
				pyl.changePlane(airports[A].hangar[j]);
				if (!pyl.canFly(airports[A].links[i]))
					continue;
				pyl.doFly(airports[A].links[i], A);
				rec_run(pyl, A);
			}
		}
		*/
	}
	~Dispatcher() {
		delete pylot;
	}
};

class AreaReader {
public:
	vector<Airport> read(string input) {
		vector<Airport> res;
		ifstream fin(input);
		int N, P;
		kilometer L;
		voracity power;
		liter capacity;
		fin >> N;
		vector<PlaneInterface*> tempHangars;
		vector<kilometer> tempLinks;
		for (size_t i = 0; i < N; i++){
			tempHangars.clear();
			tempLinks.clear();
			fin >> P;
			for (size_t j = 0; j < P; j++){
				fin >> power >> capacity;
				tempHangars.push_back(new SimplePlane(power, capacity));
			}
			for (size_t j = 0; j < N; j++){
				fin >> L;
				if (L == -1) L = INF;
				tempLinks.push_back(L);
			}
			res.push_back(Airport(tempHangars, tempLinks));
		}
		return res;
	}
};


/*
class Area {
	vector<Hangar> hangars;
	Map hMap;
	friend class Dispatcher;
public:
	Area(vector<Hangar> _hangars = {}, Map _hMap = {}) {
		if (_hangars.size() != _hMap.size())
			throw invalid_argument("sizes of hangars and map isn't same");
		hangars = _hangars;
		hMap = _hMap;
	}
	~Area() {
		for (size_t i = 0; i < hangars.size(); i++) {
			for (size_t j = 0; j < hangars[i].size(); j++) {
				delete hangars[i][j];
			}
		}
	}
};
*/

/*
Map Dijkstra(size_t s) {
	if (s >= hMap.size())
		throw invalid_argument("out of size");
	vector<bool> used(hMap.size());
	vector<int> d(hMap.size());
	fill(d.begin(), d.end(), INF);
	d[s] = 0;
	for (size_t i = 0; i < d.size(); i++) {
		int v = -1;
		for (size_t j = 0; j < d.size(); j++) {
			if (!used[j] && (v == -1 || d[j] < d[v]))
				v = j;
			if (d[v] == INF)
				break;
			used[v] = true;
			for (size_t j = 0; j < d.size(); j++) {
				if (d[v] + hMap[v][j] < )
			}
		}
	}
}
*/