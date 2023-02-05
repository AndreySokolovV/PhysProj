#include "Particle.h"
#include <GL/glut.h>


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

			if (max_V < ((it->getDx() * it->getDx()) + (it->getDy() * it->getDy())))
			{

				max_V = (it->getDx() * it->getDx()) + (it->getDy() * it->getDy());

			}



		}

		return sqrt(max_V);

	}

	double SearchMinV(std::vector<Particle<double>>* part)
	{

		auto particlePtr = part;

		auto firstElm = (particlePtr->begin());

		double min_V = (firstElm->getDx() * firstElm->getDx()) + (firstElm->getDy() * firstElm->getDy());

		for (auto it = particlePtr->begin(); it != particlePtr->end(); ++it)
		{

			if (min_V > ((it->getDx() * it->getDx()) + (it->getDy() * it->getDy())))
			{

				min_V = (it->getDx() * it->getDx()) + (it->getDy() * it->getDy());

			}



		}

		return sqrt(min_V);

	}

	double SearchAvgV(std::vector<Particle<double>>* part)
	{

		auto particlePtr = part;

		auto firstElm = (particlePtr->begin());

		double avg_V = sqrt((firstElm->getDx() * firstElm->getDx()) + (firstElm->getDy() * firstElm->getDy()));

		for (auto it = particlePtr->begin(); it != particlePtr->end(); ++it)
		{

			avg_V += sqrt((it->getDx() * it->getDx()) + (it->getDy() * it->getDy()));

		}

		return avg_V/particlePtr->size();

	}

	void histogram(std::vector<Particle<double>>* part)
	{
		auto particlePtr = part;

		double vAbs = 0;

		int hist[10] = { 0,0,0,0,0,0,0,0,0,0 };


		for (auto it = particlePtr->begin(); it != particlePtr->end(); ++it)
		{


			vAbs = sqrt((it->getDx() * it->getDx()) + (it->getDy() * it->getDy())) * 1000;


			if (vAbs >= 0 && vAbs <= 200)
			{

				hist[0]++;

			}

			else if (vAbs >= 201 && vAbs <= 400)
			{

				hist[1]++;

			}

			else if (vAbs >= 401 && vAbs <= 600)
			{

				hist[2]++;

			}

			else if (vAbs >= 601 && vAbs <= 800)
			{

				hist[3]++;

			}

			else if (vAbs >= 801 && vAbs <= 1000)
			{

				hist[4]++;

			}

			else if (vAbs >= 1001 && vAbs <= 1200)
			{

				hist[5]++;

			}

			else if (vAbs >= 1201 && vAbs <= 1400)
			{

				hist[6]++;

			}

			else if (vAbs >= 1401 && vAbs <= 1600)
			{

				hist[7]++;

			}

			else if (vAbs >= 1601 && vAbs <= 1800)
			{

				hist[8]++;

			}

			else if (vAbs >= 1801 && vAbs <= 2000)
			{

				hist[9]++;

			}

		}

		double x1 = -0.292;
		double y1 = -1;
		double d = 0.058;
		double x2 = x1 + d;

		for (int i = 0; i < 10; i++)
		{

			glRectd(x1, y1, x2, (static_cast<double>(hist[i]))/100 - 1);

			x1 += d;
			x2 += d;

		}



	}

	void histogramold(std::vector<Particle<double>>* part)
	{
		auto particlePtr = part;

		double vAbs = 0;

		int hist[10] = { 0,0,0,0,0,0,0,0,0,0 };


		for (auto it = particlePtr->begin(); it != particlePtr->end(); ++it)
		{


			vAbs = sqrt((it->getDx() * it->getDx()) + (it->getDy() * it->getDy())) * 1000;


			if (vAbs >= 0 && vAbs <= 200)
			{

				hist[0]++;

			}

			else if (vAbs >= 201 && vAbs <= 400)
			{

				hist[1]++;

			}

			else if (vAbs >= 401 && vAbs <= 600)
			{

				hist[2]++;

			}

			else if (vAbs >= 601 && vAbs <= 800)
			{

				hist[3]++;

			}

			else if (vAbs >= 801 && vAbs <= 1000)
			{

				hist[4]++;

			}

			else if (vAbs >= 1001 && vAbs <= 1200)
			{

				hist[5]++;

			}

			else if (vAbs >= 1201 && vAbs <= 1400)
			{

				hist[6]++;

			}

			else if (vAbs >= 1401 && vAbs <= 1600)
			{

				hist[7]++;

			}

			else if (vAbs >= 1601 && vAbs <= 1800)
			{

				hist[8]++;

			}

			else if (vAbs >= 1801 && vAbs <= 2000)
			{

				hist[9]++;

			}

		}

		double x1 = -0.292;
		double y1 = -1;
		double d = 0.058;
		double x2 = x1 + d;

		for (int i = 0; i < 10; i++)
		{

			glRectd(x1, y1, x2, (static_cast<double>(hist[i])) / 100 - 1);

			x1 += d;
			x2 += d;

		}



	}


}