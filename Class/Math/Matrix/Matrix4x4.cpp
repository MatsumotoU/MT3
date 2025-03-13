#include "Matrix4x4.h"
#include "../Vector/Vector3.h"
#include <assert.h>
#include <cmath>

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const {
	Matrix4x4 result = {};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			result.m[y][x] = this->m[y][x] + other.m[y][x];
		}
	}
	return result;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const {
	Matrix4x4 result = {};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			result.m[y][x] = this->m[y][x] - other.m[y][x];
		}
	}
	return result;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
	Matrix4x4 result = {};

	for (int i = 0; i < 4; i++) {
		result.m[i][0] = this->m[i][0] * other.m[0][0] + this->m[i][1] * other.m[1][0] + this->m[i][2] * other.m[2][0] + this->m[i][3] * other.m[3][0];
		result.m[i][1] = this->m[i][0] * other.m[0][1] + this->m[i][1] * other.m[1][1] + this->m[i][2] * other.m[2][1] + this->m[i][3] * other.m[3][1];
		result.m[i][2] = this->m[i][0] * other.m[0][2] + this->m[i][1] * other.m[1][2] + this->m[i][2] * other.m[2][2] + this->m[i][3] * other.m[3][2];
		result.m[i][3] = this->m[i][0] * other.m[0][3] + this->m[i][1] * other.m[1][3] + this->m[i][2] * other.m[2][3] + this->m[i][3] * other.m[3][3];
	}

	return result;
}

