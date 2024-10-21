#include <Novice.h>
#include "TitleScene.h"
#include "gamescene.h"
#include "GameClear.h"
#include "GameOver.h"

const char kWindowTitle[] = "LE2B_14_サノ_ハヤテ_タイトル";

enum class Scenes {
	Title, Game, Clear, Over
};
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// シーン管理用の変数
	Scenes currentScene = Scenes::Title;

	TitleScene titleScene;
	gamescene gameScene;
	GameClear gameClearScene;
	GameOver gameOverScene;

	titleScene.Initialize();
	gameScene.Initialize();
	gameClearScene.Initialize();
	gameOverScene.Initialize();

	Novice::ConsolePrintf("Title Scene: Press SPACE to Start\n");
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();
		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		/// ↓更新処理ここから
		switch (currentScene) {
		case Scenes::Title:
			titleScene.Update();
			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
				currentScene = Scenes::Game;
				Novice::ConsolePrintf("Game Scene: Press 1 for Clear, 2 for Over\n");
			}
			break;
		case Scenes::Game:
			gameScene.Update();
			if (preKeys[DIK_1] == 0 && keys[DIK_1] != 0) {
				currentScene = Scenes::Clear;
				Novice::ConsolePrintf("Game Clear: Press SPACE to return to Title\n");
			}
			if (preKeys[DIK_2] == 0 && keys[DIK_2] != 0) {
				currentScene = Scenes::Over;
				Novice::ConsolePrintf("Game Over: Press SPACE to return to Title\n");
			}
			break;
		case Scenes::Clear:
			gameClearScene.Update();
			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
				currentScene = Scenes::Title;
				Novice::ConsolePrintf("Title Scene: Press SPACE to Start\n");
			}
			break;

		case Scenes::Over:
			gameOverScene.Update();
			if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
				currentScene = Scenes::Title;
				Novice::ConsolePrintf("Title Scene: Press SPACE to Start\n");
			}
			break;
		}
		/// ↑更新処理ここまで

		/// ↓描画処理ここから

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
