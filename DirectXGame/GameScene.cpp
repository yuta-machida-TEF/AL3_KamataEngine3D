#include "GameScene.h"

using namespace KamataEngine;


void GameScene::Initialize() {//h(ヘッターファイル)にいれる

	textureHandle_ = TextureManager::Load("Fruuits.png");

	sprite_ = Sprite::Create(textureHandle_, {100,50});

	model_ = Model::Create();

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//カメラの初期化
	camera_.Initialize();

}

GameScene::~GameScene() 
{
	delete sprite_;

	delete model_;
}

void GameScene::Update() {}

void GameScene::Draw() {

	//DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	
	//3Dモデル描画
	model_->Draw(worldTransform_, camera_, textureHandle_);

	//3Dモデル描画前処理
	Model::PostDraw();
}
