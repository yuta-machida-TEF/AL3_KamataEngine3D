#pragma once

class Player;

//敵
class Enemy {
public:

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;


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

	//速度
	KamataEngine::Vector3 velocity_ = {};

	// 歩行の速さ
	static inline const float kWalkSpeed = 0.04f;

	//最初の角度[度]
	static inline const float kWalkMotionAngleStart = 5.0f;
	//最後の角度[度]
	static inline const float kWalkMotionAngleEnd = 5.0f;
	//アニメーションの周期となる時間[秒]
	static inline const float kWalkMotionTime = 5.0f;

	//経過時間
	float walkTimer_ = 0.0f;

	// AABBを取得
	AABB GetAABB();

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

	//KamataEngine::Vector3 velocity_ = {};
};



