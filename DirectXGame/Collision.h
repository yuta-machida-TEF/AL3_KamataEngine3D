#pragma once
#include "KamataEngine.h"
#include"MyMath.h"


// 通常のAABB当たり判定
bool IsAABBCollision(const AABB& a, const AABB& b);

// 踏みつけ判定
bool IsStompCollision(const AABB& playerBody, const AABB& enemyHead, float playerVelocityY);
