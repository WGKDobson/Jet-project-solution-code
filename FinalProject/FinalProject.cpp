// FinalProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Jet.h"

using namespace std;


int main()
{
	Jet j1;
	Jet j2(2700, 7600, 300, -120, -80, 0, 18000, 0.48, 50000, "Jester");

	j1.z = 400;  // reposition j1 for test
	j1.thrust = 20000;

	j1.dispstatus();
	j1.load(BOMB, 4);
	j1.load(ROCKET, 6);
	j1.load(MISSILE, 2);
	

	j2.dispstatus();
	j2.load(BOMB, 3);
	j2.load(ROCKET, 4);
	j2.load(MISSILE, 4);

	cout << "-------- Loaded jets --------" << endl;
	j1.dispstatus();
	j2.dispstatus();

	cout << "--------- Test level flight updates ------------" << endl;
	for (int i = 0; i < 10; i++) {
		j1.update();
		j1.dispstatus();
		j2.update();
		j2.dispstatus();
		if(j1.inrange(&j2, 500)) cout << "### THREAT" << j1.inrange(&j2, 1800) << endl;
	}

	cout << endl << "Launch munitions" << endl;
	j1.fire(BOMB, 1);
	j1.dispstatus();

	j2.fire(MISSILE, 1);
	j2.dispstatus();

	j1.inrange(&j2, 1000);

	cout << endl;
	cout << j1.callsign << "-------- test weapons update and inrange --------" << endl;
	for (int i = 0; i < 10; i++) {
		j1.update();
		j1.dispreleased();
		if (j1.inrange(&j2, T_RANGE)) {
			cout << "**Threat detected: " << j2.callsign << " is at range: "
				<< j1.inrange(&j2, T_RANGE) << endl;
		}
	}
	cout << endl;
	cout << j2.callsign << "-------- test weapons update and inrange --------" << endl;
	for (int i = 0; i < 10; i++) {
		j2.update();
		j2.dispreleased();
		if (j2.inrange(&j1, T_RANGE)) {
			cout << "**Threat detected: " << j1.callsign << " is at range: "
				<< j2.inrange(&j1, T_RANGE) << endl;
		}

	}

	cout << " -------------- Multiple munitions dropped ----------------" << endl;
	j1.z = 300;  // increase starting alt
	j1.vz = 0; // re zero vertical speed
	for (int i = 0; i < 5; i++) {
		j1.update();
		j1.dispstatus();
	}
	for (int i = 0; i < 20; i++) {
		j1.update();
		if ((i % 3 == 0) && (j1.bombs.size())){
			cout << "*** Fire ***" << endl;
			j1.fire(BOMB, 1);
		}
		j1.dispreleased();
	}



}

