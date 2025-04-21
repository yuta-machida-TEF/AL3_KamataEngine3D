#pragma once
#include "KamataEngine.h"

class Player {
public:

	// 初期化
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera);

	// 更新
	void Update();

	// 描画
	void Draw();

private:
		// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Camera *camera_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

    KamataEngine::Model *model_;

};
