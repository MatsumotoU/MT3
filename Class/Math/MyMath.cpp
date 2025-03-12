#include "MyMath.h"
#include <Novice.h>
#include <assert.h>

unsigned int ColorFade(unsigned int color, float alpha) {

	unsigned int maskColor = 0xFFFFFF00 & color;

	return maskColor | static_cast<int>(alpha * 255);;
}

int reClamp(int t, int min, int max) {
	if (t >= max) {
		return max;
	} else if (t <= min) {
		return min;
	}
	return t;
}

Vector2 RotatePos(Vector2 anker, float angle, float length) {
	Vector2 result;
	result.x = anker.x + (cosf(angle) - sinf(angle)) * length;
	result.x = anker.x + (cosf(angle) + sinf(angle)) * length;

	return result;
}

int ScopeVar(int var, int min, int max) {

	if (var >= min && var <= max) {
		return true;
	} else {
		return false;
	}
}

unsigned int FadeColor(unsigned int color, float alpha) {

	unsigned int rgbColor = color & 0xFFFFFF00;
	return  rgbColor | static_cast<int>(alpha * 255);
}

Vector2 BezierCurve(Vector2 a, Vector2 b, Vector2 c, float pow, float t) {
	Vector2 result = { 0 };
	ptrClamp(&t, 0.0f, 1.0f);

	result.x = (powf(1.0f - t, pow) * a.x) +
		(pow * (1.0f - t) * t * b.x) +
		powf(t, pow) * c.x;

	result.y = (powf(1.0f - t, pow) * a.y) +
		(pow * (1.0f - t) * t * b.y) +
		powf(t, pow) * c.y;

	return result;
}

void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix) {
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			Novice::ScreenPrintf(x + column * 64, y + row * 20,
				"%.02f", matrix.m[row][column]);
		}
	}
}

void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix) {
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			Novice::ScreenPrintf(x + column * 64, y + row * 20,
				"%.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, Vector3 vector3, const char* str) {
	Novice::ScreenPrintf(x, y, "%.2f %.2f %.2f %s", vector3.x, vector3.y, vector3.z, str);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* str) {
	Novice::ScreenPrintf(x, y, str);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * 64, y + (row + 1) * 20,
				"%.02f", matrix.m[row][column]);
		}
	}
}
