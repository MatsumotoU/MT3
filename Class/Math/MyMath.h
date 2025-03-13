#pragma once
#include"MathInclude.h"

unsigned int ColorFade(unsigned int color, float alpha);

template <typename T>
T Clamp(T t, T min, T max) {

	if (t > max) {
		return max;
	} else if (t < min) {
		return min;
	}
	return t;
};
template <typename T>
void ptrClamp(T* t, T min, T max){

	if (*t > max) {
		*t = max;
	} else if (*t < min) {
		*t = min;
	}
};
int ScopeVar(int var, int min, int max);

Vector2 RotatePos(Vector2 anker, float angle, float length);

Vector2 BezierCurve(Vector2 a, Vector2 b, Vector2 c, float pow,float t);

void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix);
void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix);
void VectorScreenPrintf(int x, int y, Vector3 vector3,const char* str);
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* str);