Matrix4x4 Matrix4x4::Inverse() const {
	Matrix4x4 result = {};

	float i =
		+ this->m[0][0] * this->m[1][1] * this->m[2][2] * this->m[3][3]
		+ this->m[0][0] * this->m[1][2] * this->m[2][3] * this->m[3][1]
		+ this->m[0][0] * this->m[1][3] * this->m[2][1] * this->m[3][2]

		- this->m[0][0] * this->m[1][3] * this->m[2][2] * this->m[3][1]
		- this->m[0][0] * this->m[1][2] * this->m[2][1] * this->m[3][3]
		- this->m[0][0] * this->m[1][1] * this->m[2][3] * this->m[3][2]

		- this->m[0][1] * this->m[1][0] * this->m[2][2] * this->m[3][3]
		- this->m[0][2] * this->m[1][0] * this->m[2][3] * this->m[3][1]
		- this->m[0][3] * this->m[1][0] * this->m[2][1] * this->m[3][2]

		+ this->m[0][3] * this->m[1][0] * this->m[2][2] * this->m[3][1]
		+ this->m[0][2] * this->m[1][0] * this->m[2][1] * this->m[3][3]
		+ this->m[0][1] * this->m[1][0] * this->m[2][3] * this->m[3][2]

		+ this->m[0][1] * this->m[1][2] * this->m[2][0] * this->m[3][3]
		+ this->m[0][2] * this->m[1][3] * this->m[2][0] * this->m[3][1]
		+ this->m[0][3] * this->m[1][1] * this->m[2][0] * this->m[3][2]

		- this->m[0][3] * this->m[1][2] * this->m[2][0] * this->m[3][1]
		- this->m[0][2] * this->m[1][1] * this->m[2][0] * this->m[3][3]
		- this->m[0][1] * this->m[1][3] * this->m[2][0] * this->m[3][2]

		- this->m[0][1] * this->m[1][2] * this->m[2][3] * this->m[3][0]
		- this->m[0][2] * this->m[1][3] * this->m[2][1] * this->m[3][0]
		- this->m[0][3] * this->m[1][1] * this->m[2][2] * this->m[3][0]

		+ this->m[0][3] * this->m[1][2] * this->m[2][1] * this->m[3][0]
		+ this->m[0][2] * this->m[1][1] * this->m[2][3] * this->m[3][0]
		+ this->m[0][1] * this->m[1][3] * this->m[2][2] * this->m[3][0];

	// 零除算回避用
	if (i == 0.0f) {
		assert(false);
	}

	result.m[0][0] = (
		+ this->m[1][1] * this->m[2][2] * this->m[3][3]
		+ this->m[1][2] * this->m[2][3] * this->m[3][1]
		+ this->m[1][3] * this->m[2][1] * this->m[3][2]
		- this->m[1][3] * this->m[2][2] * this->m[3][1]
		- this->m[1][2] * this->m[2][1] * this->m[3][3]
		- this->m[1][1] * this->m[2][3] * this->m[3][2]
		) / i;
	result.m[0][1] = (
		- this->m[0][1] * this->m[2][2] * this->m[3][3]
		- this->m[0][2] * this->m[2][3] * this->m[3][1]
		- this->m[0][3] * this->m[2][1] * this->m[3][2]
		+ this->m[0][3] * this->m[2][2] * this->m[3][1]
		+ this->m[0][2] * this->m[2][1] * this->m[3][3]
		+ this->m[0][1] * this->m[2][3] * this->m[3][2]
		) / i;
	result.m[0][2] = (
		+ this->m[0][1] * this->m[1][2] * this->m[3][3]
		+ this->m[0][2] * this->m[1][3] * this->m[3][1]
		+ this->m[0][3] * this->m[1][1] * this->m[3][2]
		- this->m[0][3] * this->m[1][2] * this->m[3][1]
		- this->m[0][2] * this->m[1][1] * this->m[3][3]
		- this->m[0][1] * this->m[1][3] * this->m[3][2]
		) / i;
	result.m[0][3] = (
		- this->m[0][1] * this->m[1][2] * this->m[2][3]
		- this->m[0][2] * this->m[1][3] * this->m[2][1]
		- this->m[0][3] * this->m[1][1] * this->m[2][2]
		+ this->m[0][3] * this->m[1][2] * this->m[2][1]
		+ this->m[0][2] * this->m[1][1] * this->m[2][3]
		+ this->m[0][1] * this->m[1][3] * this->m[2][2]
		) / i;

	result.m[1][0] = (
		- this->m[1][0] * this->m[2][2] * this->m[3][3]
		- this->m[1][2] * this->m[2][3] * this->m[3][0]
		- this->m[1][3] * this->m[2][0] * this->m[3][2]
		+ this->m[1][3] * this->m[2][2] * this->m[3][0]
		+ this->m[1][2] * this->m[2][0] * this->m[3][3]
		+ this->m[1][0] * this->m[2][3] * this->m[3][2]
		) / i;
	result.m[1][1] = (
		+ this->m[0][0] * this->m[2][2] * this->m[3][3]
		+ this->m[0][2] * this->m[2][3] * this->m[3][0]
		+ this->m[0][3] * this->m[2][0] * this->m[3][2]
		- this->m[0][3] * this->m[2][2] * this->m[3][0]
		- this->m[0][2] * this->m[2][0] * this->m[3][3]
		- this->m[0][0] * this->m[2][3] * this->m[3][2]
		) / i;
	result.m[1][2] = (
		- this->m[0][0] * this->m[1][2] * this->m[3][3]
		- this->m[0][2] * this->m[1][3] * this->m[3][0]
		- this->m[0][3] * this->m[1][0] * this->m[3][2]
		+ this->m[0][3] * this->m[1][2] * this->m[3][0]
		+ this->m[0][2] * this->m[1][0] * this->m[3][3]
		+ this->m[0][0] * this->m[1][3] * this->m[3][2]
		) / i;
	result.m[1][3] = (
		+ this->m[0][0] * this->m[1][2] * this->m[2][3]
		+ this->m[0][2] * this->m[1][3] * this->m[2][0]
		+ this->m[0][3] * this->m[1][0] * this->m[2][2]
		- this->m[0][3] * this->m[1][2] * this->m[2][0]
		- this->m[0][2] * this->m[1][0] * this->m[2][3]
		- this->m[0][0] * this->m[1][3] * this->m[2][2]
		) / i;

	result.m[2][0] = (
		+ this->m[1][0] * this->m[2][1] * this->m[3][3]
		+ this->m[1][1] * this->m[2][3] * this->m[3][0]
		+ this->m[1][3] * this->m[2][0] * this->m[3][1]
		- this->m[1][3] * this->m[2][1] * this->m[3][0]
		- this->m[1][1] * this->m[2][0] * this->m[3][3]
		- this->m[1][0] * this->m[2][3] * this->m[3][1]
		) / i;
	result.m[2][1] = (
		- this->m[0][0] * this->m[2][1] * this->m[3][3]
		- this->m[0][1] * this->m[2][3] * this->m[3][0]
		- this->m[0][3] * this->m[2][0] * this->m[3][1]
		+ this->m[0][3] * this->m[2][1] * this->m[3][0]
		+ this->m[0][1] * this->m[2][0] * this->m[3][3]
		+ this->m[0][0] * this->m[2][3] * this->m[3][1]
		) / i;
	result.m[2][2] = (
		+ this->m[0][0] * this->m[1][1] * this->m[3][3]
		+ this->m[0][1] * this->m[1][3] * this->m[3][0]
		+ this->m[0][3] * this->m[1][0] * this->m[3][1]
		- this->m[0][3] * this->m[1][1] * this->m[3][0]
		- this->m[0][1] * this->m[1][0] * this->m[3][3]
		- this->m[0][0] * this->m[1][3] * this->m[3][1]
		) / i;
	result.m[2][3] = (
		- this->m[0][0] * this->m[1][1] * this->m[2][3]
		- this->m[0][1] * this->m[1][3] * this->m[2][0]
		- this->m[0][3] * this->m[1][0] * this->m[2][1]
		+ this->m[0][3] * this->m[1][1] * this->m[2][0]
		+ this->m[0][1] * this->m[1][0] * this->m[2][3]
		+ this->m[0][0] * this->m[1][3] * this->m[2][1]
		) / i;

	result.m[3][0] = (
		- this->m[1][0] * this->m[2][1] * this->m[3][2]
		- this->m[1][1] * this->m[2][2] * this->m[3][0]
		- this->m[1][2] * this->m[2][0] * this->m[3][1]
		+ this->m[1][2] * this->m[2][1] * this->m[3][0]
		+ this->m[1][1] * this->m[2][0] * this->m[3][2]
		+ this->m[1][0] * this->m[2][2] * this->m[3][1]
		) / i;
	result.m[3][1] = (
		+ this->m[0][0] * this->m[2][1] * this->m[3][2]
		+ this->m[0][1] * this->m[2][2] * this->m[3][0]
		+ this->m[0][2] * this->m[2][0] * this->m[3][1]
		- this->m[0][2] * this->m[2][1] * this->m[3][0]
		- this->m[0][1] * this->m[2][0] * this->m[3][2]
		- this->m[0][0] * this->m[2][2] * this->m[3][1]
		) / i;
	result.m[3][2] = (
		- this->m[0][0] * this->m[1][1] * this->m[3][2]
		- this->m[0][1] * this->m[1][2] * this->m[3][0]
		- this->m[0][2] * this->m[1][0] * this->m[3][1]
		+ this->m[0][2] * this->m[1][1] * this->m[3][0]
		+ this->m[0][1] * this->m[1][0] * this->m[3][2]
		+ this->m[0][0] * this->m[1][2] * this->m[3][1]
		) / i;
	result.m[3][3] = (
		+ this->m[0][0] * this->m[1][1] * this->m[2][2]
		+ this->m[0][1] * this->m[1][2] * this->m[2][0]
		+ this->m[0][2] * this->m[1][0] * this->m[2][1]
		- this->m[0][2] * this->m[1][1] * this->m[2][0]
		- this->m[0][1] * this->m[1][0] * this->m[2][2]
		- this->m[0][0] * this->m[1][2] * this->m[2][1]
		) / i;

	return result;
}

