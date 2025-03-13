#pragma once

// 前方宣言
class Vector3;

class Matrix4x4 final{
public:
	float m[4][4];

public:
	Matrix4x4 operator+(const Matrix4x4& other) const;
	Matrix4x4 operator-(const Matrix4x4& other) const;
	Matrix4x4 operator*(const Matrix4x4& other) const;

public:
	/// <summary>
	/// この行列の逆行列を求める
	/// </summary>
	/// <returns>この行列の逆行列</returns>
	[[nodiscard]] Matrix4x4 Inverse() const;

	/// <summary>
	/// この行列の転地行列を求める
	/// </summary>
	/// <returns>この行列の転地行列</returns>
	[[nodiscard]] Matrix4x4 Transpose() const;

public:
	/// <summary>
	/// 4x4の逆行列を求める
	/// </summary>
	/// <param name="m">4x4の行列</param>
	/// <returns>4x4の逆行列</returns>
	[[nodiscard]] static Matrix4x4 Inverse(const Matrix4x4& m);

	/// <summary>
	/// 4x4の転置行列を求める
	/// </summary>
	/// <param name="m">4x4の行列</param>
	/// <returns>4x4の転置行列</returns>
	[[nodiscard]] static Matrix4x4 Transpose(const Matrix4x4& m);

public:
	/// <summary>
	/// 2つの4x4行列の加算結果を求める
	/// </summary>
	/// <param name="m1">1つ目の4x4行列</param>
	/// <param name="m2">2つ目の4x4行列</param>
	/// <returns>2つの4x4行列の加算結果</returns>
	[[nodiscard]] static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 2つの4x4行列の減算結果を求める
	/// </summary>
	/// <param name="m1">1つ目の4x4行列</param>
	/// <param name="m2">2つ目の4x4行列</param>
	/// <returns>2つの4x4行列の減算結果</returns>
	[[nodiscard]] static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 2つの4x4行列の乗算結果を求める
	/// </summary>
	/// <param name="m1">1つ目の4x4行列</param>
	/// <param name="m2">2つ目の4x4行列</param>
	/// <returns>2つの4x4行列の乗算結果</returns>
	[[nodiscard]] static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

public:
	/// <summary>
	/// 4x4の単位行列を求める
	/// </summary>
	/// <returns>4x4の単位行列</returns>
	[[nodiscard]] static Matrix4x4 MakeIdentity4x4();

public:
	/// <summary>
	/// 拡大縮小行列を作成する
	/// </summary>
	/// <param name="scale">拡大縮小の情報</param>
	/// <returns>拡大縮小行列</returns>
	[[nodiscard]] static Matrix4x4 MakeScaleMatrix(const Vector3& translate);

	/// <summary>
	/// 移動行列を作成する
	/// </summary>
	/// <param name="translate">移動量の情報</param>
	/// <returns>移動行列</returns>
	[[nodiscard]] static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	/// <summary>
	/// X軸の回転行列を作成する
	/// </summary>
	/// <param name="radian">ラジアン</param>
	/// <returns>X軸の回転行列</returns>
	[[nodiscard]] static Matrix4x4 MakeRotateXMatrix(const float& radian);

	/// <summary>
	/// Y軸の回転行列を作成する
	/// </summary>
	/// <param name="radian">ラジアン</param>
	/// <returns>X軸の回転行列</returns>
	[[nodiscard]] static Matrix4x4 MakeRotateYMatrix(const float& radian);

	/// <summary>
	/// Z軸の回転行列を作成する
	/// </summary>
	/// <param name="radian">ラジアン</param>
	/// <returns>X軸の回転行列</returns>
	[[nodiscard]] static Matrix4x4 MakeRotateZMatrix(const float& radian);
};