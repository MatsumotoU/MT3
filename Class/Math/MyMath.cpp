#include "MyMath.h"
#include <Novice.h>
#include <assert.h>
#include <numbers>

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 result{};
	result = segment.origin + Vector3::Project(point - segment.origin, segment.diff);
	return result;
}

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

void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 origine = Vector3::Transform(Vector3::Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 endPoint = Vector3::Transform(Vector3::Transform(segment.origin + segment.diff, viewProjectionMatrix), viewportMatrix);
	Novice::DrawLine(
		static_cast<int>(origine.x), static_cast<int>(origine.y),
		static_cast<int>(endPoint.x), static_cast<int>(endPoint.y),
		color);
}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / static_cast<float>(kSubdivision);

	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		Vector3 beginPos{ 
			-kGridEvery * (static_cast<float>(kSubdivision) / 2.0f) ,
			0.0f,
			kGridEvery * static_cast<float>(xIndex) - kGridEvery * (static_cast<float>(kSubdivision) / 2.0f) };

		Vector3 endPos{ 
			kGridEvery * (static_cast<float>(kSubdivision) / 2.0f) ,
			0.0f,
			kGridEvery * static_cast<float>(xIndex) - kGridEvery * (static_cast<float>(kSubdivision) / 2.0f) };

		Vector3 ndcVertex = Vector3::Transform(beginPos, viewProjectionMatrix);
		beginPos = Vector3::Transform(ndcVertex, viewportMatrix);

		ndcVertex = Vector3::Transform(endPos, viewProjectionMatrix);
		endPos = Vector3::Transform(ndcVertex, viewportMatrix);

		if (xIndex == kSubdivision/2) {
			Novice::DrawLine(
				static_cast<int>(beginPos.x), static_cast<int>(beginPos.y),
				static_cast<int>(endPos.x), static_cast<int>(endPos.y),
				0x232323FF);
		} else {
			Novice::DrawLine(
				static_cast<int>(beginPos.x), static_cast<int>(beginPos.y),
				static_cast<int>(endPos.x), static_cast<int>(endPos.y),
				0xAAAAAAFF);
		}
	}
	
	// 左から右への線を順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		Vector3 beginPos{ 
			kGridEvery * static_cast<float>(zIndex)  - kGridEvery * (static_cast<float>(kSubdivision) / 2.0f),
			0.0f,
			kGridEvery * (static_cast<float>(kSubdivision) / 2.0f) };

		Vector3 endPos{ 
			kGridEvery * static_cast<float>(zIndex) - kGridEvery * (static_cast<float>(kSubdivision) / 2.0f) ,
			0.0f,
			-kGridEvery * (static_cast<float>(kSubdivision) / 2.0f) };

		Vector3 ndcVertex = Vector3::Transform(beginPos, viewProjectionMatrix);
		beginPos = Vector3::Transform(ndcVertex, viewportMatrix);

		ndcVertex = Vector3::Transform(endPos, viewProjectionMatrix);
		endPos = Vector3::Transform(ndcVertex, viewportMatrix);

		if (zIndex == kSubdivision / 2) {
			Novice::DrawLine(
				static_cast<int>(beginPos.x), static_cast<int>(beginPos.y),
				static_cast<int>(endPos.x), static_cast<int>(endPos.y),
				0x232323FF);
		} else {
			Novice::DrawLine(
				static_cast<int>(beginPos.x), static_cast<int>(beginPos.y),
				static_cast<int>(endPos.x), static_cast<int>(endPos.y),
				0xAAAAAAFF);
		}
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	assert(sphere.subdivision >= 0);

	const uint32_t kSubdivision = static_cast<uint32_t>(sphere.subdivision);
	const float pi = std::numbers::pi_v<float>;
	const float kLonEvery = pi / static_cast<float>(kSubdivision) * 2;
	const float kLatEvery = (pi * 2.0f) / static_cast<float>(kSubdivision) * 2;
	// 緯度の方向に分割
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * static_cast<float>(latIndex);// 現在の緯度
		float nextLat = (2.0f * pi) / static_cast<float>(kSubdivision) * 2.0f;

		// 経度の方向に分割
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lot = kLonEvery * static_cast<float>(lonIndex);// 現在の緯度
			float nextLot = pi / static_cast<float>(kSubdivision) * 2.0f;

			Vector3 a{}, b{}, c{};
			a = { 
				cosf(lot) * cosf(lat),
				sinf(lot),
				cosf(lot) * sinf(lat) };
			b = { 
				cosf(lot + nextLot) * cosf(lat),
				sinf(lot + nextLot),
				cosf(lot + nextLot) * sinf(lat)};
			c = {
				cosf(lot) * cosf(lat + nextLat),
				sinf(lot),
				cosf(lot) * sinf(lat + nextLat) };

			// 半径分でかくする
			a = a * sphere.radius;
			b = b * sphere.radius;
			c = c * sphere.radius;

			// ワールド座標系生成
			Matrix4x4 worldMatrix = Matrix4x4::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, sphere.center);
			Matrix4x4 worldViewProjectionMatrix = Matrix4x4::Multiply(worldMatrix, viewProjectionMatrix);

			// スクリーン座標系へ変換
			Vector3 ndcVertex = Vector3::Transform(a, worldViewProjectionMatrix);
			a = Vector3::Transform(ndcVertex, viewportMatrix);
			ndcVertex = Vector3::Transform(b, worldViewProjectionMatrix);
			b = Vector3::Transform(ndcVertex, viewportMatrix);
			ndcVertex = Vector3::Transform(c, worldViewProjectionMatrix);
			c = Vector3::Transform(ndcVertex, viewportMatrix);

			// 描画
			Novice::DrawLine(
				static_cast<int>(a.x), static_cast<int>(a.y),
				static_cast<int>(b.x), static_cast<int>(b.y),
				static_cast<unsigned int>(color));
			Novice::DrawLine(
				static_cast<int>(a.x), static_cast<int>(a.y),
				static_cast<int>(c.x), static_cast<int>(c.y),
				static_cast<unsigned int>(color));

		}
	}
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 center = plane.normal * plane.distance;

	Vector3 perpendiculars[4]{};
	perpendiculars[0] = Vector3::Normalize(Vector3::Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y ,-perpendiculars[0].z };
	perpendiculars[2] = Vector3::Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y ,-perpendiculars[2].z };
	Vector3 points[4]{};
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = perpendiculars[index] * 2.0f;
		Vector3 point = center + extend;
		points[index] = Vector3::Transform(Vector3::Transform(point, viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawLine(
		static_cast<int>(points[0].x), static_cast<int>(points[0].y),
		static_cast<int>(points[3].x), static_cast<int>(points[3].y),
		static_cast<unsigned int>(color));
	Novice::DrawLine(
		static_cast<int>(points[1].x), static_cast<int>(points[1].y),
		static_cast<int>(points[2].x), static_cast<int>(points[2].y),
		static_cast<unsigned int>(color));
	Novice::DrawLine(
		static_cast<int>(points[2].x), static_cast<int>(points[2].y),
		static_cast<int>(points[0].x), static_cast<int>(points[0].y),
		static_cast<unsigned int>(color));
	Novice::DrawLine(
		static_cast<int>(points[3].x), static_cast<int>(points[3].y),
		static_cast<int>(points[1].x), static_cast<int>(points[1].y),
		static_cast<unsigned int>(color));

	
}

int ColisionSphere(const Sphere& sphere1, const Sphere& sphere2) {
	if ((sphere1.center - sphere2.center).Length() <= sphere1.radius + sphere2.radius) {
		return true;
	} else {
		return false;
	}
}

int ColisionPlaneToSphere(const Plane& plane, const Sphere& sphere) {
	float length = fabsf(Vector3::Dot(plane.normal, sphere.center) - (plane.normal * plane.distance).Length());
	return length <= sphere.radius;
}

int isCollision(const Segment& segment, const Plane& plane) {
	float dot = Vector3::Dot(plane.normal, segment.diff);
	// 並行回避
	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - Vector3::Dot(segment.origin, plane.normal)) / dot;

	if (t >= 0.0f && segment.diff.Length() >= t) {
		return true;
	}
	Novice::ScreenPrintf(0, 0, "%f", t);
	return false;
}