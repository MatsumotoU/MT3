#pragma once

// �O���錾
class Matrix4x4;

class Vector3 final{
public:
	float x;
	float y;
	float z;

public:
	Vector3 operator-()const { return { -x, -y, -z }; };

	Vector3 operator+(const Vector3& other) { return { x + other.x, y + other.y, z + other.z }; }
	Vector3 operator-(const Vector3& other) { return { x - other.x, y - other.y, z - other.z }; }
	Vector3 operator*(const Vector3& other) { return { x * other.x, y * other.y, z * other.z }; }
	Vector3 operator/(const Vector3& other) { return { x / other.x, y / other.y, z / other.z }; }
	Vector3 operator=(const Vector3& other) { return { x = other.x, y = other.y, z = other.z }; }
	Vector3 operator+=(const Vector3& other) { return { x += other.x, y += other.y, z += other.z }; }
	Vector3 operator-=(const Vector3& other) { return { x -= other.x, y -= other.y, z -= other.z }; }
	Vector3 operator*=(const Vector3& other) { return { x *= other.x, y *= other.y, z *= other.z }; }
	Vector3 operator/=(const Vector3& other) { return { x /= other.x, y /= other.y, z /= other.z }; }

	Vector3 operator+(const float& other) { return { x + other,y + other,z + other }; };
	Vector3 operator-(const float& other) { return { x - other,y - other,z - other }; };
	Vector3 operator/(const float& other) { return { x / other,y / other,z / other }; };
	Vector3 operator*(const float& other) { return { x * other,y * other,z * other }; };

public:
	/// <summary>
	/// 3�����x�N�g���̒��������߂�
	/// </summary>
	/// <returns>3�����x�N�g���̒���</returns>
	[[nodiscard]] float Length() const;

	/// <summary>
	/// ���K�����ꂽ3�����x�N�g�������߂�
	/// </summary>
	/// <returns>���K�����ꂽ3�����x�N�g��</returns>
	[[nodiscard]] Vector3 Normalize() const;

public:
	/// <summary>
	/// 2��3�����x�N�g���̓��ς����߂�
	/// </summary>
	/// <param name="v1">1�ڂ�3�����x�N�g��</param>
	/// <param name="v2">2�ڂ�3�����x�N�g��</param>
	/// <returns>2��3�����x�N�g���̓���</returns>
	[[nodiscard]] float Dot(const Vector3& v1, const Vector3& v2);

public:
	/// <summary>
	/// ���[���h���W�ɕϊ�����
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
};
