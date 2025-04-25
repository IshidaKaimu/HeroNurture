#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"

// =======================
// 定数宣言
// =======================
namespace Constant_RaccoonDog 
{
	//初期設定
	const D3DXVECTOR3 INIT_POS    = { 0.0f, 4.5f, 30.0f };	//座標
	const D3DXVECTOR3 INIT_SCALE  = { 0.04f, 0.04f, 0.04f };//拡縮
	const D3DXVECTOR3 INIT_ROTATE = { D3DXToRadian(-110.0f), D3DXToRadian(90.0f), D3DXToRadian(-2.0f) };//回転
	//アニメーション関連
	constexpr float MOVE_SPEED = 0.4f; //移動速度
}


class CRaccoonDog
	: public CHeroBase
{
public:
	CRaccoonDog();
	~CRaccoonDog();
	
	//初期化
	void Initialize() ;

	//ヒーロー登場シーンでのアニメーション
	void AppearanceAnim(float camz);

	//描画関数
	void Draw() override;

private:

};

