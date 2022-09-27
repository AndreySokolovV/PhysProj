#pragma once



namespace Consts {
	constexpr int xMax = 100;
	constexpr int yMax = 100;
	constexpr int partNum = 100;
	constexpr int partSize = 1;
}

class Particle
{
private:

	int m_x;
	int m_y;
	int m_dy;
	int m_dx;
	int m_size;
	int m_color;

public:

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

	void setColor(int color) { m_color = color; }

	int update_xy() { return m_x += m_dx; m_y += m_dy; }

};
