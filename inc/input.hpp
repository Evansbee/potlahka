#pragma once


#include <vector>
#include <string>

class hittable;
class camera;

struct input_return
{
	int width;
	int height;
	std::vector<hittable *> objects;
	camera* camera;
};

input_return ParseInputFile(const std::string& inputFile);
input_return ParseInputString(const std::string& inputFile);