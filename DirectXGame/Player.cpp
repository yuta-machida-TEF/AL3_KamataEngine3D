#define NOMINMAX
#include "Player.h"
#include "Enemy.h"
#include "MapChipField.h"
#include <algorithm>
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;

void Player::Initialize(Model* model, Camera* camera, KamataEngine::Vector3& position) {
	// NULLポイントチェック
	assert(model);

	model_ = model;

	worldTransform_.translation_ = position;

	camera_ = camera;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	worldTransform_.Initialize();
}

void Player::Update() {
	// 1.移動入力
	InputMove();
	// 2.移動量を加速して衝突判定する
	// 衝突情報を初期化
	CollisionMapInfo collisionMapInfo;
	// 移動量に速度の値をコピー
	collisionMapInfo.move = velocity_;
	// 3.判定結果を反映して移動させる
	CheakMapMove(collisionMapInfo);
	// 7.旋回制御
	AnimateTurn();

	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix(); // プレイヤーの座標の計算
}

void Player::Draw()
{
     model_->Draw(worldTransform_, *camera_);
}

// 移動入力
void Player::InputMove() {
	// 左右移動操作
	//if (onGround_) {
		if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)
			|| Input::GetInstance()->PushKey(DIK_W)|| Input::GetInstance()->PushKey(DIK_S)) 
		{

			// 左右加速
		    Vector2 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_D)) {
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAccleration;

				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					// 旋回開始時の角度を記録する
					trunFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーに時間を設定する
					trunTimer_ = kTimeTurn;
				}
			} 
			else if (Input::GetInstance()->PushKey(DIK_A)) {
			    // 右移動中の左入力
			    if (velocity_.x > 0.0f) {
				    // 速度と逆方向に入力中は急ブレーキ
				    velocity_.x *= (1.0f - kAttenuation);
			    }
			    acceleration.x -= kAccleration;
			    if (lrDirection_ != LRDirection::kLeft) {
				    lrDirection_ = LRDirection::kLeft;
				    // 旋回開始時の角度を記録する
				    trunFirstRotationY_ = worldTransform_.rotation_.y;
				    // 旋回タイマーに時間を設定する
				    trunTimer_ = kTimeTurn;
			    }
		    } else if (Input::GetInstance()->PushKey(DIK_W)) {
			    // 右移動中の左入力
			    if (velocity_.y < 0.0f) {
				    // 速度と逆方向に入力中は急ブレーキ
				    velocity_.y *= (1.0f - kAttenuation);
			    }
			    acceleration.y += kAccleration;

			    if (lrDirection_ != LRDirection::UP) 
				{
				    lrDirection_ = LRDirection::UP;
			    }

		    } else if (Input::GetInstance()->PushKey(DIK_S)) {
			    // 右移動中の左入力
			    if (velocity_.y > 0.0f) {
				    // 速度と逆方向に入力中は急ブレーキ
				    velocity_.y *= (1.0f - kAttenuation);
			    }
			    acceleration.y -= kAccleration;

			    if (lrDirection_ != LRDirection::DOWN)
				{
				    lrDirection_ = LRDirection::DOWN;   
			    }

		    }

			// 加速/減速
		    velocity_.x += acceleration.x;
		    velocity_.y += acceleration.y;

			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		    velocity_.y = std::clamp(velocity_.y, -kLimitRunSpeed, kLimitRunSpeed);

		} else {
			// 非入力時は移動減衰をかける
			velocity_.x *= (1.0f - kAccleration);
			velocity_.y *= (1.0f - kAccleration);
		}
}



// 3.判定結果を反映して移動させる
void Player::CheakMapMove(const CollisionMapInfo& info) {
	// 移動
	worldTransform_.translation_ += info.move;
}


// 7.旋回制御
void Player::AnimateTurn() {
	// 旋回制御
	if (trunTimer_ > 0.0f) {
		trunTimer_ -= 1.0f / 60.0f;

		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		// 自キャラの角度を設定する
		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, trunFirstRotationY_, trunTimer_ / kTimeTurn);
	}
}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}


