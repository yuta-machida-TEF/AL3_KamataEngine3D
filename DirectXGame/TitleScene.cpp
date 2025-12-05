#define NOMINMAX
#include "TitleScene.h"
#include <algorithm>
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;


void TitleScene::Initialize(uint32_t textrueHandle) {
	//3Dモデルの生成
	TilteHandle = textrueHandle;

	// ゲームプレイフェーズ
	phase_ = Phase::kFadeIn;

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 6.0f);

}
   
TitleScene::~TitleScene()
{
	delete fade_;
}


void TitleScene::Update() 
{
	fade_->Update();
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
	//DirectXCommonインタランスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	//3Dモデル描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// スプライト描画
	sprite->Draw();
	

	//3Dモデル描画後処理
	Model::PostDraw();

	fade_->Draw();
}
