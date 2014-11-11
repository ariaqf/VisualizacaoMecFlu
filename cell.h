#ifndef _INCLUDE_CELL
#define _INCLUDE_CELL

#include <vector>

using std;

class Liquid 
{
	private double density, kinematic_viscosity;
	public Liquid();
};

/*class Particle
{
	private double x, y, speed_x, speed_y;
	private Liquid liquid;
	public Particle();
	public Particle(double x_, double y_);
	public Particle(double x_, double y_, double speed_x, double speed_y);
	public void setSpeed(double x_, double y_) 
	{
		speed_x = x_;
		speed_y = y_;
	}
	public void addSpeed(double x_, double y_) 
	{
		speed_x += x_;
		speed_y += y_;
	}
};*/

class Cell 
{
	private double x, y, width, height, speed_x, speed_y;
	private bool isVoid, hasLiquid, isBorder;
	public Cell();
	public Cell(double x_, double y_, double w_, double h_);
	public void setSpeed(double x_, double y_) 
	{
		speed_x = x_;
		speed_y = y_;
	}
	public void addSpeed(double x_, double y_) 
	{
		speed_x += x_;
		speed_y += y_;
	}
};

#endif