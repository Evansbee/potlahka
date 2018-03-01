#include "camera.hpp"


ray camera::GetRay(real u, real v) const
{
	return ray(m_Position, m_LowerLeftCorner + u * m_Horizontal + v * m_Vertical);
}

void camera::_UpdateViewPlane()
{
	m_LowerLeftCorner = vec3(-2.0, -1.0, -1.0);
	m_Horizontal = vec3(4.0, 0.0, 0.0);
	m_Vertical = vec3(0.0, 2.0, 0.0);
}