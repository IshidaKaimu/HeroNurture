#pragma once
#pragma once
#include "SkinMesh/CSkinMesh.h"
#include "Sprite3D/CSprite3D.h"
#include "StaticMeshObject/Character/CCharacter.h"
#include "SkinMeshObject/Hero/CHero.h"
#include "StaticMeshObject/Ground/CGround.h"

class CSkinMeshManager
{
public:
	//メッシュリスト		
	enum SkinMeshList
	{
		Yui,
		Wooo,
		Boss,
		FastBoss,
		Ground,

		Max,
	};

	//シングルトン化
	static CSkinMeshManager* GetInstance() {
		static CSkinMeshManager s_Instance;
		return &s_Instance;
	}

	~CSkinMeshManager();

	HRESULT Load(CDirectX9* pdx9, CDirectX11* pdx11);

	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }
	void SetDx9(CDirectX9& Dx9) { m_pDx9 = &Dx9; }

	static CSkinMesh& GetMesh(SkinMeshList list) { return *CSkinMeshManager::GetInstance()->m_pSkinMesh[list]; }

private:

	//シングルトン化
	CSkinMeshManager();
	CSkinMeshManager(const CSkinMeshManager& rhs) = delete;
	CSkinMeshManager& operator = (const CSkinMeshManager& rhs) = delete;

private:

	CDirectX11* m_pDx11;
	CDirectX9* m_pDx9;

private:

	CSkinMesh* m_pSkinMesh[SkinMeshList::Max];
};

