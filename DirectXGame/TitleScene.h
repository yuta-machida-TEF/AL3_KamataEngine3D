#pragma once
#include "Fade.h"
#include "KamataEngine.h"


//タイトルシーン
class TitleScene{
public:
	
	void Initialize();
	void Update();
	void Draw();

	~TitleScene();


	//終了フラグ
	bool finished_ = false;
	//デスフラグのgetter
	bool IsFinished() const { return finished_; }

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

};

