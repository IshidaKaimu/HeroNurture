#pragma once
#include "Singleton\CSingleton.h"
#include "Utility\CUtility.h"

// =======================
// 定数宣言
// =======================
//育成ターン数
constexpr int MAX_TURN = 50;


//=====================================
//育成モードマネージャークラス
//制作者：石田櫂夢
//=====================================
class CNurtureManager
	: public CSingleton<CNurtureManager>
{
private:
	//フレンド宣言
	//アクセス権を与える
	friend class CSingleton<CNurtureManager>;
	~CNurtureManager();
public:

private:
	CNurtureManager();
public:

	//読み込み回数制限フラグの操作
	void SetIsDataLoaded(bool loaded) { m_IsDataLoaded = loaded; }

	//----育成経過ターン関連関数----
	//ターン数の経過
	void TurnProgress() { m_Turn--; }
	//ターン数の初期化
	void InitTurn() { m_Turn = MAX_TURN; }

	//スタミナゲージの幅の初期化
	void InitStaminaWidth() { m_GageWidth = 1.0f; }

	//----ゲッター・セッター----
	//読み込み回数制限フラグ
	bool GetIsDataLoaded() { return m_IsDataLoaded; }
	//ターン数
	int GetRemainingTurn() { return m_Turn; }
	//スタミナゲージの幅
	float GetStaminaWidth() { return m_GageWidth; }
	void  SetStaminaWidth(float width) { m_GageWidth = width; }
	//休息フラグ
	bool GetRestFlag() { return m_Rest; }
	void SetRestFlag(bool rest) { m_Rest = rest; }

private:
	//残りターン数
	int         m_Turn;

	//スタミナゲージの幅
	float m_GageWidth;

	//----フラグ----
	//休息を選択したかのフラグ
	bool m_Rest;
	//データ読み込みが初回かどうかのフラグ
	bool m_IsDataLoaded;
};
