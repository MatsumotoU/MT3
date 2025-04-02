#pragma once

// 前方宣言
class Matrix4x4;

class Vector3 final {
public:
	float x;
	float y;
	float z;

public:
	Vector3 operator-()const { return { -x, -y, -z }; };

	Vector3 operator+(const Vector3& other) const { return { x + other.x, y + other.y, z + other.z }; }
	Vector3 operator-(const Vector3& other) const { return { x - other.x, y - other.y, z - other.z }; }
	Vector3 operator*(const Vector3& other) const { return { x * other.x, y * other.y, z * other.z }; }
	Vector3 operator/(const Vector3& other) const { return { x / other.x, y / other.y, z / other.z }; }
	Vector3 operator=(const Vector3& other) { return { x = other.x, y = other.y, z = other.z }; }
	Vector3 operator+=(const Vector3& other) { return { x += other.x, y += other.y, z += other.z }; }
	Vector3 operator-=(const Vector3& other) { return { x -= other.x, y -= other.y, z -= other.z }; }
	Vector3 operator*=(const Vector3& other) { return { x *= other.x, y *= other.y, z *= other.z }; }
	Vector3 operator/=(const Vector3& other) { return { x /= other.x, y /= other.y, z /= other.z }; }

	Vector3 operator+(const float& other) const { return { x + other,y + other,z + other }; };
	Vector3 operator-(const float& other) const { return { x - other,y - other,z - other }; };
	Vector3 operator/(const float& other) const { return { x / other,y / other,z / other }; };
	Vector3 operator*(const float& other) const { return { x * other,y * other,z * other }; };

public:
	/// <summary>
	/// 3次元ベクトルの長さを求める
	/// </summary>
	/// <returns>3次元ベクトルの長さ</returns>
	[[nodiscard]] float Length() const;

	/// <summary>
	/// 正規化された3次元ベクトルを求める
	/// </summary>
	/// <returns>正規化された3次元ベクトル</returns>
	[[nodiscard]] Vector3 Normalize() const;

public:
	/// <summary>
	/// 2つの3次元ベクトルの内積を求める
	/// </summary>
	/// <param name="v1">1つ目の3次元ベクトル</param>
	/// <param name="v2">2つ目の3次元ベクトル</param>
	/// <returns>2つの3次元ベクトルの内積</returns>
	[[nodiscard]] static float Dot(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 2つの3次元ベクトルの外積を求める
	/// </summary>
	/// <param name="v1">1つ目の3次元ベクトル</param>
	/// <param name="v2">2つ目の3次元ベクトル</param>
	/// <returns>2つの3次元ベクトルの外積</returns>
	[[nodiscard]] static Vector3 Cross(const Vector3& v1, const Vector3& v2);

public:
	/// <summary>
	/// ワールド座標に変換する
	/// </summary>
	/// <param name="vector">変換元ローカル座標</param>
	/// <param name="matrix">変換に使用する行列</param>
	/// <returns>ワールド座標</returns>
	[[nodiscard]] static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

public:
	/// <summary>
	/// 正射影ベクトルを求める
	/// </summary>
	/// <param name="v1">1つ目の3次元ベクトル</param>
	/// <param name="v2">2つ目の3次元ベクトル</param>
	/// <returns>正射影ベクトル</returns>
	[[nodiscard]] static Vector3 Project(const Vector3& v1, const Vector3& v2);
};







