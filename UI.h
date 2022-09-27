#pragma once
#include <vector>
#include <GL/glut.h>
#include <cstdlib>
#include "Particle.h" 

class UI
{
private:

	std::vector<Particle>* particles = nullptr;


public:

	UI(std::vector<Particle>& parts) { particles = &parts;}
	void uiInit(int argc, char** argv);
	void uiShow();
	
};

