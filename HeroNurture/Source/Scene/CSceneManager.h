#pragma once
#include "CSceneBase.h"
#include "CDirectX11.h"
#include "CDirectX9.h"
#include "Singleton\CSingleton.h"
#include "Utility\CUtility.h"
#include <memory>


//----前方宣言---
class CTitleScene;
class CModeSelect;
class CNurtureHeroSelectScene;
class CNurtureScene;
class CTraningScene;
class CTraningResultScene;
class CBattleHeroSelectScene;
class CYuiAppearanceScene;
class CBattleScene;
class CBattleResultScene;

//=====================================
//シーンマネージャークラス
//制作者：石田櫂夢
//=====================================
class CSceneManager
	: public CSceneBase
	, public CSingleton<CSceneManager>
{
private:
	//フレンド宣言
	//アクセス権を与える
	friend class CSingleton<CSceneManager>;
	~CSceneManager();
public:
	//シーンリスト
	enum enSceneList :char
	{
		Title,
		CreateAcount,
		Login,
		ModeSelect,
		NurtureHeroSelect,
		Nurture,
		Training,
		NurtureResult,
		BattleHeroSelect,
		YuiAppearance,
		KaitoAppearance,
		Battle,
		UniqueAttack,
		BattleResult,
		Max_S,
		none,
	};

	//勝敗リスト
	enum enBattleResultList
	{
		Win,
		Lose,
	};

public:
	//構築関数
    void Create(CDirectX9& pDx9, CDirectX11& pDx11, HWND hwnd);

	//破棄関数
	void Release();

	//初期化関数
	void Initialize();

	//更新関数
	void Update();
	
	//描画関数
	void Draw();

	//各シーンの構築、データ読み込み
	void LoadCreate(enSceneList List);	

	//シーン構築関数
	static std::unique_ptr<CSceneBase> Create(enSceneList List);
private:
	//他からアクセスされることがないように
	CSceneManager();

public:
	//白フェード関連の初期化
	void InitWhiteFade() { m_Scene->InitWhiteFade(); }

	//白フェードの再生
	void PlayWhiteFade(int max, float speed, float alpha) { m_Scene->PlayWhiteFade(max, speed, alpha); }

	//---ゲッター・セッター---
    //DirectX9
    CDirectX9* GetDx9()			 { return m_pDx9; }
	void SetDx9( CDirectX9& Dx9) { m_pDx9 = &Dx9; }
    //DirectX11
	CDirectX11* GetDx11()		   { return m_pDx11; }
	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }
    //ウィンドウハンドル
    HWND GetWnd()			{ return m_hWnd; }
    void SetWnd(HWND m_wnd) { m_hWnd = m_wnd; }
	//ユーザー名
	std::wstring GetName() { return m_UserName; } //wstring型
	std::string GetStringName() { return CUtility::GetInstance().WstringToString(m_UserName); } //string型
	void SetName(std::wstring name) { m_UserName = name; }


private:
	//ユニークポインタ
	std::unique_ptr<CSceneBase> m_Scene;
	//ウィンドウハンドル
    HWND        m_hWnd;
	//DirectX9
    CDirectX9*  m_pDx9;
	//DirectX11
    CDirectX11* m_pDx11;  
	
	//ユーザー名
	std::wstring m_UserName;
};
