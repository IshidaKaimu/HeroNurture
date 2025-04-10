#pragma once
#include <vector>
#include "Singleton\CSingleton.h"
using namespace std;

//=====================================
// キー入力マネージャークラス
// 制作者:石田櫂夢
//=====================================

class CKeyManager
	: public CSingleton<CKeyManager>
{
private:
	friend class CSingleton<CKeyManager>;
	~CKeyManager();

public:
	//更新処理
	void Update();

	//キーが離されたとき
	bool IsUp(int input);
	//キーが押されたとき
	bool IsDown(int input);
	//キーが押し続けられているとき
	bool IsKeep(int input);

	bool KeyCore(int input,vector<int> keymax);

private:
	//他からアクセスされることがないように
	CKeyManager();
private:
	//過去に押されていたキーを格納する配列
	vector<int> m_OldKeys;
	//現在押されているキーを格納する配列
	vector<int> m_NowKeys;
};

