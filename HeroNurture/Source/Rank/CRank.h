#pragma once
#include "Singleton\CSingleton.h"
#include "UIObject\CUIObject.h"
#include "WriteText\WriteText.h"
#include "Json\CJson.h"
#include <random>
#include <type_traits>

//ランクリスト
enum enRankList : char
{
	S,	//Sランク
	A,	//Aランク
	B,	//Bランク
	C,	//Cランク
	D,  //Dランク
	E   //Eランク
};

//=====================================
//育成ランククラス
//制作者：石田櫂夢
//=====================================
class CRank
	: public CSingleton<CRank>
{
private:
	//アクセス権を与える
	friend class CSingleton<CRank>;
	~CRank();
public:
	//ランクの表示
	void DrawRank(float value, int typeno, float x, float y);

private:
	CRank();

private:
	//ランク列挙型
	enRankList m_Rank;
};
