/* VGP 126 Final Project Munition class functions and constructors
W. Dobson  9-16-2018

*/

#include "stdafx.h"
#include "Munition.h"

// Default constructor is a bomb
Munition::Munition()
{
	x = 0;
	y = 0;
	z = 0;
	vx = 0;
	vy = 0;
	vz = 0;
	mtype = BOMB;
	mass = 550;
	drag = 0.08;
	thrust = 0;
	hitpower = 1000;
}

// Constructor for specified munition type at declaration
Munition::Munition(MunitionType mt)
{
	x = 0;
	y = 0;
	z = 0;
	vx = 0;
	vy = 0;
	vz = 0;
	if (mt == BOMB) {
		mtype = BOMB;
		mass = 550;
		drag = 0.08;
		thrust = 0;
		hitpower = 1000;
	}
	else if (mt == ROCKET) {
		mtype = ROCKET;
		mass = 78;
		drag = 0.02;
		thrust = 1500;
		hitpower = 150;
	}
	else {
		mtype = MISSILE;
		mass = 245;
		drag = 0.05;
		thrust = 5200;
		hitpower = 560;
	}
}

Munition::~Munition()
{
}
