#pragma once
#include "StaticMesh/CStaticMesh.h"
#include "Sprite3D/CSprite3D.h"
#include "StaticMeshObject/Character/CCharacter.h"
#include "SkinMeshObject/Hero/CHeroBase.h"
#include "StaticMeshObject/Ground/CGround.h"

class CMeshManager
{
public:
	//メッシュリスト		
	enum MeshList
	{
		Player,
		Boss,
		Ground,
		Sky,
		Black,

		Max,
	};

	//シングルトン化
	static CMeshManager* GetInstance() {
		static CMeshManager s_Instance;
		return &s_Instance;
	}

	~CMeshManager();

	HRESULT Load(CDirectX9* pdx9, CDirectX11* pdx11);

	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }
	void SetDx9(CDirectX9& Dx9) { m_pDx9 = &Dx9; }

	static CStaticMesh& GetMesh(MeshList list) { return *CMeshManager::GetInstance()->m_pStaticMesh[list]; }

	//CStaticMeshのGetMeshを呼び出す
	LPD3DXMESH Mesh(MeshList list) {
		return CMeshManager::GetInstance()->m_pStaticMesh[list]->GetMesh();
	}

private:

	//シングルトン化
	CMeshManager();
	CMeshManager(const CMeshManager& rhs) = delete;
	CMeshManager& operator = (const CMeshManager& rhs) = delete;

private:

	CDirectX11* m_pDx11;
	CDirectX9* m_pDx9;

private:

	CStaticMesh* m_pStaticMesh[MeshList::Max];
};

