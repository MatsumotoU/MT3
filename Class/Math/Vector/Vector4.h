#pragma once
class Vector4 final{
public:
	float x;
	float y;
	float z;
	float w;

public:
	Vector4 operator-()const { return { -x, -y, -z, -w }; };

	Vector4 operator+(const Vector4& other) const { return { x + other.x, y + other.y, z + other.z , w + other.w }; }
	Vector4 operator-(const Vector4& other) const { return { x - other.x, y - other.y, z - other.z , w - other.w }; }
	Vector4 operator*(const Vector4& other) const { return { x * other.x, y * other.y, z * other.z , w * other.w }; }
	Vector4 operator/(const Vector4& other) const { return { x / other.x, y / other.y, z / other.z , w / other.w }; }
	Vector4 operator=(const Vector4& other) { return { x = other.x, y = other.y, z = other.z , w = other.w }; }
	Vector4 operator+=(const Vector4& other) { return { x += other.x, y += other.y, z += other.z ,w += other.w }; }
	Vector4 operator-=(const Vector4& other) { return { x -= other.x, y -= other.y, z -= other.z ,w -= other.w }; }
	Vector4 operator*=(const Vector4& other) { return { x *= other.x, y *= other.y, z *= other.z ,w *= other.w }; }
	Vector4 operator/=(const Vector4& other) { return { x /= other.x, y /= other.y, z /= other.z ,w /= other.w }; }

	Vector4 operator+(const float& other) { return { x + other,y + other,z + other , w + other}; };
	Vector4 operator-(const float& other) { return { x - other,y - other,z - other , w - other }; };
	Vector4 operator/(const float& other) { return { x / other,y / other,z / other , w / other }; };
	Vector4 operator*(const float& other) { return { x * other,y * other,z * other , w * other }; };

public:
	/// <summary>
	/// 4�����x�N�g���̒��������߂�
	/// </summary>
	/// <returns>4�����x�N�g���̒���</returns>
	[[nodiscard]] float Length() const;

	/// <summary>
	/// ���K�����ꂽ4�����x�N�g�������߂�
	/// </summary>
	/// <returns>���K�����ꂽ4�����x�N�g��</returns>
	[[nodiscard]] Vector4 Normalize() const;
};

