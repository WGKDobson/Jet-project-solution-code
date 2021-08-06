/* VGP 126 Final Project Jet class functions and constructors
	W. Dobson  9-16-2018
	
*/

#include "stdafx.h"
#include "Jet.h"

// Default constructor
Jet::Jet() : x(1500), y(6800), z(9800), vx(120), vy(80), vz(0),
mass(14000), drag(0.28), thrust(100000)
{
	callsign = "Maverick";  // default handle
}

// Constructor to let users specify all starting parameters
Jet::Jet(int x1, int y1, int z1, float vx1, float vy1, float vz1,
	float m, float d, float t, const string cs) {
	x = x1;
	y = y1;
	z = z1;
	vx = vx1;
	vy = vy1;
	vz = vz1;
	mass = 14000;
	drag = 0.48;
	thrust = 100000;
	callsign = cs;
}

Jet::~Jet()
{
}

// Function to load munitions on the jet that uses the limits 
// defined in Jet.h to limit payload. Also increases jet mass and drag with each weapon added.
void Jet::load(MunitionType mt, int qty) {
	for (int i = 0; i < qty; i++) {
		if (mt == BOMB) {
			Munition *m = new Munition(BOMB);  // create a new munition object
			if (bombs.size() < MAXBOMB) {  // limit to max of 4 bombs
				bombs.push_back(*m); // add bomb to payload
				mass += m->mass;     // increase jet mass
				drag += m->drag;     // increase jet drag
			}
			delete m;                // clean up 
		}
		else if (mt == ROCKET) {
			Munition *m = new Munition(ROCKET);  // create a new munition object
			if (rockets.size() < MAXROC) {  // limit to max of 8 rockets
				rockets.push_back(*m); // add rocket to payload
				mass += m->mass;     // increase jet mass
				drag += m->drag;     // increase jet drag
			}
			delete m;                // clean up 
		}
		else {
			Munition *m = new Munition(MISSILE);  // create a new munition object
			if (missiles.size() < MAXMIS) {  // limit to max of 4 missiles
				missiles.push_back(*m); // add missile to payload
				mass += m->mass;     // increase jet mass
				drag += m->drag;     // increase jet drag
			}
			delete m;                // clean up 
		}		
	}
}

// Function to fire weapons. Uses an iterator as pointer to items in vectors 
// of munition objects to move them into the released vector.  Copies jet 
// loc and vel parameters for each released weapon 
void Jet::fire(MunitionType mt, int qty) {
	vector<Munition>::iterator it; // iterator needed to move objects
	
	for (int i = 0; i < qty; i++) {  // must use qty - 1 to stop loading
		if (mt == BOMB) {		
			if (bombs.size() >0) {  // if weapon available
				it = bombs.begin();
				it->x = x;  // set weapons loc and vel to jets parms
				it->y = y;
				it->z = z;
				it->vx = vx;
				it->vy = vy;
				it->vz = vz;
				released.push_back(*it); // copy weapon to released vector
				mass -= it->mass;     // decrease jet mass
				drag -= it->drag;     // decrease jet drag
				bombs.erase(it);      // remove bomb from payload
			}		
		}
		else if (mt == ROCKET) {
			if (rockets.size() >0) {  // if weapon available
				it = rockets.begin();
				it->x = x;  // set weapons loc and vel to jets parms
				it->y = y;
				it->z = z;
				it->vx = vx;
				it->vy = vy;
				it->vz = vz;
				released.push_back(*it); // copy weapon to released vector
				mass -= it->mass;     // decrease jet mass
				drag -= it->drag;     // decrease jet drag
				rockets.erase(it);    // remove rocket from payload
			}
		}
		else {
			if (missiles.size() >0) {  // if weapon available
				it = missiles.begin();
				it->x = x;  // set weapons loc and vel to jets parms
				it->y = y;
				it->z = z;
				it->vx = vx;
				it->vy = vy;
				it->vz = vz;
				released.push_back(*it); // copy weapon to released vector
				mass -= it->mass;     // decrease jet mass
				drag -= it->drag;     // decrease jet drag
				missiles.erase(it);   // remove missile from payload
			} 
		}
	}
}

