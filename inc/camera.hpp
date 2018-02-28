#pragma once

#include "config.hpp"
#include "vec3.hpp"
class camera
{
public:
	camera() = delete; //don't let it come in this way...

	void SetPosition(const vec3 &newPosition);
	void SetLookAt(const vec3 &newLookAt);
	void SetFocusDistance(real newFocusDistance);
	void SetFoV(real newFoV);

	vec3 Position() const;
	vec3 LookAt() const;
	real FocusDistance() const;
	real FoV() const;

private:
	vec3 m_Position;
	vec3 m_LookAt;
	real m_FocusDistance;
	real m_FoV; // width/height
};