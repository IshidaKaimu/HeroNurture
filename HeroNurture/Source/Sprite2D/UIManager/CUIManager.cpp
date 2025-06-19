#include "CUIManager.h"
#include "Windows.h"
#include "stdafx\stdafx.h"

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

HRESULT CUIManager::Load(CDirectX11* dx11)
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
	{																		//表示サイズ     //元画像サイズ  //1コマ当たりの表示サイズ
		{UIList::Fade,	         _T("Data\\Texture\\fade.png")			   ,{ 1280.0f,720.0f,1280.0f,720.0f, 0.0f, 0.0f}},
		{UIList::WhiteFade,	     _T("Data\\Texture\\WhiteFade.png")		   ,{ 1280.0f,720.0f,1280.0f,720.0f, 0.0f, 0.0f}},
		{UIList::TitleBack,      _T("Data\\Texture\\TitleBack.png")	       ,{ 534.0f, 200.0f, 534.0f, 200.0f, 534.0f, 200.0f}},
		{UIList::TitleInfoBack,  _T("Data\\Texture\\TitleInfoBack.png")	   ,{ 465.0f, 136.0f, 465.0f, 136.0f, 465.0f, 136.0f}},
		{UIList::BasicBack,      _T("Data\\Texture\\BasicBack.png")	       ,{ 1280.0f,720.0f,1280.0f,720.0f, 1280.0f, 720.0f}},
		{UIList::ModeSelectLeft, _T("Data\\Texture\\ModeSelectLeft.png")   ,{ 640.0f, 720.0f, 640.0f, 720.0f, 640.0f, 720.0f}},
		{UIList::ModeSelectRight,_T("Data\\Texture\\ModeSelectRight.png")  ,{ 640.0f, 720.0f, 640.0f, 720.0f, 640.0f, 720.0f}},
		{UIList::ModeSelectCover,_T("Data\\Texture\\ModeSelectCover.png")  ,{ 640.0f, 720.0f, 640.0f, 720.0f, 640.0f, 720.0f}},
		{UIList::ControlBar,	 _T("Data\\Texture\\ControlBar.png")       ,{ 1280.0f,60.0f, 1280.0f,60.0f, 0.0f,0.0f,}},
		{UIList::PowerTraning,   _T("Data\\Texture\\PowerTraning.png")	   ,{ 290.0, 260.0, 290.0, 260.0, 290.0, 260.0}},
		{UIList::MagicTraning,   _T("Data\\Texture\\MagicTraning.png")	   ,{ 290.0, 260.0, 290.0, 260.0, 290.0, 260.0}},
		{UIList::SpeedTraning,   _T("Data\\Texture\\SpeedTraning.png")	   ,{ 290.0, 260.0, 290.0, 260.0, 290.0, 260.0}},
		{UIList::HpTraning,	     _T("Data\\Texture\\HpTraning.png")		   ,{ 290.0, 260.0, 290.0, 260.0, 290.0, 260.0}},
		{UIList::Rest,	         _T("Data\\Texture\\Rest.png")		       ,{ 290.0, 260.0, 290.0, 260.0, 290.0, 260.0}},
		{UIList::PowerBack,	     _T("Data\\Texture\\PowerTraningBack.png") ,{ 1280.0f,720.0f,1280.0f,720.0f,1280.0f,720.0f}},
		{UIList::MagicBack,	     _T("Data\\Texture\\MagicTraningBack.png") ,{ 1280.0f,720.0f,1280.0f,720.0f,1280.0f,720.0f}},
		{UIList::SpeedBack,	     _T("Data\\Texture\\SpeedTraningBack.png") ,{ 1280.0f,720.0f,1280.0f,720.0f,1280.0f,720.0f}},
		{UIList::HpBack,	     _T("Data\\Texture\\HpTraningBack.png")	   ,{ 1280.0f,720.0f,1280.0f,720.0f,1280.0f,720.0f}},
		{UIList::RestBack,	     _T("Data\\Texture\\RestBack.png")		   ,{ 1280.0f,720.0f,1280.0f,720.0f,1280.0f,720.0f}},
		{UIList::TextBox,	     _T("Data\\Texture\\TextBox.png")		   ,{ 1180.0f,190.0f,1180.0f,190.0f,1180.0f,190.0f}},
		{UIList::ParamList,	     _T("Data\\Texture\\NurtureParamList.png") ,{ 787.0f, 161.0f, 787.0f, 161.0f, 787.0f, 161.0f}},
		{UIList::ResultParamList,_T("Data\\Texture\\ResultParamList.png")  ,{ 178.0f, 472.0f, 178.0f, 472.0f, 178.0f, 472.0f}},
		{UIList::StaminaGauge,	 _T("Data\\Texture\\Stamina.png")		   ,{ 602.0f, 54.0f,  602.0f, 54.0f,  602.0f, 54.0f}},
		{UIList::StaminaBack,	 _T("Data\\Texture\\StaminaBack.png")      ,{ 602.0f, 54.0f,  602.0f, 54.0f,  602.0f, 54.0f}},
		{UIList::StaminaFrame,	 _T("Data\\Texture\\StaminaFrame.png")     ,{ 700.0f, 72.0f,  700.0f, 72.0f,  700.0f, 72.0f}},
		{UIList::TurnBack,	     _T("Data\\Texture\\TurnFrame.png")        ,{ 421.0f, 121.0f, 421.0f, 121.0f, 421.0f, 121.0f}},
		{UIList::HpGauge,	     _T("Data\\Texture\\HpGauge.png")		   ,{ 602.0f, 54.0f,  602.0f, 54.0f,  602.0f, 54.0f}},
		{UIList::EnemyHpGauge,	 _T("Data\\Texture\\EnemyHpGauge.png")	   ,{ 602.0f, 54.0f,  602.0f, 54.0f,  602.0f, 54.0f}},
		{UIList::HpGaugeBack,	 _T("Data\\Texture\\HpGaugeBack.png")      ,{ 602.0f, 54.0f,  602.0f, 54.0f,  602.0f, 54.0f}},
		{UIList::GaugeFrame,	 _T("Data\\Texture\\GaugeFrame.png")       ,{ 602.0f, 70.0f,  602.0f, 70.0f,  602.0f, 70.0f}},
		{UIList::GaugeDecrease,	 _T("Data\\Texture\\GaugeDecrease.png")    ,{ 602.0f, 54.0f,  602.0f, 54.0f,  602.0f, 54.0f}},
		{UIList::PowerAttack,	 _T("Data\\Texture\\PowerAttack.png")      ,{ 341.0f, 300.0f, 341.0f, 300.0f, 341.0f, 300.0f}},
		{UIList::MagicAttack,	 _T("Data\\Texture\\MagicAttack.png")      ,{ 340.0f, 300.0f, 340.0f, 300.0f, 340.0f, 300.0f}},
		{UIList::AttackCover,	 _T("Data\\Texture\\AttackCover.png")      ,{ 341.0f, 300.0f, 341.0f, 300.0f, 341.0f, 300.0f}},
		{UIList::Arrow,	         _T("Data\\Texture\\Arrow.png")            ,{ 137.0f, 93.0f,  137.0f, 93.0f,  137.0f, 93.0f}},
		{UIList::SelectArrow,	 _T("Data\\Texture\\SelectArrow.png")      ,{ 125.0f, 111.0f, 125.0f, 111.0f, 125.0f, 111.0f}},
		{UIList::NameSpace,	     _T("Data\\Texture\\NameSpace.png")        ,{ 1347.0f, 336.0f, 1347.0f, 336.0f, 1347.0f, 336.0f}},
		{UIList::Safe,			 _T("Data\\Texture\\Safe.png")             ,{ 314.0f, 299.0f, 314.0f, 299.0f, 314.0f, 299.0f}},
		{UIList::Anxiety,	     _T("Data\\Texture\\Anxiety.png")          ,{ 314.0f, 299.0f, 314.0f, 299.0f, 314.0f, 299.0f}},
		{UIList::Danger,	     _T("Data\\Texture\\Danger.png")           ,{ 316.0f, 301.0f, 316.0f, 301.0f, 316.0f, 301.0f}},
	};

	int list_max = sizeof(SList) / sizeof(SList[0]);
	for (int i = 0; i < list_max; i++)
	{
		if (m_pSprite2D[SList[i].listNo]->Init(
			*dx11, SList[i].path, SList[i].Ss) == E_FAIL)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

