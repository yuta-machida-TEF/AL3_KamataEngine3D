#include "Collision.h"
#include"MyMath.h"

bool IsStompCollision(const AABB& playerBody, const AABB& enemyHead, float playerVelocityY) {
	// 上昇中は踏みつけ無効
	if (playerVelocityY >= 0.0f) {
		return false;
	}

	// 頭と体が当たっていない
	if (!IsAABBCollision(playerBody, enemyHead)) {
		return false;
	}

	// 上から踏んでいるか
	float playerBottom = playerBody.min.y;
	float enemyHeadTop = enemyHead.max.y;

	const float tolerance = 0.1f;
	if (playerBottom >= enemyHeadTop - tolerance) {
		return true;
	}

	return false;
}
