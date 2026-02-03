#pragma once
#include "MyMath.h" //アフィン変換行列の計算のヘッター
// #include "KamataEngine.h"

class Player;

// 敵
class Enemy {
public:
	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	// 衝突応答
	void OnCollision(const Player* player);

	// マップとの当たり判定情報
	struct CollisionMapInfo {
		bool ceiling = false;            // 天井衝突フラグ
		bool langing = false;            // 着地フラグ
		bool hitwall = false;            // 壁接触フラグ
		KamataEngine::Vector3 move = {}; // 移動量
	};

	// アニメーションの周期となる時間[秒]
	static inline const float kWalkMotionTime = 5.0f;

	// 経過時間
	float walkTimer_ = 0.0f;

	// AABBを取得
	AABB GetAABB();

	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();

	void initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);
	void SetPostion(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);
	void SetPostion2(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);
	void SetPostion3(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);
	void SetPostion4(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);
	void Update();
	void Draw();

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Camera* camera_;

	KamataEngine::Model* model_;
};
