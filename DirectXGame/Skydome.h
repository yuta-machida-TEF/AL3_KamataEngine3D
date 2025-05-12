#pragma once
#include "KamataEngine.h"

class Skydome {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera_);

	void Update();

	void Draw();

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	
	// モデル
	KamataEngine::Camera* camera_;

	KamataEngine::Model* model_;

	KamataEngine::Model* cube_;
};