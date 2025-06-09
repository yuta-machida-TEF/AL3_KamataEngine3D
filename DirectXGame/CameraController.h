#pragma once
#include <vector>
#include "KamataEngine.h"
#include "Skydome.h"
#include "MapChipField.h"
using namespace KamataEngine::MathUtility;

//前方宣言
class Player;

class CameraController {
public:
	void Initialze();

	void Update();

	void Reset();

	Player* target_ = nullptr;

	void SetTarget(Player* target)
	{ 
		target_ = target;
	}

	// カメラ
	KamataEngine::Camera camera_;

	//追従対象とカメラの座標の差(オフセット)

	const KamataEngine::Camera& GetViewProjecttion() const { return camera_; }

	static inline const float kInterpolationRate = 1.8f;



	//追従対象とカメラの座標の差(オフセット)
	KamataEngine::Vector3 targetOffset_ = {0, 0, -15.0f};

	//短形
	struct Rect 
	{
		float left = 0.0f;//左端
		float right = 1.0f; // 右端
		float bottom = 0.0f;//下端
		float top = 1.0f;//上端
	};

	//カメラ移動範囲
	Rect movableArea_ = {0, 100, 0, 100};

	void SetMovableArea(Rect area)
	{ movableArea_ = area;}

	//カメラの目標座標
	KamataEngine::Vector3 coordInate;

	//追従対象の各方向へのカメラ移動範囲
	// 速度掛け率
	static inline const float kVelocityBiass = 3;
	static inline const Rect targetMargin = {-9.0f, 9.0f, -5.0f, 5.0f};

private:

	//カメラ
	KamataEngine::Camera Camera_;

};

