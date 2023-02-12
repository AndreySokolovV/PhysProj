#pragma once
#include <vector>

namespace Consts
{
	constexpr double WinWidth = 1200;
	constexpr double WinHeight = 800;
	constexpr double xMax = 100;
	constexpr double yMax = 100;
	
	constexpr double partSize = 2;
	constexpr double xMin = 0.0;
	constexpr double yMin = 0.0;
	constexpr double x1 = 35;
	constexpr double x2 = 65;
	constexpr double y1 = 35;
	constexpr double y2 = 65;
}





struct Color
{

	int  r;
	int  g;
	int  b;

};

enum class State { outOfHit, inHit };

template <typename T>
class Particle
{
private:
    
	
	T m_x;
	T m_y;
	T m_dy;
	T m_dx;
	T m_size;
    Color m_color;
	T m_Weight;
	State m_state;
	int m_index;
public:

	Particle();
	
	void SetWeight(T m) { m_Weight = m; }
	T getWeight() { return m_Weight; }

	T getX() { return m_x; }
	T getY() { return m_y; }

	void setX(T x) { m_x = x; }
	void setY(T y) { m_y = y; }

	T getDx() { return m_dx; }
	T getDy() { return m_dy; }

	void setDx(T dx) { m_dx = dx; }
	void setDy(T dy) { m_dy = dy; }

	T getSize() { return m_size; }

	void setSize(T size) { m_size = size; }

	void setColor(Color color) { m_color = color;}
	Color getColor() { return m_color; }

	State getState() { return m_state; }
	void setState(State state) { m_state = state; }

	int getIndex() { return m_index; }
	void setIndex(int index) { m_index = index; }

	T update_xy();

};

namespace MiscFunc
{

	double SearchMaxV(std::vector<Particle<double>>* part);
	double SearchMinV(std::vector<Particle<double>>* part);
	void histogram(std::vector<Particle<double>>* part);
	double SearchAvgV(std::vector<Particle<double>>* part);

}