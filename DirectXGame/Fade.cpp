#include "Fade.h"
#include"algorithm"
#include "KamataEngine.h"
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

void Fade::Update() {}

void Fade::Draw() 
{
	//DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList()); 
	sprite_->Draw();
	Sprite::PostDraw();
}
