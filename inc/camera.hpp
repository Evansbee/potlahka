#pragma once

#include "config.hpp"
#include "vec3.hpp"
#include "ray.hpp"

class camera
{
public:
	camera() = delete; //don't let it come in this way...
	camera(const vec3& position, const vec3& lookAt, real FoV, real AspectRatio) :
		m_Position(position),
		m_LookAt(lookAt),
		m_FoV(FoV),
		m_AspectRatio(AspectRatio)
	{
		_UpdateViewPlane();
	}

	ray GetRay(real u, real v) const;


	void SetPosition(const vec3 &newPosition);
	void SetLookAt(const vec3 &newLookAt);
	void SetFocusDistance(real newFocusDistance);
	void SetFoV(real newFoV);
	void SetAspectRatio(real newAspectRatio);

	vec3 Position() const {return m_Position; }
	vec3 LookAt() const { return m_LookAt; }
	real FocusDistance() const { return m_FocusDistance;  }
	real FoV() const { return m_FoV;  }
	real AspectRatio() const { return m_AspectRatio;  }

private:
	void _UpdateViewPlane();

	vec3 m_LowerLeftCorner;
	vec3 m_Horizontal;
	vec3 m_Vertical;

	vec3 m_Position;
	vec3 m_LookAt;
	real m_FocusDistance;
	real m_FoV; // vertical
	real m_AspectRatio; //width/height, usually positive
};