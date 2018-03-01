#pragma once

#include "config.hpp"
#include "vec3.hpp"

vec3 random_direction(); //unit length
vec3 random_in_unit_sphere();
real random_range(real lower = 0.0, real upper = 1.0); // lower <= ret < upper

