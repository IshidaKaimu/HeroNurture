#pragma once
#include "Singleton\CSingleton.h"

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

private:
	CUtility();

};

