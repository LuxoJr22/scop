#ifndef UTILS_HPP
# define UTILS_HPP

#include <array>
#include <math.h> 


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
};

struct vector2
{
	float x;
	float y;

	bool operator==(const vector2& other) const {
		return x == other.x && y == other.y;
	}
};

// struct mat4
// {
// 	float mat[16];

// 	static mat4 create(float value){
// 		mat4 ret;

// 		for (int i = 0; i < 4; i++)
// 		{
// 			for (int x = 0; x < 4; x ++)
// 			{
// 				ret.mat[i * 4 + x] = value;
// 			}
// 		}
// 		return (ret);
// 	}

// 	bool operator==(const mat4& other) const {
// 		return mat == other.mat;
// 	}

// 	static mat4 rotate(mat4 mat, float angle, vector3 axis){
// 		mat4 ret;

// 		float cos = std::cos(angle);
// 		float sin = std::sin(angle);

// 		ret.mat[0] = mat.mat[0];
// 		ret.mat[1] = mat.mat[1];
// 		ret.mat[2] = mat.mat[2];
// 		ret.mat[3] = mat.mat[3];

// 		ret.mat[4] = mat.mat[4];
// 		ret.mat[5] = mat.mat[5];
// 		ret.mat[6] = mat.mat[6];
// 		ret.mat[7] = mat.mat[7];

// 		ret.mat[8] = mat.mat[8];
// 		ret.mat[9] = mat.mat[9];
// 		ret.mat[10] = mat.mat[10];
// 		ret.mat[11] = mat.mat[11];

// 		ret.mat[12] = mat.mat[12];
// 		ret.mat[13] = mat.mat[13];
// 		ret.mat[14] = mat.mat[14];
// 		ret.mat[15] = mat.mat[15];

// 		return (ret);
// 	}
// };

#endif