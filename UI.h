#pragma once
#include <vector>
#include <GL/glut.h>
#include <cstdlib>
#include "Particle.h" 

struct Point
{
	double x;
	double y;
};

class UI
{
private:

	std::vector<Particle<double>>* particles = nullptr;
	std::vector<Point> area;

	bool checkBoundX(double x, double y);
	bool checkBoundY(double y, double x);

	void drawArea();
	
public:

	UI(std::vector<Particle<double>>& parts);
	void uiInit(int argc, char** argv);
	void uiShow();
	


};

