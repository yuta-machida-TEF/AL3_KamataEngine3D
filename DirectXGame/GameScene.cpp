#include "MyMath.h"
#include "GameScene.h"
//#include "Player.h"
using namespace KamataEngine;



void GameScene::Initialize() {//h(ヘッターファイル)にいれる

	//textureHandle_ = TextureManager::Load("Fruuits.png");

	sprite_ = Sprite::Create(textureHandle_, {100,50});

	modelskydome_ = Model::CreateFromOBJ("skydome", true);

	//デバックカメラの生成
	debugCamera_ = new DebugCamera(100,200);

	cube_ = Model::CreateFromOBJ("block");

	//3Dモデルデータの生成
	model_ = Model::CreateFromOBJ("player", true);

	// 自キャラの生成
	player_ = new Player();

	mapChipField_ = new MapChipField;

	//座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1,18);
	player_->Initialize(model_, &camera_, playerPosition);

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//カメラの初期化
	camera_.Initialize();

	

	skydome_ = new Skydome();

	//自キャラの初期化
   // player_->Initialize(modelPlayer_,&camera_,playerPosition);

	skydome_->Initialize(modelskydome_,&camera_);

	

	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	GenerateBlocks();

	//要素数
	//const uint32_t kNumBlockVirtical = 10;
	//const uint32_t kNumBlockHorizontal = 20;
    //ブロック1個分の横幅
	//const float kBlockWidth = 2.0f;
	//const float kBlockHeight = 2.0f;
	////要素数を変更する
	//worldTransformBlocks_.resize(10);

	//////キューブの生成
	//for (uint32_t i = 0; i < 10; i++) 
	//{
	//	worldTransformBlocks_[i].resize(20);		
	//}

	////ブロックの生成
	//for (uint32_t i = 0; i < 10; i++) {
	//	for (uint32_t j = 0; j < 20; j++) {
	//		if ((i + j) % 2 == 0)//1マス分にボックスの形にしたいなら(i + j)にする 
	//		{
	//			continue;
	//		}
	//		worldTransformBlocks_[i][j] = new WorldTransform();
	//		worldTransformBlocks_[i][j]->Initialize();
	//		worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
	//		worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
	//	}
	//}

	
	
}

void GameScene::GenerateBlocks() 
{
	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	// ブロック1個分の横幅
	//const float kBlockWidth = 2.0f;
	//const float kBlockHeight = 2.0f;
	// 要素数を変更する
	worldTransformBlocks_.resize(numBlockVirtical);

	////キューブの生成
	for (uint32_t i = 0; i < numBlockVirtical; i++) 
	{
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; i++) {
		for (uint32_t j = 0; j < numBlockHorizontal; j++) {
			if (mapChipField_->GetMapChipTypeByIndex(j,i) == MapChipType::kBlock) // 1マス分にボックスの形にしたいなら(i + j)にする
			{
				WorldTransform*worldTransform = new WorldTransform();
			    worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}	
		}
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
	
		for (std::vector<KamataEngine::WorldTransform*> &worldTransformBlockLine : worldTransformBlocks_) 
		{
		    for(WorldTransform* worldTransformBlock : worldTransformBlockLine) 
		    {
			    delete worldTransformBlock;
		    }
		}
	    worldTransformBlocks_.clear();

}

void GameScene::Update() 
{
	//自キャラの更新
	player_->Update();
    //行列を定義バッファに転送
	//worldTransform_.TransferMatrix();


	//ブロックの更新
	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			
				if (!worldTransformBlock) 
				{
				continue;
			     }

			// アフィン変換行列の作成

			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

			////定数バッファに転送する
			
				 worldTransformBlock->TransferMatrix();
			
		}
	}

	debugCamera_->Update();

	#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_0))
	{
		isDebugCameraActive_ = !isDebugCameraActive_; 
	}

#endif // _DEBUG

	if (isDebugCameraActive_) 
	{
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else 
	{
		//ビュープロジェクション行列の更新と転送
		camera_.UpdateMatrix();
	}

}

void GameScene::Draw() {

	//DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	
	//3Dモデル描画
	//
	//model_->Draw(worldTransform_, camera_, textureHandle_);

	// 自キャラの描画
	player_->Draw();

	for (std::vector<KamataEngine::WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) 
			{
				continue;
			}
			cube_->Draw(*worldTransformBlock, camera_);
		}
	}
		
	skydome_->Draw();
	

	//3Dモデル描画前処理
	Model::PostDraw();//プログラムの終了

	
	
}
