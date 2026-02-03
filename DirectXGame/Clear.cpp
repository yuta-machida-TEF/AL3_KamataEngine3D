#include "Clear.h"

using namespace KamataEngine;
using namespace MathUtility;

void Clear::Initialize(Model* model, Camera* camera, const Vector3& position) {
	model_ = model;
	camera_ = camera;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	// ★ MyMath の UpdateMatrix を使う
	UpdateMatrix(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Clear::Update() {
	// ★ ここも MyMath のみ
	UpdateMatrix(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Clear::Draw() {
	if (model_) {
		model_->Draw(worldTransform_, *camera_);
	}
}
