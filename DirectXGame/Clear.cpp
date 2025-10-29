#define NOMINMAX
#include "MapChipField.h"
#include "Player.h"
#include <algorithm>
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;
#include "Clear.h"

void Clear::Initialize(/*uint32_t textrueHandle*/) {
	// ゲームプレイフェーズ
	phase_ = Phase::kFadeIn;

	fade_= new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 6.0f);
}

void Clear::Update() { fade_->Update(); }

void Clear::Draw() 
{
	////DirectXCommonインタランスの取得
	//DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//model_->Draw(worldTransform_, *camera_ /*textureHandle_*/);
	//Sprite::PreDraw(dxCommon->GetCommandList());

	// スプライト描画
	//sprite->Draw();



}

Clear::~Clear() 
{ delete fade_; }

//void Clear::OnCollision(const Player* player) { (void)player; }