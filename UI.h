#pragma once
#include <vector>
#include <GL/glut.h>
#include <cstdlib>
#include "Particle.h" 

struct Point
{
	int x;
	int y;
};

class UI
{
private:

	std::vector<Particle>* particles = nullptr;
	std::vector<Point> area;

	bool checkBoundX(int x, int y);
	bool checkBoundY(int y, int x);

	void drawArea();
	
public:

	UI(std::vector<Particle>& parts);
	void uiInit(int argc, char** argv);
	void uiShow();
	


};

