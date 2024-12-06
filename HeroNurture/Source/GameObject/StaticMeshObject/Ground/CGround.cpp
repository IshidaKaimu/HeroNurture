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

//���b�V���f�[�^�ݒ�
void CGround::LoadData()
{
	AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

//�X�V�֐�
void CGround::Update()
{
	CStaticMeshObject::Update();
}

//�`��֐�
void CGround::Draw()
{
	CStaticMeshObject::Draw();
}
