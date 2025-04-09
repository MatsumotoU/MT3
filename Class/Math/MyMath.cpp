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

		if (xIndex == kSubdivision / 2) {
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
			kGridEvery * static_cast<float>(zIndex) - kGridEvery * (static_cast<float>(kSubdivision) / 2.0f),
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

	Matrix4x4 cameraRotateMatrix = Matrix4x4::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { cameraRotate.x,-cameraRotate.y,cameraRotate.z }, { 0.0f,0.0f,0.0f });
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
				cosf(lot + nextLot) * sinf(lat) };
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

void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Matrix4x4 rotateMatrix{};
	rotateMatrix.m[3][3] = 1.0f;
	for (int32_t index = 0; index < 3; ++index) {
		rotateMatrix.m[index][0] = obb.orientations[index].x;
		rotateMatrix.m[index][1] = obb.orientations[index].y;
		rotateMatrix.m[index][2] = obb.orientations[index].z;
	}
	Matrix4x4 transformMatrix = Matrix4x4::MakeTranslateMatrix(obb.center);

	Vector3 p[8]{};
	p[0] = -obb.size;
	p[1] = { -obb.size.x, +obb.size.y, -obb.size.z };
	p[2] = { -obb.size.x, +obb.size.y, +obb.size.z };
	p[3] = { -obb.size.x, -obb.size.y, +obb.size.z };

	p[4] = { +obb.size.x, -obb.size.y, -obb.size.z };
	p[5] = { +obb.size.x, +obb.size.y, -obb.size.z };
	p[6] = obb.size;
	p[7] = { +obb.size.x, -obb.size.y, +obb.size.z };

	for (int32_t index = 0; index < 8; ++index) {
		p[index] = Vector3::Transform(Vector3::Transform(p[index], rotateMatrix), transformMatrix);
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

int isCollision(const AABB& aabb, const Segment& segment) {
	Plane plane[6]{};
	plane[0].normal = { 1.0f,0.0f,0.0f };
	plane[0].distance = aabb.min.x;
	plane[1].normal = { 1.0f,0.0f,0.0f };
	plane[1].distance = aabb.max.x;

	plane[2].normal = { 0.0f,1.0f,0.0f };
	plane[2].distance = aabb.min.y;
	plane[3].normal = { 0.0f,1.0f,0.0f };
	plane[3].distance = aabb.max.y;

	plane[4].normal = { 0.0f,0.0f,1.0f };
	plane[4].distance = aabb.min.z;
	plane[5].normal = { 0.0f,0.0f,1.0f };
	plane[5].distance = aabb.max.z;

	float dot = Vector3::Dot(plane[0].normal, segment.diff);
	float tXmin = (plane[0].distance - Vector3::Dot(segment.origin, plane[0].normal)) / dot;
	dot = Vector3::Dot(plane[1].normal, segment.diff);
	float tXmax = (plane[1].distance - Vector3::Dot(segment.origin, plane[1].normal)) / dot;
	dot = Vector3::Dot(plane[2].normal, segment.diff);
	float tYmin = (plane[2].distance - Vector3::Dot(segment.origin, plane[2].normal)) / dot;
	dot = Vector3::Dot(plane[3].normal, segment.diff);
	float tYmax = (plane[3].distance - Vector3::Dot(segment.origin, plane[3].normal)) / dot;
	dot = Vector3::Dot(plane[4].normal, segment.diff);
	float tZmin = (plane[4].distance - Vector3::Dot(segment.origin, plane[4].normal)) / dot;
	dot = Vector3::Dot(plane[5].normal, segment.diff);
	float tZmax = (plane[5].distance - Vector3::Dot(segment.origin, plane[5].normal)) / dot;

	float tNearX = min(tXmin, tXmax);
	float tFarX = max(tXmin, tXmax);
	float tNearY = min(tYmin, tYmax);
	float tFarY = max(tYmin, tYmax);
	float tNearZ = min(tZmin, tZmax);
	float tFarZ = max(tZmin, tZmax);

	float tmin = max(max(tNearX, tNearY), tNearZ);
	float tmax = min(min(tFarX, tFarY), tFarZ);
	if (tmin <= tmax) {
		if (tmin >= 0.0f && segment.diff.Length() >= tmin ||
			tmax >= 0.0f && segment.diff.Length() >= tmax) {
			return true;
		} else {
			AABB hitBox{ segment.origin,segment.origin + segment.diff };
			return isCollision(hitBox, aabb);
		}
	}
	return false;
}

int isCollision(const OBB& obb, const Sphere& sphere) {
	Matrix4x4 rotateMatrix{};
	rotateMatrix.m[3][3] = 1.0f;
	for (int32_t index = 0; index < 3; ++index) {
		rotateMatrix.m[index][0] = obb.orientations[index].x;
		rotateMatrix.m[index][1] = obb.orientations[index].y;
		rotateMatrix.m[index][2] = obb.orientations[index].z;
	}
	Matrix4x4 transformMatrix = Matrix4x4::MakeTranslateMatrix(obb.center);
	Matrix4x4 obbWorldMatrix = Matrix4x4::Multiply(rotateMatrix, transformMatrix);

	Matrix4x4 obbWorldMatrixInvers = Matrix4x4::Inverse(obbWorldMatrix);
	Vector3 centerInOBBLocalSpace = Vector3::Transform(sphere.center, obbWorldMatrixInvers);

	AABB aabbOBBLocal{ -obb.size,obb.size };
	Sphere sphereOBBLocal{ centerInOBBLocalSpace ,sphere.radius,16,WHITE };
	return isCollision(aabbOBBLocal,sphereOBBLocal);
}

int isCollision(const OBB& obb, const Segment& segment) {
	Matrix4x4 rotateMatrix{};
	rotateMatrix.m[3][3] = 1.0f;
	for (int32_t index = 0; index < 3; ++index) {
		rotateMatrix.m[index][0] = obb.orientations[index].x;
		rotateMatrix.m[index][1] = obb.orientations[index].y;
		rotateMatrix.m[index][2] = obb.orientations[index].z;
	}
	Matrix4x4 transformMatrix = Matrix4x4::MakeTranslateMatrix(obb.center);
	Matrix4x4 obbWorldMatrix = Matrix4x4::Multiply(rotateMatrix, transformMatrix);

	Matrix4x4 obbWorldMatrixInvers = Matrix4x4::Inverse(obbWorldMatrix);
	Vector3 origineInOBBLocalSpace = Vector3::Transform(segment.origin, obbWorldMatrixInvers);

	AABB aabbOBBLocal{ -obb.size,obb.size };
	Segment segmentOBBLocal{ origineInOBBLocalSpace ,segment.diff };
	return isCollision(aabbOBBLocal, segmentOBBLocal);
}

int isCollision(const OBB& obb1, const OBB& obb2) {
	// 分離軸の候補を探す
	Vector3 separatingAxisCandidates[15]{};
	separatingAxisCandidates[0] = obb1.orientations[0];
	separatingAxisCandidates[1] = obb1.orientations[1];
	separatingAxisCandidates[2] = obb1.orientations[2];
	separatingAxisCandidates[3] = obb2.orientations[0];
	separatingAxisCandidates[4] = obb2.orientations[1];
	separatingAxisCandidates[5] = obb2.orientations[2];
	separatingAxisCandidates[6] = Vector3::Cross(obb1.orientations[0], obb2.orientations[0]);
	separatingAxisCandidates[7] = Vector3::Cross(obb1.orientations[0], obb2.orientations[1]);
	separatingAxisCandidates[8] = Vector3::Cross(obb1.orientations[0], obb2.orientations[2]);
	separatingAxisCandidates[9] = Vector3::Cross(obb1.orientations[1], obb2.orientations[0]);
	separatingAxisCandidates[10] = Vector3::Cross(obb1.orientations[1], obb2.orientations[1]);
	separatingAxisCandidates[11] = Vector3::Cross(obb1.orientations[1], obb2.orientations[2]);
	separatingAxisCandidates[12] = Vector3::Cross(obb1.orientations[2], obb2.orientations[0]);
	separatingAxisCandidates[13] = Vector3::Cross(obb1.orientations[2], obb2.orientations[1]);
	separatingAxisCandidates[14] = Vector3::Cross(obb1.orientations[2], obb2.orientations[2]);

	// obb1の各頂点
	Matrix4x4 rotateMatrix{};
	rotateMatrix.m[3][3] = 1.0f;
	for (int32_t index = 0; index < 3; ++index) {
		rotateMatrix.m[index][0] = obb1.orientations[index].x;
		rotateMatrix.m[index][1] = obb1.orientations[index].y;
		rotateMatrix.m[index][2] = obb1.orientations[index].z;
	}
	Matrix4x4 transformMatrix = Matrix4x4::MakeTranslateMatrix(obb1.center);
	Vector3 p1[8]{};
	p1[0] = -obb1.size;
	p1[1] = { -obb1.size.x, +obb1.size.y, -obb1.size.z };
	p1[2] = { -obb1.size.x, +obb1.size.y, +obb1.size.z };
	p1[3] = { -obb1.size.x, -obb1.size.y, +obb1.size.z };
	p1[4] = { +obb1.size.x, -obb1.size.y, -obb1.size.z };
	p1[5] = { +obb1.size.x, +obb1.size.y, -obb1.size.z };
	p1[6] = obb1.size;
	p1[7] = { +obb1.size.x, -obb1.size.y, +obb1.size.z };
	for (int32_t index = 0; index < 8; ++index) {
		p1[index] = Vector3::Transform(Vector3::Transform(p1[index], rotateMatrix), transformMatrix);
	}
	// obb2の各頂点
	Matrix4x4 rotateMatrix2{};
	rotateMatrix2.m[3][3] = 1.0f;
	for (int32_t index = 0; index < 3; ++index) {
		rotateMatrix2.m[index][0] = obb2.orientations[index].x;
		rotateMatrix2.m[index][1] = obb2.orientations[index].y;
		rotateMatrix2.m[index][2] = obb2.orientations[index].z;
	}
	Matrix4x4 transformMatrix2 = Matrix4x4::MakeTranslateMatrix(obb2.center);
	Vector3 p2[8]{};
	p2[0] = -obb2.size;
	p2[1] = { -obb2.size.x, +obb2.size.y, -obb2.size.z };
	p2[2] = { -obb2.size.x, +obb2.size.y, +obb2.size.z };
	p2[3] = { -obb2.size.x, -obb2.size.y, +obb2.size.z };
	p2[4] = { +obb2.size.x, -obb2.size.y, -obb2.size.z };
	p2[5] = { +obb2.size.x, +obb2.size.y, -obb2.size.z };
	p2[6] = obb2.size;
	p2[7] = { +obb2.size.x, -obb2.size.y, +obb2.size.z };
	for (int32_t index = 0; index < 8; ++index) {
		p2[index] = Vector3::Transform(Vector3::Transform(p2[index], rotateMatrix2), transformMatrix2);
	}

	// 分離軸に対して投影して判定
	for (int32_t axisIndex = 0; axisIndex < 15; ++axisIndex) {
		float obb1P[8]{};
		float obb1Max = 0.0f;
		float obb1Min = 0.0f;
		float obb2P[8]{};
		float obb2Max = 0.0f;
		float obb2Min = 0.0f;
		for (int32_t index = 0; index < 8; ++index) {
			obb1P[index] = Vector3::Dot(separatingAxisCandidates[axisIndex], p1[index]);
			obb1Max = max(obb1P[index], obb1Max);
			obb1Min = min(obb1P[index], obb1Min);
			obb2P[index] = Vector3::Dot(separatingAxisCandidates[axisIndex], p2[index]);
			obb2Max = max(obb2P[index], obb2Max);
			obb2Min = min(obb2P[index], obb2Min);
		}

		Vector2 axis = { cosf(obb1Max),sinf(obb1Max) };

		float L1 = obb1Max - obb1Min;
		float L2 = obb2Max - obb2Min;
		Novice::ScreenPrintf(0,20+ 20 * axisIndex, "L1 = %.3f L2 = %.3f", L1,L2);

		float sumSpan = L1 + L2;
		float longSpan = max(obb1Max, obb2Max) - min(obb1Min, obb2Min);
		Novice::ScreenPrintf(400, 20 + 20 * axisIndex, "sumSpan = %.3f < longSpan = %.3f", sumSpan, longSpan);
		// 1つでも分離しているなら当たっていない
		if (sumSpan < longSpan) {
			Novice::ScreenPrintf(0, 0, "false = %d", axisIndex);
			return false;
		}
	}
	return true;
}
