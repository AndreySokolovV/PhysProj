#include "Particle.h"

Particle<double>::Particle()
{

	 m_x = 0;
	 m_y = 0;
	 m_dy = 1;
	 m_dx = 1;
	 m_size = 0;
	 m_color = {255,0,0};
	 m_Weight = 1;
	 m_state = State::outOfHit;
}

double Particle<double>::update_xy()
{

	m_x += m_dx;
	m_y += m_dy;
	return 0;

}

namespace MiscFunc
{

	double SearchMaxV(std::vector<Particle<double>>* part)
	{

		auto particlePtr = part;

		auto firstElm = (particlePtr->begin());

		double max_V = (firstElm->getDx() * firstElm->getDx()) + (firstElm->getDy() * firstElm->getDy());

		for (auto it = particlePtr->begin(); it != particlePtr->end(); ++it)
		{

			double dx = it->getDx();
			double dy = it->getDy();

			if (max_V < ((it->getDx() * it->getDx()) + (it->getDy() * it->getDy())))
			{

				max_V = (it->getDx() * it->getDx()) + (it->getDy() * it->getDy());

			}



		}

		return sqrt(max_V);

	}

}