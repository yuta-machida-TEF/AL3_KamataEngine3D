#pragma once
#include "CameraController.h"
#include "Enemy.h"
#include "KamataEngine.h"
#include "MapChipField.h"
#include "Player.h"
#include "Skydome.h"
#include <vector>
#include "DeathParticles.h"
#include "Fade.h"
#include "Clear.h"

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


	// 3Dモデル
	KamataEngine::Model* modelskydome_ = nullptr;

	// モデルプレイヤー
	KamataEngine::Model* modelPlayer_ = nullptr;

	// 敵のモデル
	KamataEngine::Model* modelEnemy_ = nullptr;

	//パーティクル
	KamataEngine::Model* modelDeath_ = nullptr; 

	////クリア条件
	KamataEngine::Model* clearModel_ = nullptr;


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

	std::list<Enemy*> enemies_;

	// マップチップフィールド
	MapChipField* mapChipField_;

	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;

	// 3D
	KamataEngine::Model* cube_ = nullptr;

	// カメラコントロール
	CameraController* cameraController_ = nullptr;

	DeathParticles* deathParticles_ = nullptr;

	// 全ての当たり判定を行う
	void CheckAllCollisions();

	// ゲームのフェーズ(型)
	enum class Phase {
		kFadeIn,//フェードイン
		kPlay,  // ゲームプレイ
		kDeath, // デス演出
		kFadOut,//フェードアウト
	};

		// デスフラグ
	bool isDead_ = false;

	bool isClear_ = false;

	// デスフラグのgetter
	bool IsDead() const { return isDead_; }

	//デスフラグのgetter
	bool IsFinished() const { return finished_; }

	bool IsCleared() const { return isClear_; }


	// 終了フラグ
	bool finished_ = false;

	// フェード
	Fade* fade_ = nullptr;

	// ゲームの現在フェーズ(変数)
	Phase phase_ = Phase::kFadeIn;
 

	void ChangePhase();

	// デストラクタ
	~GameScene();

	// 更新
	void Update();

	// 描画
	void Draw();

private:

	Clear* clear_ = nullptr;

};
