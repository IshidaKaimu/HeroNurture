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

	//�A�j���[�V�����̎����Ƃ̉�]�l�̏�����
	m_MoveRotateY = 0.0f; //Y��
	m_MoveRotateZ = 0.0f; //Z��

	//��]�X�s�[�h�̏�����
	m_RotateSpeedY = 1.0f;

	//�A�j���[�V�����I���t���O�̏�����
	m_AnimEnd = false;
	//�_���[�W�A�j���[�V�����I���t���O�̏�����
	m_DamageAnimEnd = false;
	//�_���[�W�t���O�̏�����
	m_Damage = false;
	//�A�j���[�V�����J�E���g�̏�����
	m_AnimCnt = 0;
	//�A�j���[�V�����؂�ւ��t���O�̏�����
	m_AnimChange = false;

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
	
	//�A�j���[�V�����̎����Ƃ̉�]�l�̏�����
	m_MoveRotateY = 0.0f; //Y��
	m_MoveRotateZ = 0.0f; //Z��

	//��]�X�s�[�h�̏�����
	m_RotateSpeedY = 1.0f;

	//�A�j���[�V�����I���t���O�̏�����
	m_AnimEnd = false;
	//�_���[�W�A�j���[�V�����I���t���O�̏�����
	m_DamageAnimEnd = false;
	//�_���[�W�t���O�̏�����
	m_Damage = false;
	//�A�j���[�V�����J�E���g�̏�����
	m_AnimCnt = 0;
	//�A�j���[�V�����؂�ւ��t���O�̏�����
	m_AnimChange = false;

	//�A�j���[�V�����̊J�n�n�_�̌Œ�
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;
}

void CYui::UniqueInit()
{
	//�A�j���[�V�����֘A�̏�����
	AnimInit();

	//�A�j���[�V�����̎����Ƃ̉�]�l�̏�����
	m_MoveRotateY = 0.0f; //Y��
	m_MoveRotateZ = 0.0f; //Z��

	//��]�X�s�[�h�̏�����
	m_RotateSpeedY = 1.0f;

	//�A�j���[�V�����I���t���O�̏�����
	m_AnimEnd = false;
	//�_���[�W�A�j���[�V�����I���t���O�̏�����
	m_DamageAnimEnd = false;
	//�_���[�W�t���O�̏�����
	m_Damage = false;
	//�A�j���[�V�����J�E���g�̏�����
	m_AnimCnt = 0;
	//�A�j���[�V�����؂�ւ��t���O�̏�����
	m_AnimChange = false;

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
#if DEBUG
	ImGui::Begin(JAPANESE("Yui"));
	ImGui::InputFloat3(JAPANESE("�ʒu"),DebugPos);
	ImGui::InputFloat3(JAPANESE("�g�k"), DebugScale);
	ImGui::End();
	SetPosition(DebugPos);
	SetScale(DebugScale);
#endif

#if _DEBUG
	ImGui::Begin(JAPANESE("Yui"));
	ImGui::Text(JAPANESE("�ʒux:%f"), m_vPosition.x);
	ImGui::Text(JAPANESE("�ʒuy:%f"), m_vPosition.y);
	ImGui::Text(JAPANESE("�ʒuz:%f"), m_vPosition.z);
	ImGui::End();
#endif

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
	//�A�j���[�V�����I����ɖ߂������ʒu
	D3DXVECTOR3 InitPos;
	
	//�G�����������Ŗ߂������ʒu�����߂�
	if (vector == 1.0f) { InitPos = BATTLEINIT_POS; }
	else { InitPos = ENEMYINIT_POS; }


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
		m_AnimEnd = true;
	}

	if (!m_AnimEnd) {
		SetPosition(m_MoveX, m_MoveY, m_MoveZ);
	}
	else
	{
		//�ʒu��߂�
		SetPosition(InitPos);
		//�ϓ����Ă����l��߂�
		m_MoveX = InitPos.x; //X���W
		m_MoveY = InitPos.y; //Y���W
		m_MoveZ = InitPos.z; //Z���W
		//��]�l��߂�
		SetRotation(BATTLE_ROTATE.x, BATTLE_ROTATE.y, BATTLE_ROTATE.z * vector);

		AnimChange(3);
	}
}

