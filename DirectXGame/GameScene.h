#pragma once
#include "KamataEngine.h"

class GameScene
{
public:
	//初期化
	~GameScene();//~はdelete
	void Initialize();
	uint32_t textureHandle_ = 0;

	//スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	//更新
	void Update();

	//描画
	void Draw();

};



