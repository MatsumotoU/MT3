#pragma once
#include"MathInclude.h"

struct Sphere
{
	Vector3 center;
	float radius;
	int subdivision;
	unsigned int color;
};

struct Plane
{
	Vector3 normal; // 法線
	float distance; // 距離
};

/// <summary>
/// 直線
/// </summary>
struct Line
{
	Vector3 origin; // 始点
	Vector3 diff; // 終点への差分ベクトル
};

/// <summary>
/// 半直線
/// </summary>
struct Ray
{
	Vector3 origin; //!< 始点
	Vector3 diff; //!< 終点への差分ベクトル
};

/// <summary>
/// 線分
/// </summary>
struct Segment
{
	Vector3 origin; //!< 始点
	Vector3 diff; //!< 終点への差分ベクトル
};


/// <summary>
/// 最近接点を求める
/// </summary>
/// <param name="point">対象となる点の位置</param>
/// <param name="segment">対象とする線分</param>
/// <returns>最近接点</returns>
[[nodiscard]] Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

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

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

int ColisionSphere(const Sphere& sphere1, const Sphere& sphere2);
int ColisionPlaneToSphere(const Plane& plane, const Sphere& sphere);