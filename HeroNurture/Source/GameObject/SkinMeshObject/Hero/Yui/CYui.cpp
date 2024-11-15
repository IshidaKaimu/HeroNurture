#include "CYui.h"
#include "Effect/CEffect.h"
#include "Sound/CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"

CYui::CYui()
	: m_BonePos()
	, m_Run()
	, m_AnimChange()
	, m_EffPosZ(1.0f)
{
}

CYui::~CYui()
{
}

//�������֐�
void CYui::Initialize()
{
}

//�f�[�^�ǂݍ��݊֐�
void CYui::LoadData()
{
	//���b�V���f�[�^�̓ǂݍ���
	AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
}

//�X�V�֐�
void CYui::Update()
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
void CYui::Draw(LIGHT& Light)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw(Light);
}

//�A�j���[�V�����֐�
void CYui::Animation()
{
	if (GetAsyncKeyState('N') & 0x8000)
	{
		m_AnimNo = 2;	//�o��A�j���[�V������
		m_AnimTime = 0; //�A�j���[�V�����o�ߎ��ԏ�����
		//�o��A�j���[�V����
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
	}

}

void CYui::AnimChange()
{
	m_AnimChange = true;
}



