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

//���b�V���f�[�^�ݒ�֐�
void CSky::LoadData()
{
	AttachMesh(CMeshManager::GetSkyMesh());
}

//�X�V�֐�
void CSky::Update()
{

}

//�`��
void CSky::Draw()
{
	if (m_pSkyMesh == nullptr) {
		return;
	}

	m_vRotation.y += 0.005f;

	//�`�撼�O�ō��W���]���Ȃǂ��X�V.
	m_pSkyMesh->SetPosition(m_vPosition);
	m_pSkyMesh->SetRotation(m_vRotation);
	m_pSkyMesh->SetScale(m_vScale);

	//�����_�����O.
	m_pSkyMesh->Render();
}

