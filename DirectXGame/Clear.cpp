
#define NOMINMAX
#include "MapChipField.h"
#include "Player.h"
#include <algorithm>
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;
#include "Clear.h"

void Clear::Initialize(uint32_t textrueHandle) {
	
	// 3Dモデルの生成
	clearHandle = textrueHandle;
	
	// ゲームプレイフェーズ
	phase_ = Phase::kFadeIn;

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 6.0f);
}

void Clear::Update() 
{ 
	fade_->Update();
}

void Clear::Draw() 
{
	sprite->Draw();
	fade_->Draw();
}

Clear::~Clear() { delete fade_; }
