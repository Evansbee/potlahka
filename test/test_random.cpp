#include "catch.hpp"
#include "random.hpp"

TEST_CASE("Random Uniform Audit", "[Random]")
{
	INFO("Random -1.0 - 1.0: " << random_range(-1.0, 1.0));
	INFO("Random -1.0 - 1.0: " << random_range(-1.0, 1.0));
	INFO("Random -1.0 - 1.0: " << random_range(-1.0, 1.0));
	INFO("Random -1.0 - 1.0: " << random_range(-1.0, 1.0));
	INFO("Random -10.0 - 10.0: " << random_range(-10.0, 10.0));
	INFO("Random -10.0 - 10.0: " << random_range(-10.0, 10.0));
	INFO("Random -10.0 - 10.0: " << random_range(-10.0, 10.0));
	INFO("Random -10.0 - 10.0: " << random_range(-10.0, 10.0));
	REQUIRE(true);
}

TEST_CASE("Random Direction Audit", "[Random]")
{
	INFO("Random Direction: " << random_direction());
	INFO("Random Direction: " << random_direction());
	INFO("Random Direction: " << random_direction());
	INFO("Random Direction: " << random_direction());
	REQUIRE(true);
}