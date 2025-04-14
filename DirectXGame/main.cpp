#include <Windows.h>

#include "KamataEngine.h"
#include "GameScene.h"

using namespace KamataEngine;//usingは、kamataEngineの下に書く
DirectXCommon* dxCommon = DirectXCommon::GetInstance();//DirectX12のクラスは、DirectXCommonにする

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	//エンジンの初期化
	KamataEngine::Initialize(L"LE2D_22_マチダ_ユウタ_AL3");//名前を入れると実行画面の左上に名前が表示される

    //ゲームシーンのインタンス生成
	GameScene* gameScene = new GameScene();

	//ゲームシーンの初期化
	gameScene->Initialize();

	//メインループ
	while (true)
	{
		//エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		//ゲームシーンの更新
		gameScene->Update();

		//描画開始
		dxCommon->PreDraw();

		//ゲームシーンの描画
		gameScene->Draw();

		dxCommon->PostDraw();

	}

	//ゲームシーンの解放
	delete gameScene;

	//nullptrの代入
	gameScene = nullptr;

	//エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}
