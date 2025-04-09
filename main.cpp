#include <Novice.h>
#include <imgui.h>
#include "Class/Math/MyMath.h"

const char kWindowTitle[] = "LE2A_14_マツモトユウタ_3次元衝突判定_面と球";

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

	// 図形
	Segment segment{ {1.0f,0.0f,0.0f},{0.5f,0.5f,0.0f} };
	unsigned int hitColor = WHITE;
	Vector3 rotate{};
	OBB obb = {
		{-1.0f,0.0f,0.0f},
		{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},
		{0.5f,0.5f,0.5f}
	};

	Vector3 rotate1{};
	OBB obb1 = {
		{1.0f,1.0f,0.0f},
		{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}},
		{0.5f,0.5f,0.5f}
	};

	// マウス操作用
	Vector3 cursorTranslate{};
	Vector3 cursorRotate{};
	Vector3 cursorScale{ 1.0f,1.0f,1.0f };
	Vector2 cursorMoveDir{};
	int cursorPosX = 0;
	int cursorPosY = 0;
	int oldCursorPosX = cursorPosX;
	int oldCursorPosY = cursorPosY;
	float moveSpeed = 0.05f;

	// ワールド軸表示用
	bool isActiveAxis = true;
	int axisSize = 50;
	Vector2 axisTranslate = { 100.0f,620.0f };

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
		Matrix4x4 cursorMatrix = Matrix4x4::MakeAffineMatrix(cursorScale, cursorRotate, {0.0f,0.0f,0.0f});
		Matrix4x4 cursorTransMatrix = Matrix4x4::MakeAffineMatrix({1.0f,1.0f,1.0f}, {0.0f,0.0f,0.0f}, cursorTranslate);

		// ビュープロジェクション行列とビューポート行列
		Matrix4x4 cameraMatrix = Matrix4x4::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		cameraMatrix = Matrix4x4::Multiply(cameraMatrix, cursorTransMatrix);
		cameraMatrix = Matrix4x4::Multiply(cameraMatrix, cursorMatrix);
		Matrix4x4 viewMatrix = Matrix4x4::Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = Matrix4x4::MakePerspectiveFovMatrix(0.45f, static_cast<float>(kWindowWidth) / static_cast<float>(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewportMatrix = Matrix4x4::MakeViewportMatrix(0, 0, static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight), 0.0f, 1.0f);
		Matrix4x4 viewProjectionMatrix = Matrix4x4::Multiply(viewMatrix, projectionMatrix);

		// OBBの軸生成
		Matrix4x4 rotateMatrix = Matrix4x4::MakeRotateXYZMatrix(rotate);
		for (int32_t index = 0; index < 3; ++index) {
			obb.orientations[index].x = rotateMatrix.m[index][0];
			obb.orientations[index].y = rotateMatrix.m[index][1];
			obb.orientations[index].z = rotateMatrix.m[index][2];
		}

		rotateMatrix = Matrix4x4::MakeRotateXYZMatrix(rotate1);
		for (int32_t index = 0; index < 3; ++index) {
			obb1.orientations[index].x = rotateMatrix.m[index][0];
			obb1.orientations[index].y = rotateMatrix.m[index][1];
			obb1.orientations[index].z = rotateMatrix.m[index][2];
		}

		// 当たり判定
		if (isCollision(obb, obb1)) {
			hitColor = RED;
		} else {
			hitColor = WHITE;
		}

		// ImGui
		ImGui::Begin("OpWindow");
		if (ImGui::TreeNode("Camera")) {
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

			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Axis")) {
			ImGui::Checkbox("isActive", &isActiveAxis);
			ImGui::DragFloat2("AxisTranslate", &axisTranslate.x);
			ImGui::DragInt("AxisSize", &axisSize,0);
			ImGui::TreePop();
		}
		
		ImGui::End();

		// オブジェクトの情報
		ImGui::Begin("ObjectWindow");
		ImGui::DragFloat3("ObbCenter", &obb.center.x, 0.01f);
		ImGui::DragFloat3("ObbRotate", &rotate.x, 0.01f);
		ImGui::DragFloat3("ObbSize", &obb.size.x, 0.01f);

		ImGui::DragFloat3("Obb1Center", &obb1.center.x, 0.01f);
		ImGui::DragFloat3("Obb1Rotate", &rotate1.x, 0.01f);
		ImGui::DragFloat3("Obb1Size", &obb1.size.x, 0.01f);

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawOBB(obb, viewProjectionMatrix, viewportMatrix, hitColor);
		DrawOBB(obb1, viewProjectionMatrix, viewportMatrix, hitColor);

		if (isActiveAxis) {
			DrawAxis(static_cast<int>(axisTranslate.x), static_cast<int>(axisTranslate.y), axisSize, cursorRotate + cameraRotate);
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