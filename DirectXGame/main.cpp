#include <Windows.h>
#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"

using namespace KamataEngine;                           // usingは、kamataEngineの下に書く
DirectXCommon* dxCommon = DirectXCommon::GetInstance(); // DirectX12のクラスは、DirectXCommonにする
                                                        // シーン(型)
enum class Scene {
	kUnknown = 0,

	kTitle,
	kGame,
};

// 現在シーン(型)
Scene scene = Scene::kUnknown;
GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;

void ChangeScene();
// 終了フラグ
bool finished_ = false;

void UpdateScene();

void DrawScene();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KamataEngine::Initialize(L"LE2D_22_マチダ_ユウタ_AL3"); // 名前を入れると実行画面の左上に名前が表示される

	// ゲームシーンのインタンス生成
	gameScene = new GameScene();
	titleScene = new TitleScene();
	// ゲームシーンの初期化
	gameScene->Initialize();
	titleScene->Initialize();
	scene = Scene::kTitle;

	
	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		
	    //シーン切り替え
		ChangeScene();
		 //現在シーン更新
		UpdateScene();
	    

		// ゲームシーンの更新

		// 描画開始
		dxCommon->PreDraw();

		// 現在シーンの描画
		DrawScene();

		// ゲームシーンの描画
		dxCommon->PostDraw();
	}
	// ゲームシーンの解放
	delete gameScene;
	delete titleScene;
	

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}

void ChangeScene() {
	switch (scene) 
	{
	case Scene::kTitle:
		if(titleScene->IsFinished()) 
		{
		
			// シーン変更
			scene = Scene::kGame;
			// 旧シーンの解放
			delete titleScene;
			titleScene = nullptr;
			// 新シーンの生成と初期化
			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->IsFinished()) 
		{

			if (gameScene->IsCleared()) {
			//シーン変更
			scene = Scene::kTitle;
			//旧シーンの解放
			delete gameScene;
			gameScene = nullptr;
			//新シーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();

			} else {

			// シーン変更
			scene = Scene::kTitle;
			// 旧シーンの解放
			delete gameScene;
			gameScene = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		    }
		}
		break;
	}
}

void UpdateScene() {
	switch (scene) 
	{
	case Scene::kTitle:

		titleScene->Update();

		break;
	case Scene::kGame:

		gameScene->Update();
		break;
	case Scene::kUnknown:
		titleScene->Draw();
		break;
	}
}

void DrawScene() 
{
	switch (scene) {
	case Scene::kTitle:

		titleScene->Draw();

		break;
	case Scene::kGame:

		gameScene->Draw();
		break;
	case Scene::kUnknown:
		titleScene->Draw();
		break;
	}
}
