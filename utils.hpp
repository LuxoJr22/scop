#ifndef UTILS_HPP
# define UTILS_HPP

# define GLFW_INCLUDE_VULKAN
# include <GLFW/glfw3.h>

# include <array>
# include <math.h> 
# include <vector>
# include <unordered_map>
# include <chrono>
# include <fstream>
# include <iostream>
# include <stdexcept>
# include <cstdlib>
# include <vector>
# include <cstring>
# include <cstdint>
# include <limits>
# include <algorithm>
# include <random>
# include <optional>
# include <array>
# include <map>
# include <set>

struct vert {
	float x;
	float y;
	float z;
};

struct face {
	bool isTriangle;

	float vertices[4];

	float tris[2][3];

};

struct limit {
	float max;
	float min;
};


struct attributes {
	std::vector<vert> vertices;
	std::vector<face> faces;

	limit lim_x;
	limit lim_y;
	limit lim_z;

	float off_x;
	float off_y;
	float off_z;
};

struct colors {
	int r;
	int g;
	int b;
	int a;
};

struct img_load {
	int height;
	int width;
	int nb_char;
	int len_char;
	std::map<std::string, colors> chars;
	unsigned char *pixels;
};

struct vector4
{
	float x;
	float y;
	float z;
	float w;

	bool operator==(const vector4& other) const {
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	static vector4 create(float x, float y, float z, float w){
		vector4 ret;

		ret.x = x;
		ret.y = y;
		ret.z = z;
		ret.w = w;

		return (ret);
	}

	float& operator[](std::size_t idx) { 
		if (idx == 0)
			return x; 
		if (idx == 1)
			return y;
		if (idx == 2)
			return z; 
		if (idx == 3)
			return w;
		else
			return w; 
	}

	vector4 operator*(const vector4& rhs)
	{
		vector4 ret;
		ret.x = rhs.x * x;
		ret.y = rhs.y * y;
		ret.z = rhs.z * z;
		ret.w = rhs.w * w;
		return (ret);
	}

	vector4 operator*(const float& rhs)
	{
		vector4 ret;
		ret.x = rhs * x;
		ret.y = rhs * y;
		ret.z = rhs * z;
		ret.w = rhs * w;
		return (ret);
	}


	vector4 operator+(const vector4& rhs)
	{
		vector4 ret;
		ret.x = rhs.x + x;
		ret.y = rhs.y + y;
		ret.z = rhs.z + z;
		ret.w = rhs.w + w;
		return (ret);
	}
};


struct vector3
{
	float x;
	float y;
	float z;

	bool operator==(const vector3& other) const {
		return x == other.x && y == other.y && z == other.z;
	}

	static vector3 create(float x, float y, float z){
		vector3 ret;

		ret.x = x;
		ret.y = y;
		ret.z = z;

		return (ret);
	}

	vector3 operator*(const float& rhs)
	{
		vector3 ret;
		ret.x = rhs * x;
		ret.y = rhs * y;
		ret.z = rhs * z;
		return (ret);
	}

	vector3 operator-(const vector3& rhs)
	{
		vector3 ret;
		ret.x = x - rhs.x;
		ret.y = y - rhs.y;
		ret.z = z - rhs.z;
		return (ret);
	}

	float& operator[](std::size_t idx) { 
		if (idx == 0)
			return x; 
		if (idx == 1)
			return y;
		if (idx == 2)
			return z;
		else
			return z; 
	}
	
};

struct vector2
{
	float x;
	float y;

	bool operator==(const vector2& other) const {
		return x == other.x && y == other.y;
	}
};

struct mat4
{
	vector4 mat[4];

	static mat4 create(float value){
		mat4 ret;

		for (int i = 0; i < 4; i++)
		{
			for (int x = 0; x < 4; x ++)
			{
				if (i == x)
					ret.mat[i][x] = value;
				else
					ret.mat[i][x] = 0.0f;
			}
		}
		return (ret);
	}

	vector4& operator[](std::size_t idx) { return mat[idx]; }

	bool operator==(const mat4& other) const {
		return mat == other.mat;
	}

	static mat4 rotate(mat4 mat, float angle, vector3 axis){
		mat4 ret;
		mat4 rotate;


		float cos = std::cos(angle);
		float sin = std::sin(angle);

		vector3 temp(axis * (1.0f - cos));

		rotate[0][0] = cos + temp[0] * axis[0];
		rotate[0][1] = temp[0] * axis[1] + sin * axis[2];
		rotate[0][2] = temp[0] * axis[2] - sin * axis[1];

		rotate[1][0] = temp[1] * axis[0] - sin * axis[2];
		rotate[1][1] = cos + temp[1] * axis[1];
		rotate[1][2] = temp[1] * axis[2] + sin * axis[0];

		rotate[2][0] = temp[2] * axis[0] + sin * axis[1];
		rotate[2][1] = temp[2] * axis[1] - sin * axis[0];
		rotate[2][2] = cos + temp[2] * axis[2];


		ret[0] = mat[0] * rotate[0][0] + mat[1] * rotate[0][1] + mat[2] * rotate[0][2];
		ret[1] = mat[0] * rotate[1][0] + mat[1] * rotate[1][1] + mat[2] * rotate[1][2];
		ret[2] = mat[0] * rotate[2][0] + mat[1] * rotate[2][1] + mat[2] * rotate[2][2];
		ret[3] = mat[3];

		return (ret);
	}
};

void Load_obj(attributes *att, const char *filename);
mat4 lookat(vector3 eye, vector3 center, vector3 up);
mat4 perspective(float fov, float aspect, float near, float far);
void keyboard_input(GLFWwindow  *window, vector3 *position);
std::array<float, 4> splitted_line(std::string line);
unsigned char *load_img(const char *str, int *width, int *height);
void center_obj(attributes *att);

#endif