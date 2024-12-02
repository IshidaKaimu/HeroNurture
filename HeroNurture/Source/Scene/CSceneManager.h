#pragma once
#include "CSceneBase.h"
#include "CDirectX11.h"
#include "CDirectX9.h"
#include <memory>

//----前方宣言---
class CTitle;
class CHeroSelect;
class CNatureScene;
class CTraning;

class CSceneManager
	: public CSceneBase
{
public:
	//シーンリスト列挙型
	enum enSceneList
	{
		SceneSelect = 0,
		GameMain,
		Nature,
		Training,
		Max,
		none = -1,
	};

public:
	static CSceneManager* GetInstance() {
		static CSceneManager s_Instance;
		return &s_Instance;
	}

	~CSceneManager() ;

	//構築関数
    void Create(CDirectX9& pDx9, CDirectX11& pDx11, HWND hwnd);

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

	//読み込み回数制限フラグの操作
	void IsDataLoaded(bool loaded) { m_Scene->IsDataLoaded(loaded); }

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
	//読み込み回数制限フラグの取得
	bool GetIsDataLoaded() { return m_Scene->GetIsDataLoaded(); }


private:
	CSceneManager();
	CSceneManager(const CSceneManager& rhs) = delete;
	CSceneManager& operator = (const CSceneManager& rhs) = delete;
private:
	std::unique_ptr<CSceneBase> m_Scene;	//ユニークポインタ

    HWND        m_hWnd;    //ウィンドウハンドル
    CDirectX9*  m_pDx9;	   //DirectX9
    CDirectX11* m_pDx11;   //DirectX11

};
