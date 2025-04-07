#include "MyMath.h"
#include <Novice.h>
#include <assert.h>
#include <numbers>
#include <algorithm>

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

void DrawAxis(int x, int y, int size, const Vector3& cameraRotate) {
	Vector3 axes[3]{};
	axes[0] = { 1.0f,0.0f,0.0f };
	axes[1] = { 0.0f,-1.0f,0.0f };
	axes[2] = { 0.0f,0.0f,-1.0f };

	Matrix4x4 cameraRotateMatrix = Matrix4x4::MakeAffineMatrix({1.0f,1.0f,1.0f},{cameraRotate.x,-cameraRotate.y,cameraRotate.z}, {0.0f,0.0f,0.0f});
	cameraRotateMatrix = Matrix4x4::Inverse(cameraRotateMatrix);
	for (int32_t index = 0; index < 3; ++index) {
		axes[index] = Vector3::Transform(axes[index], cameraRotateMatrix) * static_cast<float>(size);
	}

	Novice::DrawBox(x - (size + 16), y - (size + 16), (size + 16) * 2, (size + 16) * 2, 0.0f, 0x232323AF, kFillModeSolid);
	Novice::DrawBox(x - (size + 16), y - (size + 16), (size + 16) * 2, (size + 16) * 2, 0.0f, WHITE, kFillModeWireFrame);

	Novice::ScreenPrintf(x + static_cast<int>(axes[0].x), y + static_cast<int>(axes[0].y), "X");
	Novice::ScreenPrintf(x + static_cast<int>(axes[1].x), y + static_cast<int>(axes[1].y), "Y");
	Novice::ScreenPrintf(x + static_cast<int>(axes[2].x), y + static_cast<int>(axes[2].y), "Z");

	Novice::DrawLine(
		x, y,
		x + static_cast<int>(axes[0].x), y + static_cast<int>(axes[0].y),
		RED);
	Novice::DrawLine(
		x, y,
		x + static_cast<int>(axes[1].x), y + static_cast<int>(axes[1].y),
		GREEN);
	Novice::DrawLine(
		x, y,
		x + static_cast<int>(axes[2].x), y + static_cast<int>(axes[2].y),
		BLUE);
}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 p[3]{};
	for (int32_t index = 0; index < 3; ++index) {
		p[index] = Vector3::Transform(Vector3::Transform(triangle.vertices[index], viewProjectionMatrix), viewportMatrix);
	}

	for (int32_t index = 0; index < 3; ++index) {
		Novice::DrawLine(
			static_cast<int>(p[index].x), static_cast<int>(p[index].y),
			static_cast<int>(p[(index + 1) % 3].x), static_cast<int>(p[(index + 1) % 3].y),
			static_cast<unsigned int>(color));
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

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 p[8]{};
	p[0] = aabb.min;
	p[1] = { aabb.min.x,aabb.max.y,aabb.min.z };
	p[2] = { aabb.min.x,aabb.max.y,aabb.max.z };
	p[3] = { aabb.min.x,aabb.min.y,aabb.max.z };
	
	p[4] = { aabb.max.x,aabb.min.y,aabb.min.z };
	p[5] = { aabb.max.x,aabb.max.y,aabb.min.z };
	p[6] = aabb.max;
	p[7] = { aabb.max.x,aabb.min.y,aabb.max.z };

	for (int32_t index = 0; index < 8; ++index) {
		p[index] = Vector3::Transform(Vector3::Transform(p[index], viewProjectionMatrix), viewportMatrix);
	}

	for (int32_t index = 0; index < 4; ++index) {
		Novice::DrawLine(
			static_cast<int>(p[index].x), static_cast<int>(p[index].y),
			static_cast<int>(p[(index + 1) % 4].x), static_cast<int>(p[(index + 1) % 4].y),
			static_cast<unsigned int>(color));
		Novice::DrawLine(
			static_cast<int>(p[index + 4].x), static_cast<int>(p[index + 4].y),
			static_cast<int>(p[(index + 1) % 4 + 4].x), static_cast<int>(p[(index + 1) % 4 + 4].y),
			static_cast<unsigned int>(color));
		Novice::DrawLine(
			static_cast<int>(p[index].x), static_cast<int>(p[index].y),
			static_cast<int>(p[(index + 4)].x), static_cast<int>(p[(index + 4)].y),
			static_cast<unsigned int>(color));
	}
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
	
	return false;
}

int isCollision(const Segment& segment, const Triangle& triangle) {

	Vector3 v01 = triangle.vertices[1] - triangle.vertices[0];
	Vector3 v12 = triangle.vertices[2] - triangle.vertices[1];
	Vector3 v20 = triangle.vertices[0] - triangle.vertices[2];

	Plane plane{};
	plane.normal = Vector3::Cross(v01, v12).Normalize();
	plane.distance = plane.normal.x * triangle.vertices[0].x + plane.normal.y * triangle.vertices[0].y + plane.normal.z * triangle.vertices[0].z;

	// 平面上の当たり判定
	float dot = Vector3::Dot(plane.normal, segment.diff);
	// 並行回避
	if (dot == 0.0f) {
		return false;
	}
	float t = (plane.distance - Vector3::Dot(segment.origin, plane.normal)) / dot;
	if (t < 0.0f || segment.diff.Length() < t) {
		return false;
	}

	Vector3 p = segment.origin + segment.diff * t;

	Vector3 v0p = p - triangle.vertices[0];
	Vector3 v1p = p - triangle.vertices[1];
	Vector3 v2p = p - triangle.vertices[2];

	Vector3 cross01 = Vector3::Cross(v01, v1p);
	Vector3 cross12 = Vector3::Cross(v12, v2p);
	Vector3 cross20 = Vector3::Cross(v20, v0p);

	if (
		Vector3::Dot(cross01, plane.normal) >= 0.0f &&
		Vector3::Dot(cross12, plane.normal) >= 0.0f &&
		Vector3::Dot(cross20, plane.normal) >= 0.0f) {

		return true;
	}
	return false;
}

int isCollision(const AABB& aabb1, const AABB& aabb2) {
	if (
		(aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	}
	return false;
}

int isCollision(const AABB& aabb, const Sphere& sphere) {
	Vector3 closestPoint{
		std::clamp(sphere.center.x,aabb.min.x,aabb.max.x),
		std::clamp(sphere.center.y,aabb.min.y,aabb.max.y),
		std::clamp(sphere.center.z,aabb.min.z,aabb.max.z) };
	float distance = (closestPoint - sphere.center).Length();
	if (distance <= sphere.radius) {
		return true;
	}
	return false;
}
