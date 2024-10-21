#include <Novice.h>
#include "WallcollisionDirection.h"

const char kWindowTitle[] = "LE2B_14_サノ_ハヤテ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	WallcollisionDirection wallEffect;
	wallEffect.Initialize();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		/// ↓更新処理ここから
		/// 
		wallEffect.Update();

		// 仮にスペースキーが押されたらエフェクトを発生させる
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			// 壁の座標 (仮に画面の中央)
			wallEffect.OnCollision(640.0f, 360.0f);
		}
		/// ↑更新処理ここまで
		
		/// ↓描画処理ここから
		wallEffect.Draw();
		/// 
		/// ↑描画処理ここまで
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