Matrix4x4 Matrix4x4::Transpose() const {
	Matrix4x4 result = {};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			result.m[y][x] = this->m[x][y];
		}
	}
	return result;
}

Matrix4x4 Matrix4x4::Inverse(const Matrix4x4& m) {
	Matrix4x4 result = {};

	float i =
		+m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]

		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]

		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]

		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]

		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]

		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]

		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]

		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];

	// 零除算回避用
	if (i == 0.0f) {
		assert(false);
	}

	result.m[0][0] = (
		+m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[1][1] * m.m[2][3] * m.m[3][2]
		) / i;
	result.m[0][1] = (
		-m.m[0][1] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[2][3] * m.m[3][2]
		) / i;
	result.m[0][2] = (
		+m.m[0][1] * m.m[1][2] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[3][2]
		) / i;
	result.m[0][3] = (
		-m.m[0][1] * m.m[1][2] * m.m[2][3]
		- m.m[0][2] * m.m[1][3] * m.m[2][1]
		- m.m[0][3] * m.m[1][1] * m.m[2][2]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2]
		) / i;

	result.m[1][0] = (
		-m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[1][3] * m.m[2][0] * m.m[3][2]
		+ m.m[1][3] * m.m[2][2] * m.m[3][0]
		+ m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[1][0] * m.m[2][3] * m.m[3][2]
		) / i;
	result.m[1][1] = (
		+m.m[0][0] * m.m[2][2] * m.m[3][3]
		+ m.m[0][2] * m.m[2][3] * m.m[3][0]
		+ m.m[0][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[2][2] * m.m[3][0]
		- m.m[0][2] * m.m[2][0] * m.m[3][3]
		- m.m[0][0] * m.m[2][3] * m.m[3][2]
		) / i;
	result.m[1][2] = (
		-m.m[0][0] * m.m[1][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][3] * m.m[3][0]
		- m.m[0][3] * m.m[1][0] * m.m[3][2]
		+ m.m[0][3] * m.m[1][2] * m.m[3][0]
		+ m.m[0][2] * m.m[1][0] * m.m[3][3]
		+ m.m[0][0] * m.m[1][3] * m.m[3][2]
		) / i;
	result.m[1][3] = (
		+m.m[0][0] * m.m[1][2] * m.m[2][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0]
		- m.m[0][2] * m.m[1][0] * m.m[2][3]
		- m.m[0][0] * m.m[1][3] * m.m[2][2]
		) / i;

	result.m[2][0] = (
		+m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[1][3] * m.m[2][0] * m.m[3][1]
		- m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[1][0] * m.m[2][3] * m.m[3][1]
		) / i;
	result.m[2][1] = (
		-m.m[0][0] * m.m[2][1] * m.m[3][3]
		- m.m[0][1] * m.m[2][3] * m.m[3][0]
		- m.m[0][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[2][1] * m.m[3][0]
		+ m.m[0][1] * m.m[2][0] * m.m[3][3]
		+ m.m[0][0] * m.m[2][3] * m.m[3][1]
		) / i;
	result.m[2][2] = (
		+m.m[0][0] * m.m[1][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][3] * m.m[3][0]
		+ m.m[0][3] * m.m[1][0] * m.m[3][1]
		- m.m[0][3] * m.m[1][1] * m.m[3][0]
		- m.m[0][1] * m.m[1][0] * m.m[3][3]
		- m.m[0][0] * m.m[1][3] * m.m[3][1]
		) / i;
	result.m[2][3] = (
		-m.m[0][0] * m.m[1][1] * m.m[2][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0]
		- m.m[0][3] * m.m[1][0] * m.m[2][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1]
		) / i;

	result.m[3][0] = (
		-m.m[1][0] * m.m[2][1] * m.m[3][2]
		- m.m[1][1] * m.m[2][2] * m.m[3][0]
		- m.m[1][2] * m.m[2][0] * m.m[3][1]
		+ m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[1][1] * m.m[2][0] * m.m[3][2]
		+ m.m[1][0] * m.m[2][2] * m.m[3][1]
		) / i;
	result.m[3][1] = (
		+m.m[0][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[2][1] * m.m[3][0]
		- m.m[0][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][0] * m.m[2][2] * m.m[3][1]
		) / i;
	result.m[3][2] = (
		-m.m[0][0] * m.m[1][1] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[3][0]
		- m.m[0][2] * m.m[1][0] * m.m[3][1]
		+ m.m[0][2] * m.m[1][1] * m.m[3][0]
		+ m.m[0][1] * m.m[1][0] * m.m[3][2]
		+ m.m[0][0] * m.m[1][2] * m.m[3][1]
		) / i;
	result.m[3][3] = (
		+m.m[0][0] * m.m[1][1] * m.m[2][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0]
		- m.m[0][1] * m.m[1][0] * m.m[2][2]
		- m.m[0][0] * m.m[1][2] * m.m[2][1]
		) / i;

	return result;
}

Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& m) {
	Matrix4x4 result = {};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			result.m[y][x] = m.m[x][y];
		}
	}
	return result;
}

