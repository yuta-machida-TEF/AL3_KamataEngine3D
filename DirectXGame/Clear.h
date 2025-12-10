#pragma once
#include "Fade.h"
#include "KamataEngine.h"
#include "MyMath.h"

class Clear {
public:
	Clear* clear_ = nullptr;

	// 初期化
	void Initialize(uint32_t textrueHandle);
	void Update();
	void Draw();

	~Clear();

	// 終了フラグ
	bool finished_ = false;
	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

	// テクスチャハンドル
	uint32_t clearHandle = KamataEngine::TextureManager::Load("Clear.png");

	// スプライトを生成
	KamataEngine::Sprite* sprite = KamataEngine::Sprite::Create(clearHandle, {0.0f, 0.0f});

	// シーンのフェーズ
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェーズアウト
	};

	// 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;

	Fade* fade_ = nullptr;

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Camera* camera_;

	// モデル
	KamataEngine::Model* model_;

};