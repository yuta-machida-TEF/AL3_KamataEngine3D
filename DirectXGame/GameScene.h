#pragma once
#include "KamataEngine.h"
#include "Player.h"


class GameScene
{
public:
	//初期化
	void Initialize();

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//3Dモデル
	KamataEngine::Model* model_ = nullptr;

	//ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	//カメラ
	KamataEngine::Camera camera_;

	//スプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	//自キャラ
	Player* player_ = nullptr;

	
	//デストラクタ
	~GameScene();


	//更新
	void Update();

	//描画
	void Draw();

};



