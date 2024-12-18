#pragma once
#include "Singleton\CSingleton.h"
#include "UIObject\CUIObject.h"
#include "WriteText\WriteText.h"

//ランク構造体
enum enRankList : char 
{
	S,
	A,
	B,
	C,
	D,
	E
};

//=====================================
//汎用クラス
//制作者：石田櫂夢
//=====================================
class CUtility
	: public CSingleton<CUtility>
{
public:
	//アクセス権を与える
    friend class CSingleton<CUtility>;
	~CUtility();

	//乱数の生成
	static int GenerateRandomValue(int min,int max);

	//ランクの表示
	void DrawRank(float value, int typeno, float x, float y);

private:
	CUtility();

private:
	//ランク列挙型
	enRankList m_Rank;
};

