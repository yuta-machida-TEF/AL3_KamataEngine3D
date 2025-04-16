#include "GameScene.h"

using namespace KamataEngine;


void GameScene::Initialize() {//h(ヘッターファイル)にいれる

	textureHandle_ = TextureManager::Load("Fruuits.png");

	sprite_ = Sprite::Create(textureHandle_, {100,50});

}

GameScene::~GameScene() 
{
	delete sprite_;
}

void GameScene::Update() {}

void GameScene::Draw() {

	//DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	sprite_->Draw();

	Sprite::PostDraw();
}
