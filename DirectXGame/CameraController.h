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

	//追従対象とカメラの座標の差(オフセット)
	KamataEngine::Vector3 targetOffset_ = {0, 0, -15.0f}; 

	const KamataEngine::Camera& GetViewProjecttion() const { return Camera_; }




	//追従対象とカメラの座標の差(オフセット)
	//KamataEngine::Vector3 targetOffset_ = {0, 0, -15.0f};

	//短形
	struct Rect 
	{
		float left = 0.0f;//左端
		float right = 1.0f; // 右端
		float bottom = 0.0f;//下端
		float top = 1.0f;//上端
	};

	//カメラ移動範囲
	Rect movableArea = {0, 100, 0, 100};


private:
	//カメラ
	KamataEngine::Camera Camera_;

};

