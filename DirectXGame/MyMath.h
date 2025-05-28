#pragma once

#include "KamataEngine.h"

//<summary>
//アフィン変換
//</summary>
KamataEngine::Matrix4x4 MakeAffineMatrix(KamataEngine::Vector3& scale,
KamataEngine::Vector3& roteaion, KamataEngine::Vector3& translation);
//イージング
float EaseInOut(float x1, float x2, float t);
