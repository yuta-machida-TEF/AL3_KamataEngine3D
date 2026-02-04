#pragma once
#include "KamataEngine.h"
#include<math.h>

//<summary>
// アフィン変換
//</summary>


struct Matrix4x4 
{
	float m[4][4];
};

namespace KamataEngine 
{
    Vector3 Normalize(const KamataEngine::Vector3& v);
}

KamataEngine::Matrix4x4 MakeAffineMatrix(KamataEngine::Vector3& scale, KamataEngine::Vector3& roteaion, KamataEngine::Vector3& translation);

KamataEngine::Matrix4x4 MakeRotateAxisMatrix(const KamataEngine::Vector3& axis, float angle);

// イージング
float EaseInOut(float x1, float x2, float t);

// AABB
struct AABB {
	KamataEngine::Vector3 min;
	KamataEngine::Vector3 max;
};

bool IsAABBCollision(const AABB& a, const AABB& b);

