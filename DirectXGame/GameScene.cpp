
#include "GameScene.h"
#include "CameraController.h"
#include "Clear.h"
#include "DeathParticles.h"
#include "Enemy.h"
#include "MyMath.h"
#include "Player.h"
using namespace KamataEngine;

void GameScene::Initialize() { // h(ヘッターファイル)にいれる

	textureHandle_ = TextureManager::Load("A.png");

	gameOverHandle_ = TextureManager::Load("B.png");

	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	sprite2_ = Sprite::Create(gameOverHandle_, {100, 50});

	modelskydome_ = Model::CreateFromOBJ("skydome", true);

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(100, 200);

	cube_ = Model::CreateFromOBJ("block");

	// 3Dモデルデータの生成
	model_ = Model::CreateFromOBJ("player", true);

	modelEnemy_ = Model::CreateFromOBJ("enemy", true);

	HaitiEnemy_ = Model::CreateFromOBJ("enemy", true);

	modelDeath_ = Model::CreateFromOBJ("deathParticle", true);

	clearModel_ = Model::CreateFromOBJ("clear", true);

	soundDataHandle_ = Audio::GetInstance()->LoadWave("DEAD_HEAT_MAX.mp3");

	// 音声再生
	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);

	// 自キャラの生成
	player_ = new Player();

	mapChipField_ = new MapChipField;

	// 座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(2, 17);
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

	// 敵
	for (int32_t i = 0; i < 10; i++) {
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPostion = mapChipField_->GetMapChipPositionByIndex(0, 9 + i);
		newEnemy->initialize(modelEnemy_, &camera_, enemyPostion);

		enemies_.push_back(newEnemy);
	}

	// Clear* newClear = new Clear();
	Vector3 clearPostion = mapChipField_->GetMapChipPositionByIndex(2, 20);
	// clear_->Initialize(clearModel_, &camera_, clearPostion);
	// enemies_.push_back(newClear);

	// ゲームプレイフェーズ
	phase_ = Phase::kFadeIn;

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 2.0f);
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
	//aabb1 = player_->GetAABB();

	// 自キャラと敵弾全ての当たり判定
	for (Enemy* enemy : enemies_) {
		aabb2 = enemy->GetAABB();

		// AABB同士の交差判定
		if (IsCollision(aabb1, aabb2)) {
			// 自キャラの衝突時間数を呼び出す
			//player_->OnCollision(enemy);
			// 敵の衝突時間関数を呼び出す
			enemy->OnCollision(player_);
		}
	}
#pragma endregion
}

void GameScene::ChangePhase() {

	switch (phase_) {

	case Phase::kFadeIn:
		if (fade_->IsFinished()) {
			// ゲームプレイへ切り替え
			phase_ = Phase::kPlay;
		}
		break;
	case Phase::kPlay:

		Vector3 worldPos = player_->GetWorldPosition();

		if (worldPos.x >= 97) {
			fade_->Start(Fade::Status::FadeOut, 2.0f);
			phase_ = Phase::kFadOut;
			isClear_ = true;
		}

		/*fade_ = new Fade();
		fade_->Initialize();
		fade_->Start(Fade::Status::FadeIn, 6.0f);*/

		// ゲームプレイフェーズの処理
		if (player_->IsDead()) {
			// 死亡演出フェーズに切り替え
			phase_ = Phase::kDeath;
			// 自キャラの座標を取得
			// Vector3 deathParticlesPosition = player_->GetWorldPosition();

			// 仮の生成処理。後で削除
			deathParticles_ = new DeathParticles;
			KamataEngine::Vector3 deathParticlesPosition = player_->GetWorldPosition();
			deathParticles_->Initialize(modelDeath_, &camera_, deathParticlesPosition);
		}
		break;
	case Phase::kDeath:
		// デス演出フェーズの処理
		if (deathParticles_ && deathParticles_->IsFinished()) {
			fade_->Start(Fade::Status::FadeOut, 2.0f);
			phase_ = Phase::kFadOut;
		}
		break;

	case Phase::kFadOut:
		if (fade_->IsFinished()) {
			Audio::GetInstance()->StopWave(voiceHandle_);
			// シーン終了へ
			finished_ = true;
		}
		break;
	}
}

GameScene::~GameScene() {
	delete sprite_;

	delete sprite2_;

	delete skydome_;

	delete player_;

	delete clear_;

	// 3Dモデルデータの解放
	delete model_;

	delete debugCamera_;

	// マップチップフィールドの解放
	delete mapChipField_;
	// フェード
	delete fade_;

	delete clearModel_;

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
	// フェード
	fade_->Update();
	switch (phase_) {
	case GameScene::Phase::kPlay:
		break;

	case GameScene::Phase::kDeath:
		break;

	case GameScene::Phase::kFadeIn:
		// フェード
		// fade_->Update();
		break;
	case GameScene::Phase::kFadOut:
		// フェード
		// fade_->Update();
		break;
	default:
		break;
	}

	// 自キャラの更新
	player_->Update();
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

	if (deathParticles_) {
		deathParticles_->Update();
	}

	// clearModel_->

	// デスパーティクルが終了したらシーンを終了する
	/*if (deathParticles_ && deathParticles_->IsFinished())
	{
	    phase_ = Phase::kFadOut;
	    fade_->Start(Fade::Status::FadeOut, 1.0f);
	}*/

	ChangePhase();
	switch (phase_) {
	case Phase::kPlay:
		// ゲームプレイフェーズの処理
		break;
	case Phase::kDeath:
		// デス演出フェーズの処理
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
	if (phase_ == Phase::kPlay || phase_ == Phase::kFadeIn) {
		player_->Draw();
	}

	/*for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			cube_->Draw(*worldTransformBlock, camera_);
		}
	}*/

	skydome_->Draw();

	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}

	if (deathParticles_) {
		deathParticles_->Draw();
	}

	// clear;

	// 3Dモデル描画前処理
	Model::PostDraw(); // プログラムの終了

	fade_->Draw();
}
