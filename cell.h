#ifndef _INCLUDE_CELL
#define _INCLUDE_CELL

#include <iostream>

/*class Liquid 
{
	private double density, kinematic_viscosity;
	public Liquid();
};*/

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
	private:
	 double width, height;
	public:
	 bool isVoid, hasLiquid, isBorder;
	 double speed_x, speed_y, leftSpeed, rightSpeed, topSpeed, bottomSpeed;
	 Cell() {
	 	height = 10;
	 	width = 10;
	 	isVoid = false;
	 	hasLiquid = false;
	 	isBorder = false;
	 	speed_x = 0;
	 	speed_y = 0;
	 	leftSpeed = 0;
	 	rightSpeed = 0;
	 	topSpeed = 0;
	 	bottomSpeed = 0;
	 }
	 Cell(double w_, double h_) {
	 	height = h_;
	 	width = w_;
	 	isVoid = false;
	 	hasLiquid = false;
	 	isBorder = false;
	 	speed_x = 0;
	 	speed_y = 0;
	 	leftSpeed = 0;
	 	rightSpeed = 0;
	 	topSpeed = 0;
	 	bottomSpeed = 0;
	 }
	 void updateSpeed() {
	 	speed_x = (leftSpeed+rightSpeed)/2;
	 	speed_y = (topSpeed+bottomSpeed)/2;
	 }
};

#endif