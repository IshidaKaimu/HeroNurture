#pragma once
#include "Singleton\CSingleton.h"

//=====================================
//バトルモードマネージャークラス
//制作者：石田櫂夢
//=====================================
class CBattleManager
	: public CSingleton<CBattleManager>
{
private:
	//フレンド宣言
	//アクセス権を与える
	friend class CSingleton<CBattleManager>;
	~CBattleManager();
public:

	//勝敗リスト
	enum enBattleResultList
	{
		Win,
		Lose,
	};

private:
	CBattleManager();
public:
	
	//---ゲッター・セッター---
	//勝敗
	enBattleResultList GetBattleResult() { return m_BattleResult; }
	void SetBattleResult(enBattleResultList result) { m_BattleResult = result; }

private:

	//----列挙型----
	//勝敗リスト
	enBattleResultList m_BattleResult;
};
