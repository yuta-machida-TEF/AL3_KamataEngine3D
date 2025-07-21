#pragma once
#include "CameraController.h"
#include "Enemy.h"
#include "KamataEngine.h"
#include "MapChipField.h"
#include "Player.h"
#include "Skydome.h"
#include <vector>
#include "DeathParticles.h"

class GameScene {
public:
	void GenerateBlocks();

	// 初期化
	void Initialize();

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_; // stdでエラーが起きたらKamataEngine::をいれる

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// デバックカメラ有効
	bool isDebugCameraActive_ = false;

	// デバックカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// デバックカメラの生成
	// debugCamera_ = new DebugCamera();

	// 3Dモデル
	KamataEngine::Model* modelskydome_ = nullptr;

	// モデルプレイヤー
	KamataEngine::Model* modelPlayer_ = nullptr;

	// 敵のモデル
	KamataEngine::Model* modelEnemy_ = nullptr;

	//パーティクル
	KamataEngine::Model* modelDeath_ = nullptr; 

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	// 自キャラ
	Player* player_ = nullptr;

	// キューブ
	Skydome* skydome_ = nullptr;

	// 敵
	// Enemy* enemy_ = nullptr;

	std::list<Enemy*> enemies_;

	// マップチップフィールド
	MapChipField* mapChipField_;

	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;

	// 3D
	KamataEngine::Model* cube_ = nullptr;

	// カメラコントロール
	CameraController* cameraController_ = nullptr;
	// void Initialize();
	// KamataEngine::Model* cameraModel_;

	DeathParticles* deathParticles_ = nullptr;

	// 全ての当たり判定を行う
	void CheckAllCollisions();

	// ゲームのフェーズ(型)
	enum class Phase {
		kPlay,  // ゲームプレイ
		kDeath, // デス演出
	};

		// デスフラグ
	bool isDead_ = false;

	// デスフラグのgetter
	bool IsDead() const { return isDead_; }

	// ゲームの現在フェーズ(変数)
	Phase phase_;

	void ChangePhase();

	// デストラクタ
	~GameScene();

	// 更新
	void Update();

	// 描画
	void Draw();
};
