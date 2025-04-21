#include "GameScene.h"
//#include "Player.h"

using namespace KamataEngine;


void GameScene::Initialize() {//h(ヘッターファイル)にいれる

	textureHandle_ = TextureManager::Load("Fruuits.png");

	sprite_ = Sprite::Create(textureHandle_, {100,50});

	model_ = Model::Create();

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//カメラの初期化
	camera_.Initialize();

	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize(model_, textureHandle_,&camera_);

}

GameScene::~GameScene() 
{
	delete sprite_;

	delete model_;

	delete player_;
}

void GameScene::Update() 
{
	//自キャラの更新
	player_->Update();
    //行列を定義バッファに転送
	worldTransform_.TransferMatrix();
}

void GameScene::Draw() {

	//DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	
	//3Dモデル描画
	//model_->Draw(worldTransform_, camera_, textureHandle_);

	// 自キャラの描画
	player_->Draw();

	//3Dモデル描画前処理
	Model::PostDraw();//プログラムの終了

	
}