//�U��2
void CYui::MagicAttackAnim(float vector)
{
	//�A�j���[�V�����I����ɖ߂������ʒu
	D3DXVECTOR3 InitPos;

	//�G�����������Ŗ߂������ʒu�����߂�
	if (vector == 1.0f) { InitPos = BATTLEINIT_POS; }
	else { InitPos = ENEMYINIT_POS; }


	//�A�j���[�V�����I���܂ł̃J�E���g
	if (!m_AnimEnd)
	{
		m_AnimCnt++;
	}

	if (m_AnimNo == 3)
	{
		AnimChange(0);
	}

	if (m_AnimNo == 0)
	{
		//�A�j���[�V�����̌o�ߎ��Ԃ����Z		
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (m_MoveY <= 0.5f) {
			m_MoveY += 0.02f;
		}
		else
		{
		    //�A�j���[�V������~
		    m_AnimSpeed = 0.0f;
		}
	}

	if (!m_AnimEnd)
	{
		SetPosition(m_MoveX, m_MoveY, m_MoveZ);
	}

	//�J�E���g�����𒴂�����
	if (m_AnimCnt >= 240)
	{
		//�ʒu�̏C��
		SetPositionY(InitPos.y);
		//�ϓ�����Y���W�̏�����
		m_MoveY = InitPos.y;
		//�A�j���[�V�����I��
		m_AnimEnd = true;
		AnimChange(0);
		m_AnimCnt = 0;
	}

}

void CYui::UniqueAttackAnim()
{
	SetPosition(UNIQUE_POS_YUI);
	SetScale(BATTLE_SCALE_YUI);
	SetRotation(UNIQUE_ROTATE_YUI);
}

void CYui::DamageAnim(float vector)
{
	//�ǂ̃A�j���[�V�����̌�ł��Đ����x��ς��Ȃ�
	m_AnimSpeed = 0.01f;

	//���̃A�j���[�V�����Ŏg�p���Ă���A�j���[�V�����łȂ��ꍇ
	bool NotUseAnim = m_AnimNo != 0 && m_AnimNo != 1;

	//�ҋ@�A�j���[�V������
	if (NotUseAnim && !m_AnimChange) {
		AnimChange(0);
	}

	if (m_AnimNo == 0 && !m_AnimChange)
	{
		//�A�j���[�V�����̌o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		//�������Œ肷��
		m_MoveY = 0.0f;

		if (m_pMesh->GetAnimPeriod(m_AnimNo) - 0.4 < m_AnimTime)
		{
			AnimChange(1);
		}
		else
		{
			//�ʒu���������ɉ�����
		    m_MoveX += (0.08f * vector);
		}
	}

	if (m_AnimNo == 1)
	{
		//�A�j���[�V�����̌o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		bool Return = m_MoveX <= BATTLEINIT_POS.x;     //�������̏ꍇ
		bool EnemyReturn = m_MoveX >= ENEMYINIT_POS.x; //�G���̏ꍇ

		//�ŏ��̈ʒu�ɖ߂�
		if (Return || EnemyReturn)
		{
			m_MoveX -= (0.08f * vector);
		}
		else
		{
			//�����A�j���[�V�����ԍ��ł��ʂ̏������ł���悤��
			m_AnimChange = true;
			AnimChange(3);
		}
	}

	if (m_AnimNo == 3 && m_AnimChange)
	{
		//�߂��Ă��Ă���A�j���[�V�����I���܂ŏ����J����
		m_AnimCnt++;
		//�A�j���[�V�����̌o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
		if (m_AnimCnt >= 60) 
		{
			m_DamageAnimEnd = true;
			m_AnimChange = false;
			m_AnimCnt = 0;
		}
	}

	SetPosition(m_MoveX, m_MoveY, m_MoveZ);

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


