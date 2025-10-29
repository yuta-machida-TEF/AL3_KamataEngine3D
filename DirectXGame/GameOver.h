//#pragma once
//#include "Fade.h"
//#include "KamataEngine.h"
//
//class GameOver {
//public:
//	void Initialize(uint32_t textrueHandle);
//	void Update();
//	void Draw();
//
//	// 終了フラグ
//	bool finished_ = false;
//	// デスフラグのgetter
//	bool IsFinished() const { return finished_; }
//
//	// テクスチャハンドル
//	uint32_t GameOverHandle = KamataEngine::TextureManager::Load("B.png");
//	// スプライトを生成
//	KamataEngine::Sprite* sprite = KamataEngine::Sprite::Create(GameOverHandle, {0.0f, 0.0f});
//
//	Fade* fade_ = nullptr;
//
//	// シーンのフェーズ
//	enum class Phase {
//		kFadeIn,  // フェードイン
//		kMain,    // メイン部
//		kFadeOut, // フェーズアウト
//	};
//
//	// 現在のフェーズ
//	Phase phase_ = Phase::kFadeIn;
//
//private:
//};
