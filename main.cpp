#include <Novice.h>
#include <imgui.h>
#include <string>
#include "Class/Math/MyMath.h"

const char kWindowTitle[] = "LE2A_14_マツモトユウタ_振り子を作ってみよう";

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
	Pendulm pendulm{};
	pendulm.anchor = { 0.0f,1.0f,0.0f };
	pendulm.length = 0.8f;
	pendulm.angle = 0.7f;
	pendulm.angularVelocity = 0.0f;
	pendulm.angularAcceleration = 0.0f;

	Ball ball{};
	ball.position = { 0.0f,0.0f,0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = WHITE;
	
	Vector3 c{};
	Vector3 p{};
	Vector3 v{};
	Vector3 a{};

	int isSimulate = false;
	float deltaTime = 1.0f / 60.0f;

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

		// オブジェクト操作
		if (isSimulate) {
			pendulm.angularAcceleration = -(9.8f / pendulm.length) * std::sin(pendulm.angle);
			pendulm.angularVelocity += pendulm.angularAcceleration * deltaTime;
			pendulm.angle += pendulm.angularVelocity * deltaTime;
			//angle += angularVelocity / 60.0f;
			p.x = pendulm.anchor.x + std::sin(pendulm.angle) * pendulm.length;
			p.y = pendulm.anchor.y - std::cos(pendulm.angle) * pendulm.length;
			p.z = pendulm.anchor.z;

			v = { -pendulm.length * pendulm.angularVelocity * std::sin(pendulm.angle), pendulm.length * pendulm.angularVelocity * std::cos(pendulm.angle),0.0f };
			a = (p - pendulm.anchor) * -pow(pendulm.angularVelocity, 2.0f);

			ball.position = p;

			/*ball.velocity = v;
			ball.acceleration = a;

			ball.velocity += ball.acceleration * deltaTime;
			ball.position += ball.velocity * deltaTime;*/
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

		if (ImGui::Button("Start")) {
			isSimulate = true;
		}

		if (ImGui::Button("StepSimulate")) {
			
		}

		ImGui::DragFloat3("ballPos", &ball.position.x,0.1f);
		ImGui::DragFloat3("ballVel", &ball.velocity.x, 0.1f);
		ImGui::DragFloat3("ballAcc", &ball.acceleration.x, 0.1f);
		ImGui::DragFloat("ballMass", &ball.mass, 0.1f);
		
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		Segment segment{};
		segment.origin = pendulm.anchor;
		segment.diff = ball.position - pendulm.anchor;
		DrawSegment(segment, viewProjectionMatrix, viewportMatrix, WHITE);

		Sphere sphere{};
		sphere.center = ball.position;
		sphere.radius = 0.1f;
		sphere.subdivision = 16;
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, ball.color);

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