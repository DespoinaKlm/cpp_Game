#pragma once
//properties that the player has position x,y height , width
class  Properties {
public:
	int m_xp, m_yp, m_widthp, m_heightp;
	Properties(int X, int Y, int width, int height) {
		m_xp = X;
		m_yp = Y;
		m_widthp = width;
		m_heightp = height;
	}
};
