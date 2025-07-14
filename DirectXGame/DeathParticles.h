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

	// 追従対象とカメラの座標の差(オフセット)

private:

	KamataEngine::Model* model_;
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;


};


