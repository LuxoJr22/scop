#include "utils.hpp"
#include <fstream>

struct vert {
	float x;
	float y;
	float z;
};

struct faces {
	bool isTriangle;

	vert vertices[4];

	vert tris[2][3];

};

struct attributes {
	vert *vertices;
};

void load_obj(attributes *att, const char *filename)
{
	std::ifstream file;

	file.open(filename);
	

}