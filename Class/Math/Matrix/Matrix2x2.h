#pragma once
class Matrix2x2 final{
public:
	float m[2][2];

public:

	/// <summary>
	/// ���̍s��̓]�n�s������߂�
	/// </summary>
	/// <returns>���̍s��̓]�n�s��</returns>
	[[discard]] Matrix2x2 Transpose() const;

public:

	/// <summary>
	/// 2x2�̓]�u�s������߂�
	/// </summary>
	/// <param name="m">2x2�̍s��</param>
	/// <returns>2x2�̓]�u�s��</returns>
	[[discard]] static Matrix2x2 Transpose(const Matrix2x2& m);

public:
	/// <summary>
	/// 2��2x2�s��̉��Z���ʂ����߂�
	/// </summary>
	/// <param name="m1">1�ڂ�2x2�s��</param>
	/// <param name="m2">2�ڂ�2x2�s��</param>
	/// <returns>2��2x2�s��̉��Z����</returns>
	[[discard]] static Matrix2x2 Add(const Matrix2x2& m1, const Matrix2x2& m2);

	/// <summary>
	/// 2��2x2�s��̌��Z���ʂ����߂�
	/// </summary>
	/// <param name="m1">1�ڂ�2x2�s��</param>
	/// <param name="m2">2�ڂ�2x2�s��</param>
	/// <returns>2��2x2�s��̌��Z����</returns>
	[[discard]] static Matrix2x2 Subtract(const Matrix2x2& m1, const Matrix2x2& m2);

public:
	/// <summary>
	/// 2x2�̒P�ʍs������߂�
	/// </summary>
	/// <returns>2x2�̒P�ʍs��</returns>
	[[discard]] static Matrix2x2 MakeIdentity2x2();
};