#pragma once
#include "StaticMeshObject\CStaticMeshObject.h"
#include "StaticMeshObject\Character\CCharacter.h"
#include "StaticMeshObject\Sky\SkyMesh\CSkyMesh.h"

//=====================================
// 空クラス
// 制作者:石田櫂夢
//=====================================
class CSky
	: public CGameObject
{
public:
	CSky();
	virtual ~CSky();

	//メッシュデータ設定
	void LoadData();
	//更新関数
	virtual void Update() override;
	//描画関数
	virtual void Draw() override;

private:
	
	//メッシュを接続する.
	void AttachMesh(CSkyMesh& pskymesh) {
		m_pSkyMesh = &pskymesh;
	}
	//メッシュを切り離す.
	void DetachMesh() {
		m_pSkyMesh = nullptr;
	}

protected:
	CSkyMesh* m_pSkyMesh;

};

