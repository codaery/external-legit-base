#pragma once
#include "../../includes.hpp"

namespace math {
	float dot(const vector3& v1, const vector3& v2);
	float length(const vector3& v);
	bool world_to_screen(vector& from, vector& to, int width, int height);
	void sincos(float radians, float* sine, float* cosine);
	void calc_angle(vector3& vec_origin, vector3& vec_other, vector3& vec_angles);
	void angle_normalize(vector3& vec_angles);
	void clamp_angles(vector3& vec_angles);
	void make_vector(vector3& vec_angle, vector3& out);
	float get_fov(vector3& vec_angle, vector3& vec_origin, vector3& vec_other);
}