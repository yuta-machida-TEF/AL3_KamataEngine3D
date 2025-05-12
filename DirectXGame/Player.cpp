#include "Player.h"
using namespace KamataEngine;

void Player::Initialize(Model* model,uint32_t textureHandle,Camera* camera) {
	//NULLポイントチェック
	assert(model);

	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	
	camera_ = camera;

}

void Player::Update() {

}

void Player::Draw() {

	model_->Draw(worldTransform_, *camera_, textureHandle_);
}
