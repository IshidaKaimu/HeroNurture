#pragma once
#include <vector>
using namespace std;

class CKeyManager
{
public:
	//インスタンス取得(唯一のアクセス経路).
	static CKeyManager* GetInstance()
	{
		//唯一のインスタンス生成.
		static CKeyManager s_Instance;
		return &s_Instance;
	}

	~CKeyManager();

	void Update();

	//キーが離されたとき
	bool IsUp(int input);
	//キーが押されたとき
	bool IsDown(int input);
	//キーが押し続けられているとき
	bool IsKeep(int input);

	bool KeyCore(int input,vector<int> keymax);

private:
	CKeyManager();
	CKeyManager(const CKeyManager& rhs) = delete;
	CKeyManager& operator = (const CKeyManager& rhs) = delete;

private:
	//過去に押されていたキーを格納する配列
	vector<int> m_OldKeys;
	//現在押されているキーを格納する配列
	vector<int> m_NowKeys;
};

