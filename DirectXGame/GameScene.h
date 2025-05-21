#pragma once
#include<vector>
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include "MapChippField.h"


class GameScene {
public:
	// 初期化
	void Initialize();

	void GenerateBlocks();

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_; // stdでエラーが起きたらKamataEngine::をいれる

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//デバックカメラ有効
	bool isDebugCameraActive_ = false;

	//デバックカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr; 

	//デバックカメラの生成
	//debugCamera_ = new DebugCamera();

	// 3Dモデル
	KamataEngine::Model* modelskydome_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	// 自キャラ
	Player* player_ = nullptr;

	//キューブ
	Skydome* skydome_ = nullptr;

	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;
	
	//3D
	KamataEngine::Model* cube_ = nullptr;

	//マップチップフィールド
	MapChipField* mapChipField_;


	//デストラクタ
	~GameScene();


	//更新
	void Update();

	//描画
	void Draw();

};



