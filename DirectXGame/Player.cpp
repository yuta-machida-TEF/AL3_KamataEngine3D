#define NOMINMAX
#include "MyMath.h"//アフィン変換行列の計算のヘッター
#include "Player.h"
#include<numbers>
#include<algorithm>
using namespace KamataEngine;
using namespace MathUtility;

void Player::Initialize(Model* model, Camera* camera, KamataEngine::Vector3& position) {
	//NULLポイントチェック
	assert(model);

	model_ = model;

	//textureHandle_ = textureHandle;

	worldTransform_.translation_ = position;
	
	camera_ = camera;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	worldTransform_.Initialize();
}



void Player::Update() 
{
    //移動入力
	if (onGround_) 
	{
		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAccleration;

				if (lirDirection_ != LRDirection::kRight) {
					lirDirection_ = LRDirection::kRight;
					// 旋回開始時の角度を記録する
					trunFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーに時間を設定する
					trunTimer_ = kTimeTurn;
				}

			} 
			else if (Input::GetInstance()->PushKey(DIK_LEFT)) 
			{

				// 右移動中の左入力
				if (velocity_.x > 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAccleration;

				if (lirDirection_ != LRDirection::kLeft) {
					lirDirection_ = LRDirection::kLeft;
					// 旋回開始時の角度を記録する
					trunFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーに時間を設定する
					trunTimer_ = kTimeTurn;
				}
			}
			// 加速/減速
			velocity_ += acceleration;
			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		} 
		else 
		{
			// 非入力時は移動減衰をかける
			velocity_.x *= (1.0f - kAccleration);
		}

        if (Input::GetInstance()->PushKey(DIK_UP)) {
			// ジャンプ初速
			velocity_ += Vector3(0, kJumpAcceleration, 0);
		}
	}
	//空中
	else 
	{
		// 落下速度
		velocity_ += Vector3(0, -kGravityAcceleration, 0);
		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}
	   // 着地フラグ
	bool langing = false;

	// 地面との当たり判定
	// 下降中
	if (velocity_.y < 0) {
		// Y座標が地面以外になったら着地
		if (worldTransform_.translation_.y <= 1.0f) {
			langing = true;
		}
	}
	//接地判定
	if (onGround_) 
	{
		//ジャンプ開始
		if (velocity_.y >0.0f) 
		{
			//空中状態に移行
			onGround_ = false;
		}
	} 
	else {
		// 着地
		if (langing) {
			// めり込み排斥
			worldTransform_.translation_.y = 1.0f;
			// 摩擦で横方向速度が減衰する
			velocity_.y += (1.0f - kAttenuation);
			// 下方向速度をリセット
			velocity_.y = 0.0f;
			// 接地状態に移行
			onGround_ = true;
		}
	}

	// 移動
	   worldTransform_.translation_ += velocity_;

	// 旋回制御
	if (trunTimer_ > 0.0f) {
		trunTimer_ -= 1.0f / 60.0f;

		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lirDirection_)];
		// 自キャラの角度を設定する
		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, trunFirstRotationY_, trunTimer_ / kTimeTurn);
	}

	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix(); // プレイヤーの座標の計算

}

void Player::Draw() {

	model_->Draw(worldTransform_, *camera_/*textureHandle_*/);
}
