#define NOMINMAX
#include "MyMath.h"//アフィン変換行列の計算のヘッター
#include "Player.h"
#include "MapChipField.h"
#include<numbers>
#include<algorithm>
using namespace KamataEngine;
using namespace MathUtility;
#include "Enemy.h"

void Enemy::initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position) 
{
	// NULLポイントチェック
	assert(model);

	model_ = model;

	// textureHandle_ = textureHandle;

	worldTransform_.translation_ = position;

	camera_ = camera;

	// 速度を設定する
	velocity_ = {-kWalkSpeed, 0, 0};

	walkTimer_ = 0.0f;

	worldTransform_.rotation_.y = -std::numbers::pi_v<float> / 2.0f;

	worldTransform_.Initialize();

}

void Enemy::Update() 
{
	// void Enemy::CheakMapCollision(CollisionMapInfo& info) {}
	//
	// void Enemy::CheakMapCollisionUP(CollisionMapInfo& info) {}
	//
	// void Enemy::CheakMapCollisionDown(CollisionMapInfo& info) {}
	//
	// void Enemy::CheakMapCollisionRight(CollisionMapInfo& info) {}
	//
	// void Enemy::CheakMapCollisionLeft(CollisionMapInfo& info) {}
	//
	// void Enemy::CheakMapCeiling(const CollisionMapInfo& info) {}
	//
	// void Enemy::CheakMapWall(CollisionMapInfo& info) {}

	// void Enemy::CheakMapLanding(const CollisionMapInfo& info) {}

	//移動
	worldTransform_.translation_ += velocity_;

	//タイマーを加算
	walkTimer_ += 5.0f / 60.0f;

	//回転アニメーション
	worldTransform_.rotation_.x = std::sin(walkTimer_);

		 // アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix(); // プレイヤーの座標の計算

}

void Enemy::Draw() 
{
	model_->Draw(worldTransform_, *camera_ /*textureHandle_*/);
}


