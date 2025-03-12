#pragma once

// �O���錾
class Vector2;

class Matrix3x3 final{
public:
	float m[3][3];

public:
	Matrix3x3 operator+(const Matrix3x3& other);
	Matrix3x3 operator-(const Matrix3x3& other);
	Matrix3x3 operator*(const Matrix3x3& other);

public:
	/// <summary>
	/// ���̍s��̋t�s������߂�
	/// </summary>
	/// <returns>���̍s��̋t�s��</returns>
	[[discard]] Matrix3x3 Inverse() const;

	/// <summary>
	/// ���̍s��̓]�n�s������߂�
	/// </summary>
	/// <returns>���̍s��̓]�n�s��</returns>
	[[discard]] Matrix3x3 Transpose() const;

public:
	/// <summary>
	/// 3x3�̋t�s������߂�
	/// </summary>
	/// <param name="m">3x3�̍s��</param>
	/// <returns>3x3�̋t�s��</returns>
	[[discard]] static Matrix3x3 Inverse(const Matrix3x3& m);

	/// <summary>
	/// 3x3�̓]�u�s������߂�
	/// </summary>
	/// <param name="m">3x3�̍s��</param>
	/// <returns>3x3�̓]�u�s��</returns>
	[[discard]] static Matrix3x3 Transpose(const Matrix3x3& m);

public:
	/// <summary>
	/// 2��3x3�s��̉��Z���ʂ����߂�
	/// </summary>
	/// <param name="m1">1�ڂ�3x3�s��</param>
	/// <param name="m2">2�ڂ�3x3�s��</param>
	/// <returns>2��3x3�s��̉��Z����</returns>
	[[discard]] static Matrix3x3 Add(const Matrix3x3& m1, const Matrix3x3& m2);

	/// <summary>
	/// 2��3x3�s��̌��Z���ʂ����߂�
	/// </summary>
	/// <param name="m1">1�ڂ�3x3�s��</param>
	/// <param name="m2">2�ڂ�3x3�s��</param>
	/// <returns>2��3x3�s��̌��Z����</returns>
	[[discard]] static Matrix3x3 Subtract(const Matrix3x3& m1, const Matrix3x3& m2);

	/// <summary>
	/// 2��3x3�s��̏�Z���ʂ����߂�
	/// </summary>
	/// <param name="m1">1�ڂ�3x3�s��</param>
	/// <param name="m2">2�ڂ�3x3�s��</param>
	/// <returns>2��3x3�s��̏�Z����</returns>
	[[discard]] static Matrix3x3 Multiply(const Matrix3x3& m1, const Matrix3x3& m2);

public:
	/// <summary>
	/// 3x3�̒P�ʍs������߂�
	/// </summary>
	/// <returns>3x3�̒P�ʍs��</returns>
	[[discard]] static Matrix3x3 MakeIdentity3x3();

public:
	/// <summary>
	/// �g��k���s����쐬����
	/// </summary>
	/// <param name="scale">�g��k���̏��</param>
	/// <returns>�g��k���s��</returns>
	[[discard]] Matrix3x3 MakeScaleMatrix(const Vector2& scale) const;

	/// <summary>
	/// ��]�s����쐬����
	/// </summary>
	/// <param name="theta">���W�A��</param>
	/// <returns>��]�s��</returns>
	[[discard]] Matrix3x3 MakeRotateMatrix(const float& theta) const;

	/// <summary>
	/// �ړ��s����쐬����
	/// </summary>
	/// <param name="translate">�ړ��ʂ̏��</param>
	/// <returns>�ړ��s��</returns>
	[[discard]] Matrix3x3 MakeTranslateMatrix(const Vector2& translate) const;

	/// <summary>
	/// �A�t�B���s����쐬����
	/// </summary>
	/// <param name="scale">�g��k���̏��</param>
	/// <param name="rotate">���W�A��</param>
	/// <param name="translate">�ړ��ʂ̏��</param>
	/// <returns>�A�t�B���s��</returns>
	[[discard]] Matrix3x3 MakeAffineMatrix(const Vector2& scale, const float& rotate, const Vector2& translate) const;

public:
	/// <summary>
	/// ���ˉe�s����쐬����
	/// </summary>
	/// <param name="left">��ʂ̍��[���W</param>
	/// <param name="top">��ʂ̏�[���W</param>
	/// <param name="right">��ʂ̉E�[���W</param>
	/// <param name="bottom">��ʂ̉��[���W</param>
	/// <returns>���ˉe�s��</returns>
	[[discard]] Matrix3x3 MakeOrthographicMatrix(const float& left, const float& top, const float& right, const float& bottom) const;

	/// <summary>
	/// �r���[�|�[�g�s����쐬����
	/// </summary>
	/// <param name="left">��ʂ̍��[���W</param>
	/// <param name="top">��ʂ̏�[���W</param>
	/// <param name="width">��ʂ̉E�[���W</param>
	/// <param name="height">��ʂ̉��[���W</param>
	/// <returns>�r���[�|�[�g�s��</returns>
	[[discard]] Matrix3x3 MakeViewportMatrix(const float& left, const float& top, const float& width, const float& height) const;

	/// <summary>
	/// ���[���h�r���[�v���W�F�N�V�����s����쐬����
	/// </summary>
	/// <param name="worldMatrix">���[���h�s��</param>
	/// <param name="viewMatrix">�r���[�s��</param>
	/// <param name="orthoMatrix">���ˉe�s��</param>
	/// <param name="viewportMatrix">�r���[�|�[�g�s��</param>
	/// <returns>���[���h�r���[�v���W�F�N�V�����s��</returns>
	[[discard]] Matrix3x3 MakeWvpVpMatrix(const Matrix3x3& worldMatrix, const Matrix3x3& viewMatrix, const Matrix3x3& orthoMatrix, const Matrix3x3& viewportMatrix) const;
};