// Function to update the jets location and the locations 
// of any released weapons
void Jet::update() {
	/***************** Physics Stuff ********************/
	// jet in line velocity
	float v = sqrt(vx*vx + vy * vy + vz * vz);
	// compute lift using formula L = 0.5*C*p*A*v^2
	// for typical density p = 1.225 for air and wing area A = 27.9m^2
	// and lift coef C = 1.164 then we can model lift force as:
	float L = 7.8 * v * v;
	float Ldz = (L - mass * 9.80) / mass;  // change in vertical velocity
	// compute in line drag force
	cout << "             jet     v = " << v << endl; //debug 
	float dragF = drag * v * v;
	// now compute in line acceleration for the jet
	float dv = (thrust - dragF) / mass;
	// then apply the acceleration to each vector vel component
	float dvx = dv * (vx / v);
	float dvy = dv * (vy / v);
	float dvz = Ldz; // dv * (vz / v) + Ldz;
	//cout << "debug lift dvz " << dvz << "   Ldz " << Ldz << endl;
	// update the vel vector components with accel
	vx += dvx;
	vy += dvy;
	vz += dvz;
	/*******************************************************/
	
	// Finally update jet location
	x += vx;
	y += vy;
	z += vz;

	// Cycle through and update released weapons applying some physics. 
	// Note: since we use vector components for velocity and position we 
	// must use some extra steps find in line forces and acceleration then 
	// apply those to the vector components.
	for (int i = 0; i < released.size(); i++) {
		/***************** Physics Stuff ********************/
		// find magnitude of in line velocity v
		float mv = sqrt(released[i].vx * released[i].vx
			+ released[i].vy * released[i].vy
			+ released[i].vz * released[i].vz);
		cout << "            weapon      v = " << mv << endl; //debug 
		// compute in line drag force
		float dragF = released[i].drag * mv * mv;
		// now compute in line acceleration for the jet
		float mdv = (released[i].thrust - dragF) / released[i].mass;
		// then apply the acceleration to each vector vel component
		float mdvx = dv * (released[i].vx / mv);
		float mdvy = dv * (released[i].vy / mv);
		float mdvz = dv * (released[i].vz / mv);
		// update the vel vector components with accel
		released[i].vx += mdvx;
		released[i].vy += mdvy;
		released[i].vz += mdvz - 9.80;  // accounts for accel due to gravity
		/*******************************************************/

		// Finally we can update weapon position. (int) cast may need work
		released[i].x += (int)released[i].vx;
		released[i].y += (int)released[i].vy;
		released[i].z += (int)released[i].vz;

		// If the weapon strikes the ground report its hit location and
		// erase it from the "released" weapons vector.
		if (released[i].z <= 0) {
			cout << "Weapon " << i << " Strike: type = " << released[i].mtype
				<< "  at x = " << released[i].x
				<< "  y = " << released[i].y
				<< "  z = " << released[i].z << endl;
			// Now delete this weapon from the released vector
			released.erase(released.begin() + i);  
		}
	}  // end for		           
}  // end update()

void Jet::dispstatus() {
	cout << "CS: " << callsign << "  Pos: " << x << " " << y << " "
		<< " " << z << "  Vel: " << vx << " " << vy << " " << vz
		<< " bombs: " << bombs.size() << " rockets: " << rockets.size()
		<< " missiles: " << missiles.size() << " mass: " << mass 
		<< " drag: " << drag << endl;
}

void Jet::dispreleased() {
	string mts;  // string to store munition type for display
	for (int i = 0; i < released.size(); i++) {
		if (released[i].mtype == BOMB)  // set the type string
			mts = "bomb";
		else if (released[i].mtype == ROCKET)
			mts = "rocket";
		else
			mts = "missile";
		// Now display weapon status
		cout << "Weapon" << i << " type = " << mts
			<< "  Pos at x = " << released[i].x
			<< "  y = " << released[i].y
			<< "  z = " << released[i].z << endl;
	}
}

// Function computes Pythagorean distance another Jet object and returns
// a int distance if in range and 0 otherwise.
int Jet::inrange(Jet *enemyjet, float weaponrange) {
	float d;
	d = sqrt((x - enemyjet->x)*(x - enemyjet->x) +
		(y - enemyjet->y)*(y - enemyjet->y) +
		(z - enemyjet->z)*(z - enemyjet->z));
	//cout << "Distance = " << d << endl;  // debug

	if (d <= weaponrange)
		return (int)d;
	else
		return 0;
}
