#pragma once


namespace Consts {
	constexpr int xMax = 100;
	constexpr int yMax = 100;
	constexpr int partNum = 100;
	constexpr int partSize = 1;
	constexpr int xMin = 0;
	constexpr int yMin = 0;
	constexpr int x1 = 35;
	constexpr int x2 = 65;
	constexpr int y1 = 35;
	constexpr int y2 = 65;

}

struct Color
{

	int  r;
	int  g;
	int  b;

};

class Particle
{
private:

	int m_x;
	int m_y;
	int m_dy;
	int m_dx;
	int m_size;
    Color m_color;
	int m_Weight;
public:

	Particle();
	
	void SetWeight(int m) { m_Weight = m; }
	int getWeight() { return m_Weight; }

	int getX() { return m_x; }
	int getY() { return m_y; }

	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }

	int getDx() { return m_dx; }
	int getDy() { return m_dy; }

	void setDx(int dx) { m_dx = dx; }
	void setDy(int dy) { m_dy = dy; }

	int getSize() { return m_size; }

	void setSize(int size) { m_size = size; }

	void setColor(Color color) { m_color = color;}
	Color getColor() { return m_color; }

	int update_xy();

};
