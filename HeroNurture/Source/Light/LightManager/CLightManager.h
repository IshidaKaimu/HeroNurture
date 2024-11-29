#pragma once
#include "Global\Global.h"
#include "Singleton\CSingleton.h"
class CLightManager
	: public CSingleton<CLightManager>
{
public:
	//フレンド宣言でアクセス権を与える.
	friend class CSingleton<CLightManager>;
	~CLightManager();

public:
	//----ゲッター----
	//ライト情報の取得
	LIGHT GetLight() { return m_Light; }

private:
	//他からアクセスされることがないように
	CLightManager();

private:
	//ライト情報
	LIGHT m_Light;
};

