#include "Particle.h"

Particle::Particle()
{

	 m_x = 0;
	 m_y = 0;
	 m_dy = 1;
	 m_dx = 1;
	 m_size = 0;
	 m_color = 0;

}

int Particle::update_xy() 
{

	m_x += m_dx;
	m_y += m_dy;
	return 0;

}