#pragma once
#include "CSceneBase.h"
#include "CDirectX11.h"
#include "CDirectX9.h"
#include <memory>

//----前方宣言---
class CTitleScene;
class CModeSelect;
class CNatureHeroSelectScene;
class CNatureScene;
class CTraningScene;
class CTraningResultScene;
class CBattleScene;
class CBattleResultScene;

//育成ターン数
constexpr int MAX_TURN = 35;

//=====================================
//シーンマネージャークラス
//制作者：石田櫂夢
//=====================================
class CSceneManager
	: public CSceneBase
{
public:
	//シーンリスト
	enum enSceneList :char
	{
		Title,
		ModeSelect,
		NatureHeroSelect,
		Nature,
		Training,
		NatureResult,
		BattleHeroSelect,
		Battle,
		UniqueAttack,
		BattleResult,
		Max_S,
		none,
	};


	//役割リスト
	enum enRoleList :char
	{
		Hero,
		EnemyHero,
	};

	//勝敗リスト
	enum enBattleResultList
	{
		Win,
		Lose,
	};

public:
	static CSceneManager* GetInstance() {
		static CSceneManager s_Instance;
		return &s_Instance;
	}

	~CSceneManager() ;

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

public:
	//読み込み回数制限フラグの操作
	void SetIsDataLoaded(bool loaded) { m_IsDataLoaded = loaded; }

	//----育成経過ターン関連関数----
	//ターン数の経過
	void TurnProgress() { m_Turn--; }
	//ターン数の初期化
	void InitTurn() { m_Turn = MAX_TURN; }

	//スタミナゲージの幅の初期化
	void InitStaminaWidth() { m_GageWidth = 1.0f; }

	//白フェード関連の初期化
	void InitWhiteFade() { m_Scene->InitWhiteFade(); }

	//白フェードの再生
	void PlayWhiteFade(int max, float speed, float alpha) { m_Scene->PlayWhiteFade(max, speed, alpha); }

	//---ゲッター・セッター---
    //DirectX9
    CDirectX9* GetDx9() { return m_pDx9; }
	void SetDx9( CDirectX9& Dx9) { m_pDx9 = &Dx9; }
    //DirectX11
	CDirectX11* GetDx11() { return m_pDx11; }
	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }
    //ウィンドウハンドル
    HWND GetWnd() { return m_hWnd; }
    void SetWnd(HWND m_wnd) { m_hWnd = m_wnd; }
	//読み込み回数制限フラグ
	bool GetIsDataLoaded() { return m_IsDataLoaded; }
	//ターン数
	int GetRemainingTurn() { return m_Turn; }
	//スタミナゲージの幅
	float GetStaminaWidth() { return m_GageWidth; }
	void  SetStaminaWidth(float width) { m_GageWidth = width; }
	//休息フラグ
	bool GetRestFlag() { return m_Rest; }
	void SetRestFlag(bool rest) { m_Rest = rest; }
	//役割
	enRoleList GetRole() { return m_RoleList; }
	void SetRole(enRoleList role) { m_RoleList = role; }
	//勝敗
	enBattleResultList GetBattleResult() { return m_BattleResult; }
	void SetBattleResult( enBattleResultList result ) { m_BattleResult = result; }

private:
	CSceneManager();
	CSceneManager(const CSceneManager& rhs) = delete;
	CSceneManager& operator = (const CSceneManager& rhs) = delete;
private:
	//ユニークポインタ
	std::unique_ptr<CSceneBase> m_Scene;
	//ウィンドウハンドル
    HWND        m_hWnd;
	//DirectX9
    CDirectX9*  m_pDx9;
	//DirectX11
    CDirectX11* m_pDx11;  

	//----列挙型----
	//役割リスト
	enRoleList  m_RoleList;
	//勝敗リスト
	enBattleResultList m_BattleResult;

	//残りターン数
	int         m_Turn;



	// =======================
	// フラグ
	// =======================		
	//休息を選択したかのフラグ
	bool m_Rest;
	//データ読み込みが初回かどうかのフラグ
	bool m_IsDataLoaded;


	//スタミナゲージの幅
	float m_GageWidth;

};
