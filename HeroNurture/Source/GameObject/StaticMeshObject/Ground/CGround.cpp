#include "CGround.h"
#include "StaticMesh\MeshManager\CMeshManager.h"

CGround::CGround()
	: m_pPlayer	( nullptr )
{
	SetScale(1.0f, 1.0f, 1.0);
	SetPosition(0.0f, 0.0f, 0.0f);
}

CGround::~CGround()
{
	m_pPlayer = nullptr;
}

//メッシュデータ設定
void CGround::LoadData()
{
	AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

//更新関数
void CGround::Update()
{
	CStaticMeshObject::Update();
}

//描画関数
void CGround::Draw()
{
	CStaticMeshObject::Draw();
}
