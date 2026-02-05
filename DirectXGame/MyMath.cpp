
#include "MyMath.h"
#include <cmath>
#include <numbers>
using namespace KamataEngine;
using namespace MathUtility;

KamataEngine::Matrix4x4 MakeAffineMatrix(KamataEngine::Vector3& scale, KamataEngine::Vector3& roteaion, KamataEngine::Vector3& translation) 
{ 
	// スケーリング行列の作成
	KamataEngine::Matrix4x4 matScale = MakeScaleMatrix(scale);

	// 回転行列の作成
	KamataEngine::Matrix4x4 matRotX = MakeRotateXMatrix(roteaion.x);
	KamataEngine::Matrix4x4 matRotY = MakeRotateYMatrix(roteaion.y);
	KamataEngine::Matrix4x4 matRotZ = MakeRotateZMatrix(roteaion.z);
	KamataEngine::Matrix4x4 matRot = matRotZ * matRotX * matRotY;

	// 平行移動行列の作成
	KamataEngine::Matrix4x4 matTrans = MakeTranslateMatrix(translation);

	// スケーリング、回転、平行移動の合成
	KamataEngine::Matrix4x4 matWorld = matScale * matRot * matTrans;

	return matWorld;

}

namespace KamataEngine 
{
    Vector3 Normalize(const KamataEngine::Vector3& v) {
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return {v.x / length, v.y / length, v.z / length};
}
}

KamataEngine::Matrix4x4 MakeRotateAxisMatrix(const KamataEngine::Vector3& axis, float angle) {
	KamataEngine::Vector3 a = KamataEngine::Normalize(axis);

	float x = a.x;
	float y = a.y;
	float z = a.z;

	float c = cosf(angle);
	float s = sinf(angle);
	float t = 1.0f - c;

	KamataEngine::Matrix4x4 result = {};

	result.m[0][0] = t * x * x + c;
	result.m[0][1] = t * x * y - s * z;
	result.m[0][2] = t * x * z + s * y;
	result.m[0][3] = 0.0f;

    result.m[1][0] = t * x * y + s * z;
	result.m[1][1] = t * y * y + c;
	result.m[1][2] = t * y * z - s * x;
	result.m[1][3] = 0.0f;

    result.m[2][0] = t * x * z - s * y;
	result.m[2][1] = t * y * z + s * x;
	result.m[2][2] = t * z * z + c;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result; 
}

float EaseInOut(float x1, float x2, float t) {
	float easedT = -(std::cosf(std::numbers::pi_v<float> * t) - 1.0f) / 2.0f;
	return Lerp(x1, x2, easedT);
}

bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	return (aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) && // x軸
	       (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) && // y軸
	       (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z);   // z軸
}