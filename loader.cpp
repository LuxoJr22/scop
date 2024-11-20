#include "utils.hpp"
#include <fstream>
#include <iostream>

std::array<float, 4> splitted_line(std::string line)
{
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


void make_triangles(face *face, attributes *att)
{
	vert v0 = att->vertices[face->vertices[0]];
	vert v1 = att->vertices[face->vertices[1]];
	vert v2 = att->vertices[face->vertices[2]];
	vert v3 = att->vertices[face->vertices[3]];

	float sqr02 = ((v2.x - v0.x) * (v2.x - v0.x)) + ((v2.y - v0.y) * (v2.y - v0.y)) + ((v2.z - v0.z) * (v2.z - v0.z));
	float sqr13 = ((v3.x - v1.x) * (v3.x - v1.x)) + ((v3.y - v1.y) * (v3.y - v1.y)) + ((v3.z - v1.z) * (v3.z - v1.z));

	if (sqr02 < sqr13)
	{
		face->tris[0][0] = face->vertices[0];
		face->tris[0][1] = face->vertices[1];
	 	face->tris[0][2] = face->vertices[2];

		face->tris[1][0] = face->vertices[0];
		face->tris[1][1] = face->vertices[2];
	 	face->tris[1][2] = face->vertices[3];
	}
	else
	{
		face->tris[0][0] = face->vertices[0];
		face->tris[0][1] = face->vertices[1];
	 	face->tris[0][2] = face->vertices[3];

		face->tris[1][0] = face->vertices[1];
		face->tris[1][1] = face->vertices[2];
	 	face->tris[1][2] = face->vertices[3];
	}
}

void center_obj(attributes *att)
{
	att->lim_x.max = att->vertices[0].x;
	att->lim_x.min = att->vertices[0].x;
	att->lim_y.max = att->vertices[0].y;
	att->lim_y.min = att->vertices[0].y;
	att->lim_z.max = att->vertices[0].z;
	att->lim_z.min = att->vertices[0].z;

	for (const auto& vert : att->vertices) {
		if (vert.x > att->lim_x.max) att->lim_x.max = vert.x;
		if (vert.x < att->lim_x.min) att->lim_x.min = vert.x;
		if (vert.y > att->lim_y.max) att->lim_y.max = vert.y;
		if (vert.y < att->lim_y.min) att->lim_y.min = vert.y;
		if (vert.z > att->lim_z.max) att->lim_z.max = vert.z;
		if (vert.z < att->lim_z.min) att->lim_z.min = vert.z;
	}
	
	att->off_x = (att->lim_x.max + att->lim_x.min) / 2;
	att->off_y = (att->lim_y.max + att->lim_y.min) / 2;
	att->off_z = (att->lim_z.max + att->lim_z.min) / 2;

	for (int i = 0; i < att->vertices.size(); i++) {
		att->vertices[i].x -= att->off_x;
		att->vertices[i].y -= att->off_y;
		att->vertices[i].z -= att->off_z;
	}
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

				face.vertices[0] = number[0] - 1;
				face.vertices[1] = number[1] - 1;
				face.vertices[2] = number[2] - 1;
				face.vertices[3] = number[3] - 1;

				if (number[3] == -1)
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
					make_triangles(&face, att);
					att->faces.push_back(face);
				}
			}
		}
	}
	file.close();

}