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

//�o�g���V�[���Ŏg�p���鏉����
void CYui::BattleInitialize()
{
	//�A�j���[�V�����֘A�̏�����
	AnimInit();

	//���W�̐ݒ�
	SetPosition(BATTLEINIT_POS_YUI);
	//�g�k�̐ݒ�
	SetScale(BATTLEINIT_SCALE_YUI);
	//��]�̐ݒ�
	SetRotation(BATTLEINIT_ROTATE_YUI);

}

//�G�ɂȂ����ۂ̏������֐�
void CYui::EnemyInit()
{
	//�A�j���[�V�����֘A�̏�����
	AnimInit();

	//���W�̐ݒ�
	SetPosition(ENEMYINIT_POS_YUI);
	//�g�k�̐ݒ�
	SetScale(BATTLEINIT_SCALE_YUI);
	//��]�̐ݒ�
	SetRotation(ENEMYINIT_ROTATE_YUI);

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

//�o�g���Ɏg�p����f�[�^�̓ǂݍ���
void CYui::SetBattleParamData(const json& jsondata)
{
	//�o�g���Ɏg�p����f�[�^�̓ǂݍ���
	SetBattleParam(jsondata);
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

//�f�o�b�O�֐�
void CYui::Debug()
{
	ImGui::Begin(JAPANESE("Yui"));
	ImGui::InputFloat3(JAPANESE("�ʒu"),DebugPos);
	ImGui::InputFloat3(JAPANESE("�g�k"), DebugScale);
	ImGui::End();
	SetPosition(DebugPos);
	SetScale(DebugScale);
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
}
//�̗̓g���[�j���O�A�j���[�V����
void CYui::HpTraningAnimation()
{
}

//�A�j���[�V�����Ɋւ��鏉����
void CYui::AnimInit()
{
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_AnimSpeed = 0.01f;
	//���߂̃A�j���[�V�����̐ݒ�
	m_AnimNo = 3;
	//�o��A�j���[�V����
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
}

void CYui::AnimChange()
{
	m_AnimChange = true;
}



