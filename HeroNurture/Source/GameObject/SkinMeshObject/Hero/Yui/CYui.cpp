#include "CYui.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"

CYui::CYui()
	: m_BonePos()
	, m_Run()
	, m_AnimChange()
	, m_EffPosZ(1.0f)

{
	SetScale(0.1f, 0.1f, 0.1f);
}

CYui::~CYui()
{
}

//�������֐�
void CYui::Initialize()
{
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_AnimSpeed = 0.01f;
	//���߂̃A�j���[�V�����̐ݒ�
	m_AnimNo = 3;
	//�o��A�j���[�V����
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

}

//�f�[�^�ǂݍ��݊֐�
void CYui::LoadData( const json& jsondata )
{
	//���b�V���f�[�^�̓ǂݍ���
	AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
	
	//�e�p�����[�^�̑��
	m_Para.Power = jsondata["Paramater"]["Power"];
	m_Para.Magic = jsondata["Paramater"]["Magic"];
	m_Para.Speed = jsondata["Paramater"]["Speed"];
	m_Para.Hp    = jsondata["Paramater"]["Hp"];


}

//�X�V�֐�
void CYui::Update()
{
}

//�`��֐�
void CYui::Draw(LIGHT& Light)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw(Light);
}

//�A�j���[�V�����֐�
void CYui::Animation()
{
	if (m_AnimNo == 3)
	{

	}

	//�A�j���[�V�����̌o�ߎ��Ԃ����Z		
	m_AnimTime += m_pMesh->GetAnimSpeed();
}

void CYui::AnimChange()
{
	m_AnimChange = true;
}



