#include "CameraController.h"
#include "Player.h"

//カメラの初期化
void CameraController::Initialze() 
{ 
	Camera_;
	//void Initialze();
}

void CameraController::Reset() 
{
 //追従対象のワールドトランスフォームを参照
	const KamataEngine::WorldTransform& targetWorldTransform = target_->GetWorldTransform();
 Camera_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}

void CameraController::Update() {
	// 追従対象のワールドトランスフォームを参照
	const KamataEngine::WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	Camera_.translation_ = targetWorldTransform.translation_ + targetOffset_;
	// 行列を更新する
	Camera_.UpdateMatrix();
}