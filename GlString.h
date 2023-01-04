#pragma once
#include <string>
class GlString
{
public:

	GlString(std::string str, double x, double y)
	{
		m_str = str;
		m_x = x;
		m_y = y;
	}

	std::string m_str;
	double m_x;
	double m_y;

};

