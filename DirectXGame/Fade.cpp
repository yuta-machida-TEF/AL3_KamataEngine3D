#include "Fade.h"
#include<algorithm>
using namespace KamataEngine;

void Fade::Initialize() 
{
    //ファイル名を指定してテクスチャハンドルを読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");
	//スプライトインスタンスの生成
	sprite_ = KamataEngine::Sprite::Create(textureHandle_, {0, 0});
	sprite_->SetSize(Vector2(1280, 720));//画面サイズ
	sprite_->SetColor(Vector4{0, 0, 0, 1});//黒色
}

void Fade::Start(Status status, float duration) {
	status_ = status;
	duration_ = duration;
	counter_ = 0.0f;
}

void Fade::Stop() 
{ 
	status_ = Status::None; 
}

bool Fade::IsFinished() const 
{ 
	switch (status_) {
	case Fade::Status::FadeIn:
		break;
	case Fade::Status::FadeOut:

        if(counter_ >= duration_) 
		{
			return true;
		} 
		else 
		{
			return false;
		}
		break;
	default:
		break;
	}
	
	return true; 
}


void Fade::Update() 
{
	switch (status_) {
	case Fade::Status::None:
		//何もしない
		break;
	case Fade::Status::FadeIn:

		// フレーム分の秒数をカウントアップ
		counter_ += 1.0f / 60.0f;
		// フェード継続時間に達したら打ち止め
		if (counter_ >= duration_) {
			counter_ = duration_;
		}
		// 0.0fから1.0fの間で、経過時間がフェード経過時間に近づくほどアルファ値を大きくする
		sprite_->SetColor(Vector4(0, 0, 0,1.0f - std::clamp(counter_ / duration_, 0.0f, 1.0f)));

		break;
	case Fade::Status::FadeOut:
		//フレーム分の秒数をカウントアップ
		counter_ += 1.0f / 60.0f;
		//フェード継続時間に達したら打ち止め
		if(counter_ >= duration_) 
		{
			counter_ = duration_;
		}
		//0.0fから1.0fの間で、経過時間がフェード経過時間に近づくほどアルファ値を大きくする
		sprite_->SetColor(Vector4(0, 0, 0, std::clamp(counter_ / duration_, 0.0f, 1.0f)));

		break;
	default:
		break;
	}

}

void Fade::Draw() 
{
	//DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	if (status_ == Status::None) {
		return;
	}
	Sprite::PreDraw(dxCommon->GetCommandList()); 
	sprite_->Draw();
	Sprite::PostDraw();
}



