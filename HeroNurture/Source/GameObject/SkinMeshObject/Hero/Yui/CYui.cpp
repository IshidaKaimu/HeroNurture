#include "CYui.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"

CYui::CYui()
	: m_AnimChange()

{
	SetScale(0.1f, 0.1f, 0.1f);
}

CYui::~CYui()
{
}

//�������֐�
void CYui::Initialize()
{
	//�N���X�C���X�^���X��ϐ��ɑ��
    //�V�[���}�l�[�W���[
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_AnimSpeed = 0.01f;
	//���߂̃A�j���[�V�����̐ݒ�
	m_AnimNo = 3;
	//�o��A�j���[�V����
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

	//���t�F�[�h�̏�����
	SceneMng->InitWhiteFade();
}

//���b�V���f�[�^�ǂݍ��݊֐�
void CYui::LoadMeshData()
{
	//���b�V���f�[�^�̓ǂݍ���
	AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
}

//�p�����[�^���̓ǂݍ���
void CYui::LoadParamData(const json& jsondata)
{
	if (!CSceneManager::GetInstance()->GetIsDataLoaded()) 
	{
		//�p�����[�^�̓ǂݍ���
		LoadParam(jsondata, "Yui");
	}
	else
	{
		//�p�����[�^�̍X�V
		UpdateParam(jsondata, "Yui");
	}
}

//�X�V�֐�
void CYui::Update()
{
}

//�`��֐�
void CYui::Draw()
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw();
}

//�琬�q�[���[�I���V�[���̃A�j���[�V����
void CYui::NatureHeroSelectAnimation()
{
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_AnimSpeed = 0.01f;
}

//�o�g���q�[���[�I���V�[���̃A�j���[�V����
void CYui::BattleHeroSelectAnimation()
{
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_AnimSpeed = 0.01f;
}

//�琬�V�[���̃A�j���[�V����
void CYui::NatureAnimation(int no)
{
	//�A�j���[�V�����̌o�ߎ��Ԃ����Z		
	m_AnimTime += m_pMesh->GetAnimSpeed();
}

//�ؗ̓g���[�j���O�A�j���[�V����
void CYui::PowerTraningAnimation()
{
}
//���̓g���[�j���O�A�j���[�V����
void CYui::MagicTraningAnimation()
{
}
//�f�����g���[�j���O�A�j���[�V����
void CYui::SpeedTraningAnimation()
{
	//�N���X�C���X�^���X��ϐ��ɑ��
	//�V�[���}�l�[�W���[
	CSceneManager* SceneMng = CSceneManager::GetInstance();
	//�q�[���[�}�l�[�W���[
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	m_EventCnt++;

	if (m_EventCnt <= 1)
	{
		HeroMng->SetPosition(-10.0f, 0.0f, 0.0f);
	}

	SceneMng->PlayWhiteFade(1, 0.01f, 0.8f);
}
//�̗̓g���[�j���O�A�j���[�V����
void CYui::HpTraningAnimation()
{
}

void CYui::AnimChange()
{
	m_AnimChange = true;
}



