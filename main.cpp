#include <Novice.h>
#include "Class/Base/MyMath.h"

const char kWindowTitle[] = "LC1A_22_マツモトユウタ_3次元ベクトルの作成";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 v1 = { 1.0f,3.0f,-5.0f };
	Vector3 v2 = { 4.0f,-1.0f,2.0f };
	float k = 4.0f;
	k;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, v1 + v2, "   :Add");
		VectorScreenPrintf(0, 20, v1 - v2, "   :Subtract");
		VectorScreenPrintf(0, 40, v1 * k, "   :Multiply");
		Novice::ScreenPrintf(0, 60, "%.02f :Dot", Dot(v1, v2));
		Novice::ScreenPrintf(0, 80, "%.02f :Length", Length(v1));
		VectorScreenPrintf(0, 100, Normalize(v2), "   :Normalize");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
