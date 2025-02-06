#pragma once
#include "SkinMesh\CSkinMesh.h"
#include "Sprite3D\CSprite3D.h"
#include "StaticMeshObject\Character\CCharacter.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "Singleton\CSingleton.h"

class CSkinMeshManager
	:public CSingleton<CSkinMeshManager> 
{
private:
	friend class CSingleton<CSkinMeshManager>;
	~CSkinMeshManager();

public:
	//メッシュリスト		
	enum SkinMeshList
	{
		Yui,
		Kaito,
		Boss,
		FastBoss,
		Ground,

		Max,
	};

	HRESULT Load(CDirectX9* pdx9, CDirectX11* pdx11);

	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }
	void SetDx9(CDirectX9& Dx9) { m_pDx9 = &Dx9; }

	static CSkinMesh& GetMesh(SkinMeshList list) { return *CSkinMeshManager::GetInstance().m_pSkinMesh[list]; }

private:
	//他からアクセスされることがないように
	CSkinMeshManager();

private:
	//Dx11
	CDirectX11* m_pDx11;
	//Dx9
	CDirectX9* m_pDx9;

private:

	CSkinMesh* m_pSkinMesh[SkinMeshList::Max];
};

