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

//���b�V���f�[�^�ݒ�֐�
void CSky::LoadData()
{
	AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
}

//�X�V�֐�
void CSky::Update()
{
	CStaticMeshObject::Update();
}

//�`��
void CSky::Draw()
{
	CStaticMeshObject::Draw();
}

