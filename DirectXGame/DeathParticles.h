#pragma once
#include "KamataEngine.h"
#include <vector>
using namespace KamataEngine::MathUtility;

class DeathParticles {
public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position);
	void Update();
	void Draw();

	// パーティクルの個数
	static inline const uint32_t kNumParticles = 8;

	std::array<KamataEngine::WorldTransform, kNumParticles> worldTransforms_;

	// カメラ
	KamataEngine::Camera *camera_;

	//存続時間(消失までの時間)<秒>
	static inline const float kDuration = 3.0f;
	//移動の速さ
	static inline const float kSpeed = 0.3f;
    //分割した1個分の角度
	static inline const float kAngleUnit = 2.0f * kNumParticles / 8.0f;
	//終了フラグ
	bool isFinished_ = false;
	//経過時間カウント
	float counter_ = 0.0f;
	//色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	//色の数値
	KamataEngine::Vector4 color_;

	// 追従対象とカメラの座標の差(オフセット)

private:

	KamataEngine::Model* model_;
	// ワールド変換データ
	//KamataEngine::WorldTransform worldTransform_;


};


