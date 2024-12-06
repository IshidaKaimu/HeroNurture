#include "CKaito.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"

CKaito::CKaito()
	: m_BonePos		()
	, m_Run			()
	, m_AnimChange	()
	, m_EffPosZ		(1.0f)

{
	SetScale(0.75f, 0.75f, 0.75f);
	SetPosition(0.0f, 0.0f, 1.2f);
}

CKaito::~CKaito()
{
}

//�������֐�
void CKaito::Initialize()
{
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_AnimSpeed = 0.01f;
	//�ҋ@�A�j���[�V����
	m_AnimNo = 0;	
	//�A�j���[�V������ݒ�
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
}

//���b�V���f�[�^�ǂݍ��݊֐�
void CKaito::LoadMeshData()
{
	//���b�V���f�[�^�̓ǂݍ���
	AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));
}
//�p�����[�^���̓ǂݍ���
void CKaito::LoadParamData(const json& jsondata)
{
	if (!CSceneManager::GetInstance()->GetIsDataLoaded())
	{
		//�p�����[�^�̓ǂݍ���
		LoadParam(jsondata, "Kaito");
	}
	else
	{
		//�p�����[�^�̍X�V
		UpdateParam(jsondata, "Kaito");
	}
}

//�X�V�֐�
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

//�`��֐�
void CKaito::Draw()
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw();
}

//�q�[���[�I���V�[���̃A�j���[�V����
void CKaito::SelectAnimation()
{
}

//�琬�V�[���̃A�j���[�V����
void CKaito::NatureAnimation(int no)
{
	//�A�j���[�V�����̌o�ߎ��Ԃ����Z
	m_AnimTime += m_pMesh->GetAnimSpeed();
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



