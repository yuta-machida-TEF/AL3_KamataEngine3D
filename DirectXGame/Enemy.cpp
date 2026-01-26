#define NOMINMAX
#include "MapChipField.h"
#include "Player.h"
#include <algorithm>
#include "Enemy.h"
#include"MyMath.h"
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;

void Enemy::initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position) {
	// NULLポイントチェック
	assert(model);

	model_ = model;

	// textureHandle_ = textureHandle;

	worldTransform_.translation_ = position;

	camera_ = camera;

	// 速度を設定する
	velocity_ = {-kWalkSpeed, 0, 0};

	//walkTimer_ = 0.0f;

	worldTransform_.rotation_.y = -std::numbers::pi_v<float> / 2.0f;

	worldTransform_.Initialize();
	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix(); // プレイヤーの座標の計算
}

void Enemy::Update() {

	static float theta = 0.0f;
	theta += 0.02f;

	// ===== 回転中心（変更したい場所）=====
	KamataEngine::Vector3 pivot = {
	    12.0f, // X
	    4.0f, // Y
	    0.0f  // Z（床と同じなら0）
	};

	// ===== 回転前のEnemyの位置（中心からの相対位置）=====
	KamataEngine::Vector3 offset = {
	    -3.0f, // 半径X
	    0.0f, 0.0f};

	// ===== 画面で分かる回転（Z軸）=====
	KamataEngine::Vector3 axis = {0.0f, 0.0f, 1.0f};

	KamataEngine::Matrix4x4 rotate = MakeRotateAxisMatrix(axis, theta);

	// offset を回転
	KamataEngine::Vector3 rotatedOffset = Transform(offset, rotate);

	// 回転中心に戻す
	worldTransform_.translation_ = {pivot.x + rotatedOffset.x, pivot.y + rotatedOffset.y, pivot.z + rotatedOffset.z};

	// Enemy自体は回さない
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	// 行列作成
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}



AABB Enemy::GetAABB() {
	KamataEngine::Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

KamataEngine::Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}



//KamataEngine::Vector3 Enemy::transslate() { return KamataEngine::Vector3(); }


void Enemy::OnCollision(const Player* player) { (void)player; }

void Enemy::Draw() { model_->Draw(worldTransform_, *camera_ /*textureHandle_*/); }
