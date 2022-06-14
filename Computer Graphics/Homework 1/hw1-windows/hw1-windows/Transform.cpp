// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// define identity matrix
	mat3 identity(1.0f);

	// convert to radians
	float radian_degrees = glm::radians(degrees);

	// define matrix aa
	mat3 aa = mat3(
		axis.x * axis.x, axis.x * axis.y, axis.x * axis.z,
		axis.x * axis.y, axis.y * axis.y, axis.y * axis.z,
		axis.x * axis.z, axis.y * axis.z, axis.z * axis.z
	);

	// define matrix A
	mat3 A = mat3(
		0, axis.z, -axis.y,
		-axis.z, 0, axis.x,
		axis.y, -axis.x, 0
	);

	// calculate sine and cosine
	float sine = sin(radian_degrees);
	float cosine = cos(radian_degrees);

	// Rodrigues rotation formula
	return cosine * identity + (1 - cosine) * glm::transpose(aa) + A * sine;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	eye = rotate(degrees, up) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE 
	vec3 rotation_axis = glm::normalize(glm::cross(eye, up));
	mat3 rotation_matrix = rotate(degrees, rotation_axis);

	eye = rotation_matrix * eye;
	up = glm::normalize(rotation_matrix * up);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
	// You will change this return call
	return mat4(
		u.x, v.x, w.x, 0,
		u.y, v.y, w.y, 0,
		u.z, v.z, w.z, 0,
		-u.x * eye.x - u.y * eye.y - u.z * eye.z, -v.x * eye.x - v.y * eye.y - v.z * eye.z, -w.x * eye.x - w.y * eye.y - w.z * eye.z, 1);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}