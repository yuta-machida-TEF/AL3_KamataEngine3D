#pragma once
#include "KamataEngine.h"
#include "TitleScene.h"

class Fade {
	void Initialize();
	void Update();
	void Draw();


private:

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

};
