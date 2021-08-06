/* VGP 126 Final Project Munition class header file
W. Dobson  9-16-2018
*/
#pragma once

enum MunitionType { BOMB, ROCKET, MISSILE };

class Munition
{
public:
	MunitionType mtype;
	int x, y, z;
	float vx, vy, vz;
	float mass, thrust, drag;
	int hitpower;

	Munition();
	Munition(MunitionType const mt);

	~Munition();
};

