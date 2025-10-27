#define NOMINMAX
#include "TitleScene.h"
#include <algorithm>
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;


void TitleScene::Initialize(uint32_t textureHandle) {
	

	TilteHandle = textureHandle;

	//KamataEngine::Camera* camera_ = nullptr;

	////カメラの初期化
	//camera_.Initialize();

	////ワールド変換の初期化
	//worldTransform_.Initialize();
	//worldTransformPlayer_.Initialize();

	// ゲームプレイフェーズ
	phase_ = Phase::kFadeIn;

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 6.0f);

}
   
TitleScene::~TitleScene()
{
	delete fade_;
	delete sprite;
}


void TitleScene::Update() 
{

	fade_->Update();
	//worldTransform_.TransferMatrix();
	switch (phase_) {
	case TitleScene::Phase::kFadeIn:
		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
		}
		break;
	case TitleScene::Phase::kMain:
		
		if(fade_->IsFinished()) 
		{
			phase_ = Phase::kMain;
		}
		break;
	case TitleScene::Phase::kFadeOut:
		if (fade_->IsFinished()) 
		{
			finished_ = true;
		}
		break;
	}

}

//描画
void TitleScene::Draw() 
{
	////DirectXCommonインタランスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	////3Dモデル描画前処理
	//Model::PreDraw(dxCommon->GetCommandList());

	Sprite::PreDraw(dxCommon->GetCommandList());

	//スプライト描画
	sprite->Draw();

	//model_->Draw(textureHandle_);

	//ここに3Dモデルインタランスの描画処理を記述する
	//modelPlayer_->Draw(worldTransformPlayer_, camera_);

	//3Dモデル描画後処理
	Model::PostDraw();

	fade_->Draw();
}
