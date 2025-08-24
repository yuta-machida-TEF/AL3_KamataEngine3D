#pragma once
#include "Fade.h"
#include "KamataEngine.h"


//タイトルシーン
class TitleScene{
public:
	
	void Initialize();
	void Update();
	void Draw();

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

  
private:

	Fade* fade_ = nullptr; 

};

