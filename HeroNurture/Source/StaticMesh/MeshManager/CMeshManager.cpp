#include "CMeshManager.h"

CMeshManager::CMeshManager()
	: m_pDx11		()
	, m_pDx9		()
	, m_pStaticMesh	()
{	
}

CMeshManager::~CMeshManager()
{
	for (int i = MeshList::Max - 1; i >= 0; i--) {
		SAFE_DELETE(m_pStaticMesh[i]);
	}

	m_pDx9 = nullptr;
	m_pDx11 = nullptr;
}

HRESULT CMeshManager::Load(CDirectX9* pdx9, CDirectX11* pdx11)
{
	//スカイボックスのメッシュの作成
	m_pSkyMesh = std::make_unique<CSkyMesh>();


	for (int i = 0; i < MeshList::Max; i++) {
		m_pStaticMesh[i] = new CStaticMesh();
	}
	struct StaticMeshList
	{
		int listNo;
		LPCTSTR path;
	};


    StaticMeshList MList[] =
    {
        { MeshList::Ground,                 _T("Data\\Mesh\\Static\\Ground\\Ground.x")     },
        { MeshList::Sky,                    _T("Data\\Mesh\\Static\\Sky\\BlueSky.x")       },
    };

	int list_max = sizeof(MList) / sizeof(MList[0]);

	for (int i = 0; i < list_max; i++)
	{
		if (m_pStaticMesh[MList[i].listNo]->Init(
			*pdx9, *pdx11, MList[i].path) == E_FAIL)
		{
			return E_FAIL;
		}
	}

	// スカイボックス
	m_pSkyMesh->Init(*pdx9, *pdx11, _T("Data\\Mesh\\Static\\Sky\\BlueSky.x"));


	return S_OK;
}

