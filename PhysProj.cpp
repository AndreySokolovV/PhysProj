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

	particle.setX(rand() % Consts::xMax);
	particle.setY(rand() % Consts::yMax);

	particle.setDx((rand() % 2) ? 1 : -1 );
	particle.setDy((rand() % 2) ? 1 : -1 );

	particles.push_back(particle);

	

}
ui.uiInit(argc, argv);
ui.uiShow();
std::cout << "end";
}

