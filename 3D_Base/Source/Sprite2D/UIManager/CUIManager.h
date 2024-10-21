#pragma once
#include "Sprite2D/CSprite2D.h"
#include "CDirectX11.h"
#include "SkinMeshObject/Player/CPlayer.h"

class CUIManager
{
public:
	//UIリスト
	enum UIList
	{
		Fade,		//シーン遷移時に使うフェード用の画像
		WhiteFade,  //ごまかしに使う白フェード用画像

		Max,
	};

	//シングルトン化
	static CUIManager* GetInstance() {
		static CUIManager s_Instance;
		return &s_Instance;
	}

public:
	~CUIManager();

	HRESULT Load(CDirectX11* Dx11);

	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }

	static CSprite2D& GetSprite(UIList list) { return *GetInstance()->m_pSprite2D[list]; }

private:
	//シングルトン化
	CUIManager();
	CUIManager(const CUIManager& rhs) = delete;
	CUIManager& operator = (const CUIManager& rhs) = delete;

private:
	CDirectX11* m_pDx11;

	CSprite2D* m_pSprite2D[UIList::Max];

	CPlayer* m_pPlayer;
};

//UIサイズ定数
static const D3DXVECTOR2 TEXTBOXSIZE = { 641.0f, 97.0f };    //テキストボックス
