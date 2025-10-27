#pragma once
#include "Fade.h"
#include "KamataEngine.h"


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

	// テクスチャハンドル
	uint32_t TilteHandle = KamataEngine::TextureManager::Load("A.png");
	//スプライトを生成
	KamataEngine::Sprite* sprite = KamataEngine::Sprite::Create(TilteHandle, {0.0f, 0.0f});
	
	//// カメラ
	//KamataEngine::Camera* camera_ = nullptr;
	//
	//KamataEngine::WorldTransform worldTransformPlayer_;

 
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

	//// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;


	//	//// ワールドトランスフォーム
	//KamataEngine::WorldTransform worldTransform_;

};

