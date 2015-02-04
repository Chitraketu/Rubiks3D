#include <math.h>
#include "vec3f.h"

using namespace std;

Vec3f::Vec3f() {

}

Vec3f::Vec3f(float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

float &Vec3f::operator[](int index) {
	return v[index];
}

float Vec3f::operator[](int index) const {
	return v[index];
}

Vec3f Vec3f::operator*(float scale) const {
	return Vec3f(v[0] * scale, v[1] * scale, v[2] * scale);
}

Vec3f Vec3f::operator/(float scale) const {
	return Vec3f(v[0] / scale, v[1] / scale, v[2] / scale);
}

Vec3f Vec3f::operator+(const Vec3f &other) const {
	return Vec3f(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}

Vec3f Vec3f::operator-(const Vec3f &other) const {
	return Vec3f(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
}

Vec3f Vec3f::operator-() const {
	return Vec3f(-v[0], -v[1], -v[2]);
}

const Vec3f &Vec3f::operator*=(float scale) {
	v[0] *= scale;
	v[1] *= scale;
	v[2] *= scale;
	return *this;
}

const Vec3f &Vec3f::operator/=(float scale) {
	v[0] /= scale;
	v[1] /= scale;
	v[2] /= scale;
	return *this;
}

const Vec3f &Vec3f::operator+=(const Vec3f &other) {
	v[0] += other.v[0];
	v[1] += other.v[1];
	v[2] += other.v[2];
	return *this;
}

const Vec3f &Vec3f::operator-=(const Vec3f &other) {
	v[0] -= other.v[0];
	v[1] -= other.v[1];
	v[2] -= other.v[2];
	return *this;
}

float Vec3f::magnitude() const {
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float Vec3f::magnitudeSquared() const {
	return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

Vec3f Vec3f::normalize() const {
	float m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return Vec3f(v[0] / m, v[1] / m, v[2] / m);
}

float Vec3f::dot(const Vec3f &other) const {
	return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2];
}

Vec3f Vec3f::cross(const Vec3f &other) const {
	return Vec3f(v[1] * other.v[2] - v[2] * other.v[1],
				 v[2] * other.v[0] - v[0] * other.v[2],
				 v[0] * other.v[1] - v[1] * other.v[0]);
}

Vec3f operator*(float scale, const Vec3f &v) {
	return v * scale;
}

bool Vec3f::operator!=(Vec3f va)
{
    return v[0]!=va.v[0] && v[1] != va.v[1] && v[2]!=va.v[2];
}

ostream &operator<<(ostream &output, const Vec3f &v) {
	cout << '(' << v[0] << ", " << v[1] << ", " << v[2] << ')';
	return output;
}

Vec3f rotate_about_axis(  Vec3f v,   float degreeAngle,   Vec3f axis)
	{
		// Check the preconditions.
		//if(v == null || axis == null) throw new java.lang.Error();
		//if(Math.abs(axis.length() - 1) >= EPSILON) throw new java.lang.Error();	// make sure axis is normalized

		// Main algorithm
		float radianAngle = degreeAngle*3.1428/180.0;
		float cosAngle = cosf(radianAngle), sinAngle = sinf(radianAngle);
		Vec3f aCROSSv = axis.cross(v);

		// ret = v cos radianAngle + (axis x v) sin radianAngle + axis(axis . v)(1 - cos radianAngle)
		// (See Mathematics for 3D Game Programming and Computer Graphics, P.62, for details of why this is (it's not very hard)).
		Vec3f ret = v;
		ret=(cosAngle)*ret;
		ret += (sinAngle)*aCROSSv;
		ret += axis.dot(v) * (1 - cosAngle)* axis;
		return ret;
	}







