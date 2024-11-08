#include "utils.hpp"
#include <fstream>
#include <iostream>

std::array<float, 4> splitted_line(std::string line)
{
	std::string *lines;
	std::string	act_line;
	std::array<float, 4> number;
	int i = 0;

	number[3] = -1;
	act_line = line;
	while (act_line.find(' ') != std::string::npos)
	{
		act_line = act_line.substr(act_line.find(' ') + 1, act_line.length());
		number[i] = atof(act_line.substr(0, act_line.find(' ')).c_str());
		i ++;
	}
	return (number);
}


void Load_obj(attributes *att, const char *filename)
{
	std::ifstream file;
	std::string	line;
	std::array<float, 4> number;

	file.open(filename);
	

	while (file.good())
	{
		while (getline(file, line)) {
			if (line[0] == 'v')
			{
				number = splitted_line(line);

				vert act;
				act.x = number[0];
				act.y = number[1];
				act.z = number[2];

				att->vertices.push_back(act);
			}

			if (line[0] == 'f')
			{
				number = splitted_line(line);

				face face;

				face.vertices[0] = number[0];
				face.vertices[1] = number[1];
				face.vertices[2] = number[2];
				face.vertices[3] = number[3];

				if (number[3] != -1)
					face.isTriangle = true;
				else
					face.isTriangle = false;

				if (face.isTriangle)
				{
					face.tris[0][0] = face.vertices[0];
					face.tris[0][1] = face.vertices[1];
					face.tris[0][2] = face.vertices[2];

					att->faces.push_back(face);
				}
				else 
				{
					face.tris[0][0] = face.vertices[0];
					face.tris[0][1] = face.vertices[1];
					face.tris[0][2] = face.vertices[2];

					att->faces.push_back(face);

					face.tris[0][0] = face.vertices[3];
					face.tris[0][1] = face.vertices[1];
					face.tris[0][2] = face.vertices[2];

					att->faces.push_back(face);
				}
			}
		}
	}
	file.close();

}