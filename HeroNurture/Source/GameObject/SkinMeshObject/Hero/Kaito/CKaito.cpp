#include "CKaito.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"

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
	//�A�j���[�V�����֘A�̏�����
	AnimInit();
}

//�o�g���V�[���Ŏg�p���鏉����
void CKaito::BattleInitialize()
{
	//�A�j���[�V�����֘A�̏�����
	AnimInit();

	SetPosition(BATTLEINIT_POS);
	SetScale(BATTLE_SCALE_KAITO);
	SetRotation(BATTLE_ROTATE);
}

//�G�ɂȂ����ۂ̏������֐�
void CKaito::EnemyInit()
{
	//�A�j���[�V�����֘A�̏�����
	AnimInit();

	SetPosition(ENEMYINIT_POS);
	SetScale(BATTLE_SCALE_KAITO);
	SetRotation(ENEMY_ROTATE);
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

//�o�g���Ɏg�p����f�[�^�̓ǂݍ���
void CKaito::SetBattleParamData(const json& jsondata)
{
	//�o�g���Ɏg�p����f�[�^�̓ǂݍ���
	SetBattleParam(jsondata);
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

//�f�o�b�O�֐�
void CKaito::Debug()
{
	ImGui::Begin(JAPANESE("Kaito"));
	ImGui::InputFloat3(JAPANESE("�ʒu"), DebugPos);
	ImGui::InputFloat3(JAPANESE("�g�k"), DebugScale);
	ImGui::End();
	SetPosition(DebugPos);
	SetScale(DebugScale);
}

//�琬�q�[���[�I���V�[���̃A�j���[�V����
void CKaito::NatureHeroSelectAnimation()
{
}

//�o�g���q�[���[�I���V�[���̃A�j���[�V����
void CKaito::BattleHeroSelectAnimation()
{
}

//�琬�V�[���̃A�j���[�V����
void CKaito::NatureAnimation(int no)
{
	//�A�j���[�V�����̌o�ߎ��Ԃ����Z
	m_AnimTime += m_pMesh->GetAnimSpeed();
}

//�s���I�𒆂̃A�j���[�V����
void CKaito::MoveSelectAnim()
{
	
	if (m_AnimNo == 0) {
		//�A�j���[�V�����̌o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
		m_AnimCnt++;
	}

	if (m_AnimCnt >= 180)
	{
		//�a�艺�낵�A�j���[�V����
		m_AnimNo = 2;
		//�A�j���[�V�����̌o�ߎ��Ԃ����Z�b�g
		m_AnimTime = 0;
		//�A�j���[�V������ݒ�
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		//�J�E���g�����Z�b�g
		m_AnimCnt = 0;
	}

	if (m_AnimNo == 2)
	{
		//�A�j���[�V�����̌o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			//�ҋ@�A�j���[�V����
			m_AnimNo = 0;
			//�A�j���[�V�����̌o�ߎ��Ԃ����Z�b�g
			m_AnimTime = 0;
			//�A�j���[�V������ݒ�
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}
	}
}

void CKaito::PowerAttackAnim()
{
}

void CKaito::MagicAttackAnim()
{
}

void CKaito::UniqueAttackAnim()
{
}

float CKaito::PowerAttack()
{
	return CHeroBase::PowerAttack();
}

float CKaito::MagicAttack()
{
	return CHeroBase::MagicAttack();
}

float CKaito::UniqueAttack()
{
	float Damage = m_BattleParam.Power * CUtility::GetInstance().GenerateRandomValue(2.0f, 2.5f);
	m_UniqueGage -= 5;
	return Damage;
}

//�A�j���[�V�����֘A�̏�����
void CKaito::AnimInit()
{
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_AnimSpeed = 0.01f;
	//�ҋ@�A�j���[�V����
	m_AnimNo = 0;
	//�A�j���[�V������ݒ�
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
}


