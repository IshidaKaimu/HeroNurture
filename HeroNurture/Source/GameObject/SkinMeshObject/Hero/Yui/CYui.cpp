#include "CYui.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"

CYui::CYui()
	: m_AnimChange()
	, m_MoveRotateY(0.0f)
	, m_RotateSpeedY(1.0f)
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
	SetPosition(BATTLEINIT_POS);
	//�g�k�̐ݒ�
	SetScale(BATTLE_SCALE_YUI);
	//��]�̐ݒ�
	SetRotation(BATTLE_ROTATE);

	//�A�j���[�V�����̊J�n�n�_�̌Œ�
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;
}

//�G�ɂȂ����ۂ̏������֐�
void CYui::EnemyInit()
{
	//�A�j���[�V�����֘A�̏�����
	AnimInit();

	//���W�̐ݒ�
	SetPosition(ENEMYINIT_POS);
	//�g�k�̐ݒ�
	SetScale(BATTLE_SCALE_YUI);
	//��]�̐ݒ�
	SetRotation(ENEMY_ROTATE);
	
	//�A�j���[�V�����̊J�n�n�_�̌Œ�
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;

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

void CYui::MoveSelectAnim()
{
	if (m_AnimNo == 3)
	{
		m_AnimTime += m_pMesh->GetAnimSpeed();
	}
}

//�U��1���̃A�j���[�V����
void CYui::PowerAttackAnim(float vector)
{
	if (!m_AnimEnd) {
		m_AnimCnt++;
	}

	if (m_AnimCnt >= 60) {
		AnimChange(4);
	}

	if(m_AnimNo == 4)
	{
		if (m_AnimCnt >= 80) 
		{
			if (m_AnimCnt % 30 == 0)
			{
				if (m_RotateSpeedY <= 8.0f) {
					m_RotateSpeedY += 0.05f;
				}
			}
			m_MoveRotateY += m_RotateSpeedY;

			if (m_AnimCnt <= 120) {
				m_MoveX -= 0.1f * vector;
				if (m_MoveRotateZ <= 0.5f) {
					m_MoveRotateZ += 0.005f;
				}
			}
			if (m_AnimCnt >= 150)
			{
				if (m_MoveRotateZ >= -0.35f)
				{
					m_MoveRotateZ -= 0.01f;
				}
			}
			if (m_AnimCnt >= 240)
			{
				m_MoveX += (0.2f * vector);
			}

			SetRotation(BATTLE_ROTATE.x, m_MoveRotateY, m_MoveRotateZ * vector);
		}
	}

	if (m_AnimCnt >= 300)
	{
		m_AnimCnt = 0;
		m_MoveRotateZ = 0;
		m_AnimEnd = true;
	}

	SetPosition(m_MoveX, m_MoveY, m_MoveZ);
}

void CYui::MagicAttackAnim(float vector)
{
}

void CYui::UniqueAttackAnim(float vector)
{
}

//�U��1
float CYui::PowerAttack()
{
	return CHeroBase::PowerAttack();
}

//�U��2
float CYui::MagicAttack()
{
	return CHeroBase::MagicAttack();
}

//�ŗL�U��
float CYui::UniqueAttack()
{
	float Damage = m_BattleParam.Magic * CUtility::GetInstance().GenerateRandomValue(2.0f, 2.5f);
	m_UniqueGage -= 5;
	return Damage;
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

//�A�j���[�V�����؂�ւ��֐�
void CYui::AnimChange(int animno)
{
	CHeroBase::AnimChange(animno);
}


