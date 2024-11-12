#include "utils.hpp"

mat4 perspective(float fov, float aspect, float near, float far)
{
	float	tanfov = std::tan(fov / 2.0f);
	mat4	result = mat4::create(0.0f);

	result[0][0] = 1 / (aspect * tanfov);
	result[1][1] = 1 / tanfov;
	result[2][2] = far / (near - far);
	result[2][3] = -1.0f;
	result[3][2] = -(far * near) / (far - near) ;

	return (result);
};

float dot_product(vector3 v1, vector3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

vector3 cross_product(vector3 v1, vector3 v2)
{
	return (vector3::create((v1.y * v2.z) - (v2.y * v1.z), (v1.z * v2.x) - (v2.z * v1.x), (v1.x * v2.y) - (v2.x * v1.y)));
}

vector3 normalize_vec(vector3 vec)
{
	vector3 ret;

	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

	ret.x = vec.x / length;
	ret.y = vec.y / length;
	ret.z = vec.z / length;
	return (ret);
}

mat4 lookat(vector3 eye, vector3 center, vector3 up)
{
	vector3 f = normalize_vec(center - eye);
	vector3 s = normalize_vec(cross_product(f, up));
	vector3 u = cross_product(s, f);

	mat4 result = mat4::create(1);
	result[0][0] = s.x;
	result[1][0] = s.y;
	result[2][0] = s.z;
	result[0][1] = u.x;
	result[1][1] = u.y;
	result[2][1] = u.z;
	result[0][2] = -f.x;
	result[1][2] = -f.y;
	result[2][2] = -f.z;
	result[3][0] = -dot_product(s, eye);
	result[3][1] = -dot_product(u, eye);
	result[3][2] = dot_product(f, eye);

	return (result);

}

