#include "maths.hpp"

bool math::world_to_screen(vector& from, vector& to, int width, int height)
{
	const auto matrix = mem::get().rpm<world_to_screen_matrix>(mem::get().client_dll + offsets::viewmatrix);

	to.x = matrix.flMatrix[0][0] * from.x + matrix.flMatrix[0][1] * from.y + matrix.flMatrix[0][2] * from.z + matrix.flMatrix[0][3];
	to.y = matrix.flMatrix[1][0] * from.x + matrix.flMatrix[1][1] * from.y + matrix.flMatrix[1][2] * from.z + matrix.flMatrix[1][3];

	float w = matrix.flMatrix[3][0] * from.x + matrix.flMatrix[3][1] * from.y + matrix.flMatrix[3][2] * from.z + matrix.flMatrix[3][3];

	if (w < 0.01f)
		return false;

	float invw = 1.0f / w;
	to.x *= invw;
	to.y *= invw;

	float x = width / 2;
	float y = height / 2;

	x += 0.5 * to.x * width + 0.5;
	y -= 0.5 * to.y * height + 0.5;

	to.x = x;
	to.y = y;

	return true;
}

float math::dot(const vector3& v1, const vector3& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float math::length(const vector3& v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

void math::sincos(float radians, float* sine, float* cosine)
{
	*sine = (float)sin(radians);
	*cosine = (float)cos(radians);
}

void math::calc_angle(vector3& vec_origin, vector3& vec_other, vector3& vec_angles) {
	vector3 vec_delta = vector3((vec_origin[0] - vec_other[0]), (vec_origin[1] - vec_other[1]), (vec_origin[2] - vec_other[2]));
	float hyp = sqrtf(vec_delta[0] * vec_delta[0] + vec_delta[1] * vec_delta[1]);

	vec_angles[0] = (float)atan(vec_delta[2] / hyp) * (float)(180.f / M_PI);
	vec_angles[1] = (float)atan(vec_delta[1] / vec_delta[0]) * (float)(180.f / M_PI);
	vec_angles[2] = (float)0.f;

	if (vec_delta[0] >= 0.f)
		vec_angles[1] += 180.0f;
}

void math::angle_normalize(vector3& vec_angles) {
	for (int i = 0; i < 3; i++)
	{
		if (vec_angles[i] < -180.0f) vec_angles[i] += 360.0f;
		if (vec_angles[i] > 180.0f) vec_angles[i] -= 360.0f;
	}

	if (vec_angles.x < -89.0f)
		vec_angles.x = 89.0f;
	if (vec_angles.x > 89.0f)
		vec_angles.x = 89.0f;

	vec_angles.z = 0;
}

void math::clamp_angles(vector3& vec_angles) {
	while (vec_angles.y < -180.0f)
		vec_angles.y += 360.0f;
	while (vec_angles.y > 180.0f)
		vec_angles.y -= 360.0f;

	if (vec_angles.x < -89.0f)
		vec_angles.x = 89.0f;
	if (vec_angles.x > 89.0f)
		vec_angles.x = 89.0f;

	vec_angles.z = 0;
}

void math::make_vector(vector3& vec_angle, vector3& out) {
	float pitch = float(vec_angle[0] * M_PI / 180);
	float tmp = float(cos(pitch));
	float yaw = float(vec_angle[1] * M_PI / 180);
	out[0] = float(-tmp * -cos(yaw));
	out[1] = float(sin(yaw) * tmp);
	out[2] = float(-sin(pitch));
}

float math::get_fov(vector3& vec_angle, vector3& vec_origin, vector3& vec_other) {
	vector3 ang, aim;
	double fov;

	calc_angle(vec_origin, vec_other, ang);
	make_vector(vec_angle, aim);
	make_vector(ang, ang);

	float mag_s = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
	float mag_d = sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));

	float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];

	fov = acos(u_dot_v / (mag_s * mag_d)) * (180.f / M_PI);

	fov *= 1.4;

	return float(fov);
}