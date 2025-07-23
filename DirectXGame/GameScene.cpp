#include "GameScene.h"
#include "CameraController.h"
#include "Enemy.h"
#include "MyMath.h"
#include "Player.h"
#include "DeathParticles.h"
using namespace KamataEngine;

void GameScene::Initialize() { // h(ヘッターファイル)にいれる

	// textureHandle_ = TextureManager::Load("Fruuits.png");

	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	modelskydome_ = Model::CreateFromOBJ("skydome", true);

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(100, 200);

	cube_ = Model::CreateFromOBJ("block");

	// 3Dモデルデータの生成
	model_ = Model::CreateFromOBJ("player", true);

	modelEnemy_ = Model::CreateFromOBJ("enemy", true);

	modelDeath_ = Model::CreateFromOBJ("deathParticle", true);

	// 自キャラの生成
	player_ = new Player();

	mapChipField_ = new MapChipField;

	// 座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(2, 18);
	player_->Initialize(model_, &camera_, playerPosition);

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// カメラの初期化
	camera_.Initialize();

	skydome_ = new Skydome();

	// 自キャラの初期化
	// player_->Initialize(modelPlayer_,&camera_,playerPosition);

	skydome_->Initialize(modelskydome_, &camera_);

	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	GenerateBlocks();

	// カメラコントローラの初期化
	cameraController_ = new CameraController;
	cameraController_->Initialze();
	cameraController_->SetTarget(player_);
	cameraController_->Reset();

	CameraController::Rect cameraArea = {12.0f, 100 - 12.0f, 6.0f, 6.0f};
	cameraController_->SetMovableArea(cameraArea);

	// マップチップフィールドの生成と初期化
	// 自キャラの生成と初期化
	player_->SetMapChipField(mapChipField_);

	// 敵
	for (int32_t i = 0; i < 3; i++) {
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPostion = mapChipField_->GetMapChipPositionByIndex(15, 16 + i);
		newEnemy->initialize(modelEnemy_, &camera_, enemyPostion);

		enemies_.push_back(newEnemy);
	}
	
	// ゲームプレイフェーズ
	phase_ = Phase::kPlay;

}

void GameScene::GenerateBlocks() {
	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	// ブロック1個分の横幅
	// const float kBlockWidth = 2.0f;
	// const float kBlockHeight = 2.0f;
	// 要素数を変更する
	worldTransformBlocks_.resize(numBlockVirtical);

	////キューブの生成
	for (uint32_t i = 0; i < numBlockVirtical; i++) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; i++) {
		for (uint32_t j = 0; j < numBlockHorizontal; j++) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) // 1マス分にボックスの形にしたいなら(i + j)にする
			{
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

void GameScene::CheckAllCollisions() {
#pragma region
	// 判定対象1と2の座標
	AABB aabb1, aabb2;

	// 自キャラの座標
	aabb1 = player_->GetAABB();

	// 自キャラと敵弾全ての当たり判定
	for (Enemy* enemy : enemies_) {
		aabb2 = enemy->GetAABB();

		// AABB同士の交差判定
		if (IsCollision(aabb1, aabb2)) {
			// 自キャラの衝突時間数を呼び出す
			player_->OnCollision(enemy);
			// 敵の衝突時間関数を呼び出す
			enemy->OnCollision(player_);
		}
	}
#pragma endregion
}

void GameScene::ChangePhase() 
{
	switch (phase_) {
	case Phase::kPlay:
		//ゲームプレイフェーズの処理
		if(player_->IsDead()) 
		{
			//死亡演出フェーズに切り替え
			phase_ = Phase::kDeath;
			//自キャラの座標を取得
			//Vector3 deathParticlesPosition = player_->GetWorldPosition();

			// 仮の生成処理。後で削除
			deathParticles_ = new DeathParticles;
			KamataEngine::Vector3 deathParticlesPosition = player_->GetWorldPosition();
			deathParticles_->Initialize(modelDeath_, &camera_, deathParticlesPosition);
		}
		break;
	case Phase::kDeath:
		//デス演出フェーズの処理
		if (deathParticles_ && deathParticles_->IsFinished()) 
		{
			finished_ = true;
		}

		break;
	}
}

GameScene::~GameScene() {
	delete sprite_;

	delete skydome_;

	delete player_;

	// 3Dモデルデータの解放
	delete model_;

	delete debugCamera_;

	// マップチップフィールドの解放
	delete mapChipField_;

	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

	// delete enemy_;
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
	// 行列を定義バッファに転送
	// worldTransform_.TransferMatrix();
	cameraController_->Update();

	for (Enemy* enemy : enemies_) {
		enemy->Update();
	}

	CheckAllCollisions();

	// ブロックの更新
	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			if (!worldTransformBlock) {
				continue;
			}

			// アフィン変換行列の作成

			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

			////定数バッファに転送する

			worldTransformBlock->TransferMatrix();
		}
	}

	// debugCamera_->Update();

#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_0)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}

#endif // _DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else {
		camera_.matView = cameraController_->GetViewProjecttion().matView;
		camera_.matProjection = cameraController_->GetViewProjecttion().matProjection;
		// ビュープロジェクション行列の更新と転送
		camera_.TransferMatrix();
	}

	if(deathParticles_) 
	{
		deathParticles_->Update();
	}

	ChangePhase();
	switch (phase_) 
	{
	case Phase::kPlay:
		//ゲームプレイフェーズの処理
		break;
	case Phase::kDeath:
		//デス演出フェーズの処理
		break;
	}


}

void GameScene::Draw() {

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	// 3Dモデル描画
	//
	// model_->Draw(worldTransform_, camera_, textureHandle_);

	// 自キャラの描画
	player_->Draw();

	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			cube_->Draw(*worldTransformBlock, camera_);
		}
	}

	skydome_->Draw();

	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}

	if (deathParticles_) 
	{
		deathParticles_->Draw();
	}

	// 3Dモデル描画前処理
	Model::PostDraw(); // プログラムの終了
}
