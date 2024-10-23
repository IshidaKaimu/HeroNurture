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
	for (int i = 0; i < MeshList::Max; i++) {
		m_pStaticMesh[i] = new CStaticMesh();
	}
	struct StaticMeshList
	{
		int listNo;
		LPCTSTR path;
	};


#if 0

	//プレイヤーの読み込み
	if (m_pStaticMesh[MeshList::Player]->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Fighter\\Fighter.x")) );
	//敵Aの読み込み
	if (m_pStaticMesh[MeshList::Enemy]->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Robo\\RobotA_pivot.x")) );
	//敵Bの読み込み
	if (m_pStaticMesh[MeshList::Enemies]->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Robo\\RobotB_pivot.x")) );
	//弾の読み込み
	if (m_pStaticMesh[MeshList::Bullet]->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Bullet\\bullet.x")) );
	//地面の読み込み
	if (m_pStaticMesh[MeshList::Ground]->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Ground\\ground.x")) );
	//ゴールの読み込み
	if (m_pStaticMesh[MeshList::Goal]->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Goal\\Goal.x")) );

	//キーパーの読み込み
	if (m_pStaticMesh[MeshList::Keeper]->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Keeper\\Keeper.x")) );

	//キッカーの読み込み
	if (m_pStaticMesh[MeshList::Kicker]->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Kicker\\Kicker.x")));

	//ボールの読み込み
	if (m_pStaticMesh[MeshList::Ball]->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Ball\\Ball.x")));


//バウンディングスフィアの読み込み
	if (m_pStaticMesh[MeshList::Sphere]->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Collision\\Sphere.x")));
#else 1
    StaticMeshList MList[] =
    {
        { MeshList::Player,                 _T( "Data\\Mesh\\Static\\Fighter\\Fighter.x" ) },
        { MeshList::Ground,                 _T("Data\\Mesh\\Static\\Ground\\Ground.x")     },
        { MeshList::Sky,                    _T("Data\\Mesh\\Static\\Sky\\Sky.x")     },
        { MeshList::Black,                  _T("Data\\Mesh\\Static\\Black\\Black.x")     },
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

#endif 

	return S_OK;
}

