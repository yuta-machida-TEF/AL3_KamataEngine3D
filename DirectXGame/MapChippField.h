#pragma once
#include "KamataEngine.h"

enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {

public:

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);


	//1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;

	//ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

    static inline const uint32_t GetNumBlockVirtical()  { return kNumBlockVirtical; }
	static inline const uint32_t GetNumBlockHorizontal(){ return kNumBlockHorizontal;}

	MapChipData mapChipData_;

};






