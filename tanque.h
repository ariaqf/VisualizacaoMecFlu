#ifndef _INCLUDE_TANQUE
#define _INCLUDE_TANQUE

#include "Cell.h"

using std;

class Tanque 
{
	private double width, height, gravity;
	private vector<vector<Cell>> cells;
//	private vector<Particle> particles;
	private Liquid liquid;
	public Tanque();
	public Tanque(double w_, double h_);
	public Tanque(double w_, double h_, Liquid l_);
	public void startFlow();
};

#endif