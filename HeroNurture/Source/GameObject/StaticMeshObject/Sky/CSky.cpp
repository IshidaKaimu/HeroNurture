#include "CSky.h"
#include "StaticMesh\MeshManager\CMeshManager.h"

CSky::CSky()
{
	SetScale(100.0f, 100.0f, 100.0f);
	SetPosition(0.0f, 0.0f, 0.0f);
}

CSky::~CSky()
{
}

//メッシュデータ設定関数
void CSky::LoadData()
{
	AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
}

//更新関数
void CSky::Update()
{
	CStaticMeshObject::Update();
}

//描画
void CSky::Draw()
{
	CStaticMeshObject::Draw();
}

