#include "DeathParticles.h"
#include "CameraController.h"

void DeathParticles::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position) {
    
	// NULLポイントチェック
	assert(model);

	model_ = model;

	camera_ = camera;
	
	//ワールド変換の初期化
	for (KamataEngine::WorldTransform& worldTransform : worldTransforms_) 
	{
		 worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
}

void DeathParticles::Update() {
	for (KamataEngine::WorldTransform& worldTransform : worldTransforms_) 
	{
		// アフィン変換行列
		//worldTransform.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
		worldTransform.TransferMatrix(); // プレイヤーの座標の計算
	}
}

void DeathParticles::Draw() 
{
	model_->Draw(worldTransform_, *camera_ /*textureHandle_*/);
}
