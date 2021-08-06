/* VGP 126 Final Project Jet class header file
W. Dobson  9-16-2018
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Munition.h"
#define MAXBOMB 4  // payload limits for jet
#define MAXROC 8
#define MAXMIS 4
#define T_RANGE 500   // set a threat range threshold

using namespace std;

class Jet
{
public:
	string callsign;
	int x, y, z;
	float vx, vy, vz;
	float mass, thrust, drag;

	// vectors to store each type of munition as payload
	vector<Munition> bombs, rockets, missiles;

	// vector to store realeased weapons that will be updated
	vector<Munition> released;

	// constructors
	Jet();

	Jet(int x1, int y1, int z1, float vx1, float vy1, float vz1,
		float m, float d, float t, const string cs);

	~Jet();

	// functions
	void load(MunitionType mt, int qty);

	void fire(MunitionType mt, int qty);

	void update();

	int inrange(Jet *enemyjet, float weaponrange);

	void dispstatus();

	void dispreleased();
};

