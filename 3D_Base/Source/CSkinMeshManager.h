#pragma once
#pragma once
#include "CSkinMesh.h"
#include "CSprite3D.h"
#include "CCharacter.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CGround.h"
#include "CShot.h"

class CSkinMeshManager
{
public:
	//���b�V�����X�g		
	enum SkinMeshList
	{
		Player,
		Wooo,
		Boss,
		FastBoss,
		Ground,

		Max,
	};

	//�V���O���g����
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

	//�V���O���g����
	CSkinMeshManager();
	CSkinMeshManager(const CSkinMeshManager& rhs) = delete;
	CSkinMeshManager& operator = (const CSkinMeshManager& rhs) = delete;

private:

	CDirectX11* m_pDx11;
	CDirectX9* m_pDx9;

private:

	CSkinMesh* m_pSkinMesh[SkinMeshList::Max];
};