Matrix4x4 Matrix4x4::Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			result.m[y][x] = m1.m[y][x] + m2.m[y][x];
		}
	}
	return result;
}

Matrix4x4 Matrix4x4::Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			result.m[y][x] = m1.m[y][x] - m2.m[y][x];
		}
	}
	return result;
}

Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& m1, const Matrix4x4& m2)  {
	Matrix4x4 result = {};

	for (int i = 0; i < 4; i++) {
		result.m[i][0] = m1.m[i][0] * m2.m[0][0] + m1.m[i][1] * m2.m[1][0] + m1.m[i][2] * m2.m[2][0] + m1.m[i][3] * m2.m[3][0];
		result.m[i][1] = m1.m[i][0] * m2.m[0][1] + m1.m[i][1] * m2.m[1][1] + m1.m[i][2] * m2.m[2][1] + m1.m[i][3] * m2.m[3][1];
		result.m[i][2] = m1.m[i][0] * m2.m[0][2] + m1.m[i][1] * m2.m[1][2] + m1.m[i][2] * m2.m[2][2] + m1.m[i][3] * m2.m[3][2];
		result.m[i][3] = m1.m[i][0] * m2.m[0][3] + m1.m[i][1] * m2.m[1][3] + m1.m[i][2] * m2.m[2][3] + m1.m[i][3] * m2.m[3][3];
	}

	return result;
}

