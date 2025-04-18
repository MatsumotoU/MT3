#pragma once
#include"MathInclude.h"
/// <summary>
/// center/radius/subdivision/color
/// </summary>
struct Sphere
{
	Vector3 center;
	float radius;
	int subdivision;
};

struct AABB
{
	Vector3 min;
	Vector3 max;
};

struct OBB
{
	Vector3 center;
	Vector3 orientations[3];
	Vector3 size;
};

struct Plane
{
	Vector3 normal; // 法線
	float distance; // 距離
};

struct Triangle {
	Vector3 vertices[3];
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

struct Spring
{
	Vector3 anchor;
	float naturalLength;
	float stiffness;// 剛性
	float dampingCoefficient;// 減衰係数
};

struct Ball
{
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float mass;
	float radius;
	unsigned int color;
};

struct Pendulm
{
	Vector3 anchor;
	float length;
	float angle;
	float angularVelocity;
	float angularAcceleration;
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

void DrawSegment(const Segment& segment,const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
void DrawAxis(int x, int y, int size, const Vector3& cameraRotate);
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawBezier(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawCatmullRom(const std::vector<Vector3>& controlPoints, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

int ColisionSphere(const Sphere& sphere1, const Sphere& sphere2);
int ColisionPlaneToSphere(const Plane& plane, const Sphere& sphere);

int isCollision(const Segment& segment, const Plane& plane);
int isCollision(const Segment& segment, const Triangle& triangle);
int isCollision(const AABB& aabb1, const AABB& aabb2);
int isCollision(const AABB& aabb, const Sphere& sphere);
int isCollision(const AABB& aabb, const Segment& segment);
int isCollision(const OBB& obb, const Sphere& sphere);
int isCollision(const OBB& obb, const Segment& segment);
int isCollision(const OBB& obb1, const OBB& obb2);