#include "catch.hpp"
#include "config.hpp"
#include "vec3.hpp"

TEST_CASE("Vec3 Test", "[vec3]")
{
	real f1 = 123.512f, f2 = 234.1232f, f3 = 32423.1232f;
	vec3 float_vec(f1, f2, f3);
	REQUIRE(float_vec[0] == f1);
	REQUIRE(float_vec.r == f1);
	REQUIRE(float_vec.x == f1);

	REQUIRE(float_vec[1] == f2);
	REQUIRE(float_vec.g == f2);
	REQUIRE(float_vec.y == f2);

	REQUIRE(float_vec[2] == f3);
	REQUIRE(float_vec.b == f3);
	REQUIRE(float_vec.z == f3);
}