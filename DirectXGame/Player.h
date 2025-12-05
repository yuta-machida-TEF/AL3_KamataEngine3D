#pragma once
#include "KamataEngine.h"
#include "MyMath.h"

class MapChipField;
class Enemy;


class Player {
public:

	KamataEngine::Vector3 GetWorldPosition();

	// マップとの当たり判定情報
	struct CollisionMapInfo 
	{
		KamataEngine::Vector3 move = {}; // 移動量
	};
	// 3.判定結果を反映して移動させる
	void CheakMapMove(const CollisionMapInfo& info);

	// 自キャラ
	Player* player_ = nullptr;

	static inline const float kAccleration = 0.1f;

	static inline const float kAttenuation = 0.1f;

	static inline const float kLimitRunSpeed = 0.2f;

	// 左右
	enum class LRDirection {
		kRight,
		kLeft,
		UP,
		DOWN,
	};

	// 旋回開始時の角度
	float trunFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float trunTimer_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;

	LRDirection lrDirection_ = LRDirection::kRight;
	LRDirection lrDirection2_ = LRDirection::DOWN;

	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

	//デスフラグ
	bool isDead_ = false;

	//デスフラグのgetter
	bool IsDead() const { return isDead_; }

	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);

	void InputMove();

	// 更新
	void Update();

	// 描画
	void Draw();

	static inline const float kBlank = 0.9f;

	void AnimateTurn();

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Camera* camera_;

	KamataEngine::Model* model_;

	KamataEngine::Vector3 velocity_ = {};
};
