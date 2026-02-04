#include "DeathParticles.h"
#include "CameraController.h"
#include "MyMath.h" //アフィン変換行列の計算のヘッター
#include <algorithm>
using namespace KamataEngine;
using namespace MathUtility;

void DeathParticles::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, KamataEngine::Vector3& position) {
    
	// NULLポイントチェック
	//assert(model);

	model_ = model;

	camera_ = camera;
	
	//ワールド変換の初期化
	for (KamataEngine::WorldTransform& worldTransform : worldTransforms_) 
	{
		 worldTransform.Initialize();
		worldTransform.translation_ = position;
	}

	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};

	if (isFinished_) {
		return;
	}
}

void DeathParticles::Update() {
	for (KamataEngine::WorldTransform& worldTransform : worldTransforms_) 
	{
		// アフィン変換行列
		worldTransform.matWorld_ = MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
		worldTransform.TransferMatrix(); // プレイヤーの座標の計算
	}

	for (uint32_t i = 0; i < 8; i++) {
		// 基本となる速度ベクトル
		KamataEngine::Vector3 velocity = {0.03f, 0, 0};
		// 回転角を計算する
		float angle = 30.0f * i;
		// Z軸まわり回転行列
		KamataEngine::Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);
		// 基本ベクトルを回転させて速度ベクトルを得る
		velocity = Transform(velocity, matrixRotation);
		// 移動処理
		worldTransforms_[i].translation_ += velocity;
	}
	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}
	// 終了なら何もしない
	if (isFinished_) {
 		return;
	}
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);
	//色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	
}

void DeathParticles::Draw() 
{
	for (KamataEngine::WorldTransform& worldTransform : worldTransforms_) 
	{
		model_->Draw(worldTransform, *camera_,&objectColor_); // プレイヤーの座標の計算
	}
	//終了なら何もしない
	if (isFinished_) 
	{
		return;
	}

}
