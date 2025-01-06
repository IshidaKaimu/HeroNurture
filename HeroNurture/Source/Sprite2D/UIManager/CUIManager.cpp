#include "CUIManager.h"
CUIManager::CUIManager()
	: m_pSprite2D()

{
}

CUIManager::~CUIManager()
{
	for (int i = UIList::Max - 1; i >= 0; i--) {
		SAFE_DELETE(m_pSprite2D[i]);
	}

	//インスタンス破棄
	m_pDx11 = nullptr;
}

HRESULT CUIManager::Load(CDirectX11* Dx11)
{
	for (int i = 0; i < UIList::Max; i++) {
		m_pSprite2D[i] = new CSprite2D();
	}

	struct Sprite2DList
	{
		int listNo;
		LPCTSTR path;
		CSprite2D::SPRITE_STATE Ss;
	};

	Sprite2DList SList[] =
	{                                                                    //表示サイズ       //元画像サイズ   //1コマ当たりの表示サイズ
		{UIList::Fade,	         _T("Data\\Texture\\fade.png")			 ,{ 1280.0f, 720.0f, 1280.0f, 720.0f, 0.0f, 0.0f,}},
		{UIList::WhiteFade,	     _T("Data\\Texture\\WhiteFade.png")		 ,{ 1280.0f, 720.0f, 1280.0f, 720.0f, 0.0f, 0.0f,}},
		{UIList::PowerTraning,   _T("Data\\Texture\\PowerTraning.png")	 ,{ 290.0, 260.0, 290.0, 260.0, 290.0, 260.0,}},
		{UIList::MagicTraning,   _T("Data\\Texture\\MagicTraning.png")	 ,{ 290.0, 260.0, 290.0, 260.0, 290.0, 260.0,}},
		{UIList::SpeedTraning,   _T("Data\\Texture\\SpeedTraning.png")	 ,{ 290.0, 260.0, 290.0, 260.0, 290.0, 260.0,}},
		{UIList::HpTraning,	     _T("Data\\Texture\\HpTraning.png")		 ,{ 290.0, 260.0, 290.0, 260.0, 290.0, 260.0,}},
		{UIList::Rest,	         _T("Data\\Texture\\Rest.png")		 ,{ 290.0, 260.0, 290.0, 260.0, 290.0, 260.0,}},
		{UIList::ParamList,	     _T("Data\\Texture\\NatureParamList.png"),{ 787.0f, 161.0f, 787.0f, 161.0f, 787.0f, 161.0f,}},
		{UIList::ResultParamList,_T("Data\\Texture\\ResultParamList.png"),{ 400.0f, 600.0f, 400.0f, 600.0f, 400.0f, 600.0f,}},
		{UIList::StaminaGage,	 _T("Data\\Texture\\Stamina.png")		 ,{ 602.0f, 54.0f,  602.0f, 54.0f,  602.0f, 54.0f,}},
		{UIList::StaminaBack,	 _T("Data\\Texture\\StaminaBack.png")    ,{ 602.0f, 54.0f,  602.0f, 54.0f,  602.0f, 54.0f}}
	};

	int list_max = sizeof(SList) / sizeof(SList[0]);
	for (int i = 0; i < list_max; i++)
	{
		if (m_pSprite2D[SList[i].listNo]->Init(
			*Dx11, SList[i].path, SList[i].Ss) == E_FAIL)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

