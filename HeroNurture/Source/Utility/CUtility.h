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
	//テンプレート関数(引数の方に応じて処理を変える)
	template <typename T>
	static T GenerateRandomValue(T min, T max) 
	{
		//シード値
		std::random_device rd;
		//乱数生成器
		std::mt19937 gen(rd());

		//引数が整数型であった場合
		if constexpr (std::is_integral<T>::value) {
			//分布に乱数生成器を渡すことで乱数の範囲を指定
			std::uniform_int_distribution<T> rand_val(min, max);
			return rand_val(gen);
		}
		else if constexpr (std::is_floating_point<T>::value)
		{
			//分布に乱数生成器を渡すことで乱数の範囲を指定
			std::uniform_real_distribution<T> rand_val(min, max);
			return rand_val(gen);
		}

	}

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
