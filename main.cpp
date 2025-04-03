#include <Novice.h>
#include <imgui.h>
#include "Class/Math/MyMath.h"

const char kWindowTitle[] = "LE2A_14_マツモトユウタ_3次元衝突判定";

const int kRowHeight = 22;
const int kColumnWidth = 60;

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };

	Sphere sphere1{ {0.0f,0.0f,0.0f},1.0f,32,WHITE };
	Sphere sphere2{ {0.0f,0.0f,0.0f},0.5f,32,WHITE };

	// マウス操作用
	Vector3 cursorTranslate{};
	Vector3 cursorRotate{};
	Vector3 cursorScale{1.0f,1.0f,1.0f};
	Vector2 cursorMoveDir{};
	int cursorPosX = 0;
	int cursorPosY = 0;
	int oldCursorPosX = cursorPosX;
	int oldCursorPosY = cursorPosY;
	float moveSpeed = 0.05f;

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

		// カーソルの移動方向取得
		oldCursorPosX = cursorPosX;
		oldCursorPosY = cursorPosY;
		Novice::GetMousePosition(&cursorPosX, &cursorPosY);
		cursorMoveDir = {
			static_cast<float>(oldCursorPosX - cursorPosX),
			static_cast<float>(oldCursorPosY - cursorPosY)
		};
		cursorMoveDir = cursorMoveDir.Normalize();

		// 回転
		if (Novice::IsPressMouse(2)) {
			cursorRotate.y += (-cursorMoveDir.x * moveSpeed);
			cursorRotate.x += (cursorMoveDir.y * moveSpeed);
		}

		// 平行移動
		if (Novice::IsPressMouse(1)) {
			cursorTranslate.x += (cursorMoveDir.x * moveSpeed);
			cursorTranslate.y += (-cursorMoveDir.y * moveSpeed);
		}

		// 拡大縮小
		if (Novice::GetWheel() > 0) {
			cursorScale.x -= moveSpeed;
			cursorScale.y -= moveSpeed;
			cursorScale.z -= moveSpeed;
		}
		if (Novice::GetWheel() < 0) {
			cursorScale.x += moveSpeed;
			cursorScale.y += moveSpeed;
			cursorScale.z += moveSpeed;
		}
		Matrix4x4 cursorMatrix = Matrix4x4::MakeAffineMatrix(cursorScale, cursorRotate, cursorTranslate);

		// ビュープロジェクション行列とビューポート行列
		Matrix4x4 cameraMatrix = Matrix4x4::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		cameraMatrix = Matrix4x4::Multiply(cameraMatrix,cursorMatrix );
		Matrix4x4 viewMatrix = Matrix4x4::Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = Matrix4x4::MakePerspectiveFovMatrix(0.45f, static_cast<float>(kWindowWidth) / static_cast<float>(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewportMatrix = Matrix4x4::MakeViewportMatrix(0, 0, static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight), 0.0f, 1.0f);
		Matrix4x4 viewProjectionMatrix = Matrix4x4::Multiply(viewMatrix, projectionMatrix);

		// 当たり判定
		if ((sphere1.center - sphere2.center).Length() <= sphere1.radius + sphere2.radius) {
			sphere1.color = RED;
		} else {
			sphere1.color = WHITE;
		}

		// ImGui
		ImGui::Begin("CameraWindow");

		ImGui::Text("CameraMove: MouseRightCrick + Move");
		ImGui::Text("CameraRotate: MouseMidleCrick + Move");
		ImGui::Text("CameraScale: MouseMidleWheel+-");

		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat("MoveSpeed", &moveSpeed, 0.01f, 0.0f, 1.0f);
		if (ImGui::Button("ResetCarera")) {
			cursorTranslate = { 0.0f,0.0f,0.0f };
			cursorRotate = { 0.0f,0.0f,0.0f };
			cursorScale = { 1.0f,1.0f,1.0f };
		}

		ImGui::End();

		// 線分の情報
		ImGui::Begin("SegmentWindow");

		ImGui::Text("Sphere1");
		ImGui::DragFloat3("Sphere1_Translate", &sphere1.center.x,0.01f);
		ImGui::DragFloat("Sphere1_Radius", &sphere1.radius, 0.01f);

		ImGui::Text("Sphere2");
		ImGui::DragFloat3("Sphere2_Translate", &sphere2.center.x, 0.01f);
		ImGui::DragFloat("Sphere2_Radius", &sphere2.radius, 0.01f);

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, sphere1.color);
		DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, sphere2.color);

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