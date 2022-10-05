#include <iostream>
#include <vector> 
#include <cstdlib>
#include "UI.h"
#include "Particle.h"

//constexpr int xMax = 100;
//constexpr int yMax = 100;
//constexpr int partNum = 100;
//constexpr int partSize = 1;

int main(int argc, char** argv)
{
std::vector<Particle> particles;

UI ui(particles);

particles.reserve(Consts::partNum);

Particle particle;
for (int i = 0; i < Consts::partNum; i++) {

	particle.setX(rand() % Consts::x1);
	particle.setY(rand() % Consts::yMax);

	particle.setDx(rand() % Consts::maxDx - Consts::maxDx  /2);
	particle.setDy(rand() % Consts::maxDy - Consts::maxDy / 2);
    
	Color color = {255,0,0};

	switch (rand() % 4)
	{

	case 0:
		color.r = 255;
		color.g = 0;
		color.b = 0;
		break;

	case 1:
		color.r = 0;
		color.g = 255;
		color.b = 0;
		break;

	case 2:
		color.r = 0;
		color.g = 0;
		color.b = 255;
		break;

	case 3:
		color.r = 0;
		color.g = 0;
		color.b = 0;
		break;

	}

	particle.setColor(color);

	if (particle.getDx() == 0) 
	{
	    particle.setDx(particle.getDx() + 1);
	}

	if (particle.getDy() == 0)
	{
		particle.setDy(particle.getDy() + 1);
	}

	particles.push_back(particle);

	

}
ui.uiInit(argc, argv);
ui.uiShow();
//std::cout << "end";
}