Matrix4x4 Matrix4x4::MakeIdentity4x4() {
	Matrix4x4 result = {};
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			if (x == y) {
				result.m[y][x] = 1.0f;
			} else {
				result.m[y][x] = 0.0f;
			}
		}
	}
	return result;
}

Matrix4x4 Matrix4x4::MakeScaleMatrix(const Vector3& translate) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = translate.x;
	result.m[1][1] = translate.y;
	result.m[2][2] = translate.z;

	return result;
}

Matrix4x4 Matrix4x4::MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

Matrix4x4 Matrix4x4::MakeRotateXMatrix(const float& radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[1][1] = cos(radian);
	result.m[2][1] = -sin(radian);
	result.m[1][2] = sin(radian);
	result.m[2][2] = cos(radian);

	return result;
}

Matrix4x4 Matrix4x4::MakeRotateYMatrix(const float& radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = cos(radian);
	result.m[2][0] = sin(radian);
	result.m[0][2] = -sin(radian);
	result.m[2][2] = cos(radian);

	return result;
}

Matrix4x4 Matrix4x4::MakeRotateZMatrix(const float& radian) {
	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = cos(radian);
	result.m[1][0] = -sin(radian);
	result.m[0][1] = sin(radian);
	result.m[1][1] = cos(radian);

	return result;
}
