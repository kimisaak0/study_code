#include "npcClass.h"



npcClass::npcClass()
{
	m_pos.x = 800;
	m_pos.y = 600;
	m_dSpeed = 50.0f + rand() % 150;
}

bool npcClass::Frame()
{
	int iHalfX = m_rtDraw.right / 2;
	int iHalfY = m_rtDraw.bottom / 2;
	
	if ((m_pos.x + iHalfX) > g_rtClient.right) {
		m_dDir[0] *= -1.0;
		m_pos.x = g_rtClient.right - iHalfX;
	}

	if (m_pos.y + iHalfY > g_rtClient.bottom) {
		m_dDir[1] *= -1.0;
		m_pos.y = g_rtClient.bottom - iHalfY;
	}

	if ((m_pos.x - iHalfX) < g_rtClient.left) {
		m_dDir[0] *= -1.0;
		m_pos.x = g_rtClient.left + iHalfX;
	}

	if (m_pos.y - iHalfY < g_rtClient.top) {
		m_dDir[1] *= -1.0;
		m_pos.y = g_rtClient.top + iHalfY;
	}

	m_pos.x += m_dDir[0] * m_dSpeed * g_dSecPerFrame;
	m_pos.y += m_dDir[1] * m_dSpeed * g_dSecPerFrame;
	m_posDraw.x = m_pos.x - iHalfX;
	m_posDraw.y = m_pos.y - iHalfY;

	m_rtCollision.left = (LONG)m_posDraw.x;
	m_rtCollision.top = (LONG)m_posDraw.y;
	m_rtCollision.right = m_rtCollision.left + m_rtDraw.right;
	m_rtCollision.bottom = m_rtCollision.top + m_rtDraw.bottom;

	return true;
	
}


npcClass::~npcClass()
{
}
