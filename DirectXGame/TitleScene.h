#pragma once
#include "Fade.h"
#include "KamataEngine.h"
#include"Player.h"

//タイトルシーン
class TitleScene{
public:
	
	void Initialize(uint32_t textrueHandle);
	void Update();
	void Draw();

	~TitleScene();


	//終了フラグ
	bool finished_ = false;
	//デスフラグのgetter
	bool IsFinished() const { return finished_; }

	uint32_t TilteHandle = KamataEngine::TextureManager::Load("Title.png");

	// サウンドデータサウンド
	uint32_t TitleSound_ = 0;
	
	int titleSoundData_; 


	// スプライトを生成
	KamataEngine::Sprite* sprite = KamataEngine::Sprite::Create(TilteHandle, {0.0f, 0.0f});

	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;
	// モデルプレイヤー
	KamataEngine::Model* modelPlayer_ = nullptr;
	// カメラ
	KamataEngine::Camera camera_;
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	
	KamataEngine::WorldTransform worldTransformPlayer_;

 
	Fade* fade_ = nullptr;

	//シーンのフェーズ
	enum class Phase
	{
		kFadeIn,//フェードイン
		kMain,//メイン部
		kFadeOut,//フェーズアウト
	};

	//現在のフェーズ
	Phase phase_ = Phase::kFadeIn;

private:

	Player* player_ = nullptr;

};

