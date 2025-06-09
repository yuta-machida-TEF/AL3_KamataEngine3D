#pragma once
#include "KamataEngine.h"

class Player {
public:

	static inline const float kAccleration = 0.1f;

	static inline const float kAttenuation = 0.1f;

	static inline const float kLimitRunSpeed = 2.0f;

	//重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.5f;
	//最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 0.4f;
	//ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 1.8f;

	//左右
	enum class LRDirection {
		kRight,
		kLeft,
	};
	
	//旋回開始時の角度
	float trunFirstRotationY_ = 0.0f;
	//旋回タイマー
	float trunTimer_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;
	//接地状態フラグ
	bool onGround_ = true;
	
	LRDirection lirDirection_ = LRDirection::kRight;

	const KamataEngine::WorldTransform& GetWorldTransform() const
	{ return worldTransform_;}

	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw();

private:
		// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Camera *camera_;
	// テクスチャハンドル
	//uint32_t textureHandle_ = 0u;

    KamataEngine::Model *model_;

	KamataEngine::Vector3 velocity_ = {}; 

};
