#pragma once
#include "Singleton\CSingleton.h"
#include "UIObject\CUIObject.h"
#include "WriteText\WriteText.h"
#include "Json\CJson.h"

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
//汎用クラス
//制作者：石田櫂夢
//=====================================
class CUtility
	: public CSingleton<CUtility>
{
private:
	//アクセス権を与える
	friend class CSingleton<CUtility>;
	~CUtility();
public:

	//乱数の生成
	static int GenerateRandomValue(int min,int max);

	//ランクの表示
	void DrawRank(float value, int typeno, float x, float y);

	//値の桁数による描画位置の補正
	D3DXVECTOR2 PosCorrection(double value, float digit, float x, float y);

private:
	CUtility();

private:
	//ランク列挙型
	enRankList m_Rank;
};

