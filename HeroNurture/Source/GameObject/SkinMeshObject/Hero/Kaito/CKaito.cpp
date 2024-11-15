#include "CKaito.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"

CKaito::CKaito()
	: m_BonePos		()
	, m_Run			()
	, m_AnimChange	()
	, m_EffPosZ		(1.0f)
{
}

CKaito::~CKaito()
{
}

void CKaito::Initialize()
{
}

void CKaito::LoadData()
{
	//���b�V���f�[�^�̓ǂݍ���
	AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));
}

void CKaito::Update()
{

	//--------------------------
	//�X�L�����b�V��
	//--------------------------
	
	//Kaito
	//�A�j���[�V�����ԍ�����
	//0:�ҋ@
	//1:����
	//2:�a��(�E�ォ��E��)
	//3:�a��(��������E���)
	//4:�a�艺�낷
	//5:���
	//6:����o��
	//7:�_���[�W
	//8:���S

}

void CKaito::Draw( LIGHT& Light )
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw( Light );
}

void CKaito::Animation()
{
    m_AnimNo = 2;	//�o��A�j���[�V������
    //�o��A�j���[�V����
    m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
}

bool CKaito::SceneChange()
{
	if (m_EffPosZ >= 10.0f)
	{
		return true;
	}
	return false;
}

void CKaito::AnimChange()
{
	m_AnimChange = true;
}



