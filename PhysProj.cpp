#include <iostream>
#include <vector> 
#include <cstdlib>
#include "UI.h"
#include "Particle.h"
#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include "json11/json11.hpp"
//constexpr int xMax = 100;
//constexpr int yMax = 100;
//constexpr int partNum = 100;
//constexpr int partSize = 1;

namespace Params
{

	int partNum = 100;

}

static void LoadSettings()
{

	std::string line;
	std::string jsonData;
	std::ifstream in("settings.json");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			jsonData.append(line);
		}
	}
	in.close();

	std::string err;	

	const auto json = json11::Json::parse(jsonData, err);

	Params::partNum = atoi(json["numPoints"].dump().c_str());
   
	

}


static double MyRandf(double lower_bound, double upper_bound)
{

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(lower_bound, upper_bound);
	return dis(gen);

}

int main(int argc, char** argv)
{

	LoadSettings();

	std::vector<Particle<double>> particles;

	UI ui(particles);

	particles.reserve(Params::partNum);

	Particle<double> particle;
	for (int i = 0; i < Params::partNum; i++) 
	{

		particle.setIndex(i);
		particle.getIndex();

		particle.setX(MyRandf(Consts::xMin, Consts::x1));
		particle.setY(MyRandf(Consts::yMin, Consts::yMax));

		particle.setDx(MyRandf(-Consts::maxDx, Consts::maxDx));
		particle.setDy(MyRandf(-Consts::maxDy, Consts::maxDy));

		particle.setSize(Consts::partSize);

		particle.SetWeight(rand() % 10 + 1);

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

