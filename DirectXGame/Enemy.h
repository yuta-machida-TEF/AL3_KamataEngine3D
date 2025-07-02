#pragma once

//敵
class Enemy {
public:

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

	//void CheakMapCollision(CollisionMapInfo& info);
	//void CheakMapCollisionUP(CollisionMapInfo& info);    // 上方向
	//void CheakMapCollisionDown(CollisionMapInfo& info);  // 下方向
	//void CheakMapCollisionRight(CollisionMapInfo& info); // 右方向
	//void CheakMapCollisionLeft(CollisionMapInfo& info);  // 左方向

	//// 4.天井に接触している場合の処理
	//void CheakMapCeiling(const CollisionMapInfo& info);
	//// 5.壁に接触している場合の処理
	//void CheakMapWall(CollisionMapInfo& info);
	//// 6.接地状態の切り替え
	//void CheakMapLanding(const CollisionMapInfo& info);


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



