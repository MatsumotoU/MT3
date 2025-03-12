#pragma once

// �O���錾
class Vector3;

struct Matrix4x4 final{
	float m[4][4];

public:
	Matrix4x4 operator+(const Matrix4x4& other) const;
	Matrix4x4 operator-(const Matrix4x4& other) const;
	Matrix4x4 operator*(const Matrix4x4& other) const;

public:
	/// <summary>
	/// ���̍s��̋t�s������߂�
	/// </summary>
	/// <returns>���̍s��̋t�s��</returns>
	[[discard]] Matrix4x4 Inverse() const;

	/// <summary>
	/// ���̍s��̓]�n�s������߂�
	/// </summary>
	/// <returns>���̍s��̓]�n�s��</returns>
	[[discard]] Matrix4x4 Transpose() const;

public:
	/// <summary>
	/// 4x4�̋t�s������߂�
	/// </summary>
	/// <param name="m">4x4�̍s��</param>
	/// <returns>4x4�̋t�s��</returns>
	[[discard]] static Matrix4x4 Inverse(const Matrix4x4& m);

	/// <summary>
	/// 4x4�̓]�u�s������߂�
	/// </summary>
	/// <param name="m">4x4�̍s��</param>
	/// <returns>4x4�̓]�u�s��</returns>
	[[discard]] static Matrix4x4 Transpose(const Matrix4x4& m);

public:
	/// <summary>
	/// 2��4x4�s��̉��Z���ʂ����߂�
	/// </summary>
	/// <param name="m1">1�ڂ�4x4�s��</param>
	/// <param name="m2">2�ڂ�4x4�s��</param>
	/// <returns>2��4x4�s��̉��Z����</returns>
	[[discard]] static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 2��4x4�s��̌��Z���ʂ����߂�
	/// </summary>
	/// <param name="m1">1�ڂ�4x4�s��</param>
	/// <param name="m2">2�ڂ�4x4�s��</param>
	/// <returns>2��4x4�s��̌��Z����</returns>
	[[discard]] static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 2��4x4�s��̏�Z���ʂ����߂�
	/// </summary>
	/// <param name="m1">1�ڂ�4x4�s��</param>
	/// <param name="m2">2�ڂ�4x4�s��</param>
	/// <returns>2��4x4�s��̏�Z����</returns>
	[[discard]] static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

public:
	/// <summary>
	/// 4x4�̒P�ʍs������߂�
	/// </summary>
	/// <returns>4x4�̒P�ʍs��</returns>
	[[discard]] static Matrix4x4 MakeIdentity4x4();

public:
	/// <summary>
	/// �g��k���s����쐬����
	/// </summary>
	/// <param name="scale">�g��k���̏��</param>
	/// <returns>�g��k���s��</returns>
	[[discard]] static Matrix4x4 MakeScaleMatrix(const Vector3& translate);

	/// <summary>
	/// �ړ��s����쐬����
	/// </summary>
	/// <param name="translate">�ړ��ʂ̏��</param>
	/// <returns>�ړ��s��</returns>
	[[discard]] static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
};