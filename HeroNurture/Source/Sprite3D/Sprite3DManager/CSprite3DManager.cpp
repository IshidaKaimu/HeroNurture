#include "CSprite3DManager.h"



CSprite3DManager::CSprite3DManager()
	: m_pSprite3D()
{
}

CSprite3DManager::~CSprite3DManager()
{
	for (int i = Sprite3DList::Max - 1; i >= 0; i--) {
		SAFE_DELETE(m_pSprite3D[i]);
	}

	m_pDx11 = nullptr;
}

HRESULT CSprite3DManager::Load(CDirectX11* dx11)
{
	for (int i = 0; i < Sprite3DList::Max; i++) {
		m_pSprite3D[i] = new CSprite3D();
	}

	struct Spr3List
	{
		int listNo;
		LPCTSTR path;
		CSprite3D::SPRITE_STATE Ss;
	};


	Spr3List SList[] =
	{                                                                          //表示サイズ    //元画像サイズ  //1コマ当たりの表示サイズ
		Sprite3DList::BackGround,   _T("Data\\Texture\\Back.png"),            { 1280.0f,720.0f,1280.0f,720.0f, 1280.0f, 720.0f } ,
	};

	int list_max = sizeof(SList) / sizeof(SList[0]);
	for (int i = 0; i < list_max; i++)
	{
		if (m_pSprite3D[SList[i].listNo]->Init(
			*dx11,SList[i].path, SList[i].Ss) == E_FAIL)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

