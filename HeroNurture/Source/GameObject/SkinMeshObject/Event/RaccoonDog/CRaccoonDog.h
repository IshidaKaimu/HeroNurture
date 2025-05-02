#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
// =======================
// 前方宣言
// =======================
//エフェクト
class CEffect;

// =======================
// 定数宣言
// =======================
namespace Constant_RaccoonDog 
{
	//----初期設定----
	const D3DXVECTOR3 INIT_POS       = { 0.0f, 4.5f, 30.0f };	//座標
	const D3DXVECTOR3 INIT_SCALE     = { 0.04f, 0.04f, 0.04f }; //拡縮
	const D3DXVECTOR3 INIT_ROTATE    = { D3DXToRadian(-110.0f), D3DXToRadian(90.0f), D3DXToRadian(-2.0f) };//回転
	const D3DXVECTOR3 UPRIGHT_ROTATE = { D3DXToRadian(-100.0f), D3DXToRadian(90.0f), D3DXToRadian(-2.0f) };//直立時の回転
	//----アニメーション関連----
	//タヌキ
	constexpr float MOVE_SPEED = 0.2f; //移動速度
	constexpr float MAX_UP     = 5.0f; //上下の動きの高さ上限
	constexpr float UP_SPEED   = 0.04f;//上下の動きの速さ
	constexpr int   HIDDEN_TIME= 190;  //非表示にするタイミング
	//煙エフェクト
	constexpr int   STEAM_TIME = 120;  //再生までの時間
	constexpr float STEAM_DELAY= 5.0f; //タヌキからずらす値
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
public:
	//タヌキが非表示になったフラグの取得
	bool GetHiddenFlag() { return m_HiddenFlag; }

private:
	//上下の動き
	void UpDown();

private:
	//----フラグ----
	//タヌキがカメラに到達したか
	bool m_ReachCamFlag;
	//非表示
	bool m_HiddenFlag;
	//体を上下させる動き
	bool m_Up;
};

