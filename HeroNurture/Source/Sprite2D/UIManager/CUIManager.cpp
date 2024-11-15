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

	//�C���X�^���X�j��
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

	{                                                                //�\���T�C�Y      //���摜�T�C�Y  //1�R�}������̕\���T�C�Y
		{UIList::Fade,	    _T("Data\\Texture\\fade.png")			,{ 1280.0f, 720.0f, 1280.0f, 720.0f, 0.0f, 0.0f,}},
		{UIList::WhiteFade,	_T("Data\\Texture\\WhiteFade.png")		,{ 1280.0f, 720.0f, 1280.0f, 720.0f, 0.0f, 0.0f,}},
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

