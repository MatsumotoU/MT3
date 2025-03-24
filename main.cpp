#include <Novice.h>
#include "Class/Math/MyMath.h"

const char kWindowTitle[] = "LC1A_22_マツモトユウタ_ポリゴンを書こう";

const int kRowHeight = 22;
const int kColumnWidth = 60;

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

const Vector3 kLocalVertices[3] = {
	{0.0f,32.0f,0.0f},{32.0f,-32.0f,0.0f},{-32.0f,-32.0f,0.0f}
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Vector3::Cross(v1,v2);

	Vector3 rotate{};
	Vector3 translate{};
	Vector3 cameraPosition{};
	cameraPosition.z = -200.0f;

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

		if (keys[DIK_W]) {
			translate.z += 1.0f;
		}

		if (keys[DIK_A]) {
			translate.x -= 1.0f;
		}

		if (keys[DIK_S]) {
			translate.z -= 1.0f;
		}

		if (keys[DIK_D]) {
			translate.x += 1.0f;
		}

		rotate.y += 0.1f;

		Matrix4x4 worldMatrix = Matrix4x4::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = Matrix4x4::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
		Matrix4x4 viewMatrix = Matrix4x4::Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = Matrix4x4::MakePerspectiveFovMatrix(0.45f, static_cast<float>(kWindowWidth) / static_cast<float>(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Matrix4x4::Multiply(worldMatrix, Matrix4x4::Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = Matrix4x4::MakeViewportMatrix(0, 0, static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight), 0.0f, 1.0f);
		Vector3 screenVertices[3]{};
		for (uint32_t i = 0; i < 3; ++i) {
			Vector3 ndcVertex = Vector3::Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Vector3::Transform(ndcVertex, viewportMatrix);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, cross, "Cross");

		if (Vector3::Cross(screenVertices[0], Vector3::Cross(screenVertices[1], screenVertices[2])).z < 0.0f) {
			Novice::DrawTriangle(
				static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
				static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
				static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
				RED, kFillModeSolid);
		}

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
