#define NOMINMAX
#include "MapChipField.h"
#include "Player.h"
#include <algorithm>
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;
#include "Clear.h"

void Clear::Initialize(/*KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position*/)
{
	//// NULLポイントチェック
	//assert(model);

 //   //model_ = model;

	//worldTransform_.translation_ = position;

	//camera_ = camera;

	//worldTransform_.Initialize();
}

void Clear::Update() {}

void Clear::Draw() { model_->Draw(worldTransform_, *camera_ /*textureHandle_*/); }

//void Clear::OnCollision(const Player* player) { (void)player; }