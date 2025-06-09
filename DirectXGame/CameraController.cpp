#include "CameraController.h"
#include "Player.h"

//カメラの初期化
void CameraController::Initialze() 
{ 
	//Camera_;
	//void Initialze();
	camera_.Initialize();
}

void CameraController::Reset() 
{
 //追従対象のワールドトランスフォームを参照
	const KamataEngine::WorldTransform& targetWorldTransform = target_->GetWorldTransform();
    camera_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}

void CameraController::Update() {
	const KamataEngine::Vector3& targetVelocity = target_->GetVelocity();
	// 追従対象のワールドトランスフォームを参照
	const KamataEngine::WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	//追従対象とオフセットからカメラの目標座標を計算
	coordInate = targetWorldTransform.translation_ + targetOffset_ + targetVelocity * kVelocityBiass;

	//座標補間によりゆったり追従
	camera_.translation_.x = Lerp(camera_.translation_.x, coordInate.x, kInterpolationRate);

	//追従対象が画面外に出ないように補正
	camera_.translation_.x = max(camera_.translation_.x, camera_.translation_.x + targetMargin.left);
	camera_.translation_.x = min(camera_.translation_.x, camera_.translation_.x + targetMargin.right);
	camera_.translation_.y = max(camera_.translation_.y, camera_.translation_.y + targetMargin.bottom);
	camera_.translation_.y = min(camera_.translation_.y, camera_.translation_.y + targetMargin.top);
	
	
	// 移動範囲制限
	camera_.translation_.x = max(camera_.translation_.x, movableArea_.left);
	camera_.translation_.x = min(camera_.translation_.x, movableArea_.right);
	camera_.translation_.y = max(camera_.translation_.y, movableArea_.bottom);
	camera_.translation_.y = min(camera_.translation_.y, movableArea_.top);
	
	// 行列を更新する
	camera_.UpdateMatrix();
}