#include "CSky.h"
#include "StaticMesh\MeshManager\CMeshManager.h"

CSky::CSky()
{
	SetScale(1.7f, 1.7f, 1.7f);
	SetPosition(0.0f, -30.0f, 0.0f);
	SetRotation(D3DXToRadian(0), D3DXToRadian(90), 0.0f);
}

CSky::~CSky()
{
}

//メッシュデータ設定関数
void CSky::LoadData()
{
	AttachMesh(CMeshManager::GetSkyMesh());
}

//更新関数
void CSky::Update()
{

}

//描画
void CSky::Draw()
{
	if (m_pSkyMesh == nullptr) {
		return;
	}

	m_vRotation.y += 0.005f;

	//描画直前で座標や回転情報などを更新.
	m_pSkyMesh->SetPosition(m_vPosition);
	m_pSkyMesh->SetRotation(m_vRotation);
	m_pSkyMesh->SetScale(m_vScale);

	//レンダリング.
	m_pSkyMesh->Render();
}

