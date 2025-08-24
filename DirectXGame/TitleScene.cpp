#define NOMINMAX
#include "TitleScene.h"
#include <algorithm>
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;


void TitleScene::Initialize() 
{
	//3Dモデルの生成
	model_ = Model::CreateFromOBJ("titleFont");
	modelPlayer_ = Model::CreateFromOBJ("player");

	//カメラの初期化
	camera_.Initialize();

	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransformPlayer_.Initialize();

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
		//フェード
		fade_->Update();
		if(fade_->IsFinished()) 
		{
			phase_ = Phase::kMain;
		}
		break;
	case TitleScene::Phase::kFadeOut:
		fade_->Update();
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
	Model::PreDraw(dxCommon->GetCommandList());

	//ここに3Dモデルインタランスの描画処理を記述する
    model_->Draw(worldTransform_, camera_);
	modelPlayer_->Draw(worldTransformPlayer_, camera_);

	//3Dモデル描画後処理
	Model::PostDraw();

	fade_->Draw();
}
