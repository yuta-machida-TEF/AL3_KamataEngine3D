#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() {//~は、デストラクタのこといっている。デストラクタはプログラムが最後の時にプログラム名の削除を行う


	delete sprite_;

}

void GameScene::Initialize() {

	textureHandle_ = TextureManager::Load("banana.png"); 

	//スプライトインスタンスの生成
	sprite_ = Sprite::Create(textureHandle_, {100,50});

	//delete sprite_;
}

void GameScene::Update() {}

void GameScene::Draw() {

	//DirecitXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	sprite_->Draw();

	//スプライト描画後処理
	Sprite::PostDraw();

}
