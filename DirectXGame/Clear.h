#pragma once
#include "KamataEngine.h"
#include "MyMath.h"

//class Player;
//class MapChipField;
//class Enemy;

class Clear {
public:
	
	//// マップチップによるフィールド
	//MapChipField* mapChipField_ = nullptr;

	//// キャラクターの当たり判定サイズ
	//static inline const float kWidth = 0.8f;
	//static inline const float kHeight = 0.8f;


	//void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	//// 衝突応答
	//void OnCollision(const Player* player);

	//// マップとの当たり判定情報
	//struct CollisionMapInfo {
	//	bool ceiling = false;            // 天井衝突フラグ
	//	bool langing = false;            // 着地フラグ
	//	bool hitwall = false;            // 壁接触フラグ
	//	KamataEngine::Vector3 move = {}; // 移動量
	//};

	Clear* clear_ = nullptr;


	// 初期化
	void Initialize(/*KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position*/);
	void Update();
	void Draw();

private:

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	
	KamataEngine::Camera* camera_;

	// モデル
	KamataEngine::Model* model_;

	//テクスチャハンドル
	//uint32_t textureHandle_ = 0u; 

};

