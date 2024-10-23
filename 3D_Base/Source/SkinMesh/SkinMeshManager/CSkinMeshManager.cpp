#include "CSkinMeshManager.h"

CSkinMeshManager::CSkinMeshManager()
	: m_pDx11()
	, m_pDx9()
	, m_pSkinMesh()
{
}

CSkinMeshManager::~CSkinMeshManager()
{
	for (int i = SkinMeshList::Max - 1; i >= 0; i--) {
		SAFE_DELETE(m_pSkinMesh[i]);
	}

	m_pDx9 = nullptr;
	m_pDx11 = nullptr;
}

HRESULT CSkinMeshManager::Load(CDirectX9* pdx9, CDirectX11* pdx11)
{
	for (int i = 0; i < SkinMeshList::Max; i++) {
		m_pSkinMesh[i] = new CSkinMesh();
	}
	struct SKMeshList
	{
		int listNo;
		LPCTSTR path;
	};

	SKMeshList SKMList[] =
	{
		{ SkinMeshList::Player,        _T("Data\\Mesh\\Skin\\Yui\\Yui.x") },
		{ SkinMeshList::Wooo,          _T("Data\\Mesh\\Skin\\wooo\\wooo.x") },
		{ SkinMeshList::Boss,          _T("Data\\Mesh\\Skin\\Boss\\ultemate_s.x") },
		{ SkinMeshList::FastBoss,      _T("Data\\Mesh\\Skin\\FastBoss\\a_s.x") },

	};

	int list_max = sizeof(SKMList) / sizeof(SKMList[0]);

	for (int i = 0; i < list_max; i++)
	{
		if (m_pSkinMesh[SKMList[i].listNo]->Init(
			*pdx9, *pdx11, SKMList[i].path) == E_FAIL)
		{
			return E_FAIL;
		}
	}


	return S_OK;
}

