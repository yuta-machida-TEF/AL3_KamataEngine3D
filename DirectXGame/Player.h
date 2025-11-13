#pragma once
#include "KamataEngine.h"
#include "MyMath.h"

class MapChipField;
class Enemy;

class Player {
public:
	// AABBを取得
	AABB GetAABB();

	KamataEngine::Vector3 GetWorldPosition();

	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	// マップとの当たり判定情報
	struct CollisionMapInfo {
		bool ceiling = false;            // 天井衝突フラグ
		bool langing = false;            // 着地フラグ
		bool hitwall = false;            // 壁接触フラグ
		KamataEngine::Vector3 move = {}; // 移動量
	};

	void CheakMapCollision(CollisionMapInfo& info);
	void CheakMapCollisionUP(CollisionMapInfo& info);    // 上方向
	void CheakMapCollisionDown(CollisionMapInfo& info);  // 下方向
	void CheakMapCollisionRight(CollisionMapInfo& info); // 右方向
	void CheakMapCollisionLeft(CollisionMapInfo& info);  // 左方向
	// 3.判定結果を反映して移動させる
	void CheakMapMove(const CollisionMapInfo& info);
	// 4.天井に接触している場合の処理
	//void CheakMapCeiling(const CollisionMapInfo& info);
	//// 5.壁に接触している場合の処理
	//void CheakMapWall(CollisionMapInfo& info);

	// 角
	enum Corner {
		kRightBottom, // 右下
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kLeftTop,     // 左上

		kNumCorner // 要素数

	};

	// 攻撃フェーズ
	enum class AttackPhase {
		kUnknown = -1, // 無効状態
		kAnticipation, // 予備動作
		kAction,       // 前進動作
		kRecovery,     // 余韻動作
	};

	//振る舞い
	enum class Behavior {
		kRoot,   // 通常状態
		kAttack, // 攻撃中
		kUnknown = -1,//無効状態
	};

	//振る舞い
	Behavior behavior_ = Behavior::kRoot;

	//次の振る舞いリクエスト
	Behavior behaviorRequest_ = Behavior::kUnknown;

	//攻撃ギミックの経過時間カウンター
	uint32_t attackParameter_ = 0;

	//通常行動初期化
	void BehaviorRootInitialize();

	// 攻撃行動更新
	void BehaviorAttackUpdate();
	
	//// 通常行動更新
	//void BehaviorRootUpdate();

	////攻撃行動初期化
	//void BehaviorAttackInitaialize();

	// 自キャラ
	Player* player_ = nullptr;

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

	static inline const float kAccleration = 0.1f;

	static inline const float kAttenuation = 0.1f;

	static inline const float kLimitRunSpeed = 0.2f;

	// 重力加速度(下方向)
	//static inline const float kGravityAcceleration = 0.0f;
	// 最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 0.4f;
	// ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 0.8f;
	// 着地時の速度減衰率
	static inline const float kAttenuationLanding = 0.9f;
	// 微小な数値
	static inline const float kGroundSearchHeight = 0.1f;
	// 着地時の速度減衰率
	static inline const float kAttenuationWall = 0.9f;

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
	// 接地状態フラグ
	//bool onGround_ = true;

	LRDirection lrDirection_ = LRDirection::kRight;
	LRDirection lrDirection2_ = LRDirection::DOWN;

	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }

	//デスフラグ
	bool isDead_ = false;

	//デスフラグのgetter
	bool IsDead() const { return isDead_; }

	// 衝突応答
	void OnCollision(const Enemy* enemy);

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
	// テクスチャハンドル
	// uint32_t textureHandle_ = 0u;

	KamataEngine::Model* model_;

	KamataEngine::Vector3 velocity_ = {};
};
