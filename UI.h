#pragma once
#include <vector>
#include <GL/glut.h>
#include <cstdlib>
#include "Particle.h" 
#include "TextOutput.h"

struct Point
{
	double x;
	double y;
};

class UI
{
private:

	std::vector<Particle<double>>* particles = nullptr;
	TextOutput* m_text;
	std::vector<Point> area;

	bool checkBoundX(double x, double y);
	bool checkBoundY(double y, double x);
	
	void drawArea();
	void drawText();

public:

	UI(std::vector<Particle<double>>& parts, TextOutput& text);
	void uiInit(int argc, char** argv);
	void uiShow();
	


};

