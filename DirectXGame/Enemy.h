#pragma once
#include "MyMath.h" //アフィン変換行列の計算のヘッター
#include"Player.h"
#include "KamataEngine.h"

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

	// 速度
	KamataEngine::Vector3 velocity_ = {};

	// 歩行の速さ
	static inline const float kWalkSpeed = 0.04f;

	// AABBを取得
	AABB GetAABB();

	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();

	//踏みつけ判定
	void OnHitByPlayer(const Player* player);
	void OnStomped();     // 踏みつけ
	bool IsDead() const { return isDead_; }
	AABB GetHeadAABB();


	void initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);
	void Update();
	void Draw();

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Camera* camera_;
	// テクスチャハンドル
	// uint32_t textureHandle_ = 0u;

	KamataEngine::Model* model_;

	KamataEngine::Vector3 translate_ ={};

	KamataEngine::Vector3 rotate_ = {};

	//当たり判定用サイズ
	KamataEngine::Vector3 bodySize_ = {0.6f, 0.6f, 0.6f};

	//状態確認専用
	bool isDead_ = false;

	float headHeight_ = 0.6f;

};
