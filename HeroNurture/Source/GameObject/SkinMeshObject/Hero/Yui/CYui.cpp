#include "CYui.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "ModeManager\Nurture\CNurtureManager.h"

//�萔�̖��O���
using namespace Constant_Yui;

CYui::CYui()
	: m_AnimChange  ()
	, m_MoveRotateY (0.0f)
	, m_RotateSpeedY(1.0f)
	, m_DamageSECnt ()
{
	SetScale(0.1f, 0.1f, 0.1f);
}

CYui::~CYui()
{
}

//�������֐�
void CYui::Initialize()
{
	CSceneManager* SceneMng = &CSceneManager::GetInstance();

	//�A�j���[�V�����̏�����
	AnimInit();

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
	SetScale(BATTLE_SCALE);
	//��]�̐ݒ�
	SetRotation(BATTLE_ROTATE);

	//�A�j���[�V�����̎����Ƃ̉�]�l�̏�����
	m_MoveRotateY = 0.0f; //Y��
	m_MoveRotateZ = 0.0f; //Z��

	//��]�X�s�[�h�̏�����
	m_RotateSpeedY = 1.0f;

	//�A�j���[�V�����I���t���O�̏�����
	m_AttackAnimEnd = false;
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
void CYui::EnemyInitialize()
{
	//�A�j���[�V�����֘A�̏�����
	AnimInit();

	//���W�̐ݒ�
	SetPosition(ENEMYINIT_POS);
	//�g�k�̐ݒ�
	SetScale(BATTLE_SCALE);
	//��]�̐ݒ�
	SetRotation(ENEMY_ROTATE);
	
	//�A�j���[�V�����̎����Ƃ̉�]�l�̏�����
	m_MoveRotateY = 0.0f; //Y��
	m_MoveRotateZ = 0.0f; //Z��

	//��]�X�s�[�h�̏�����
	m_RotateSpeedY = 1.0f;

	//�A�j���[�V�����I���t���O�̏�����
	m_AttackAnimEnd = false;
	//�_���[�W�A�j���[�V�����I���t���O�̏�����
	m_DamageAnimEnd = false;
	//�_���[�W�t���O�̏�����
	m_Damage = false;
	//�A�j���[�V�����J�E���g�̏�����
	m_AnimCnt = 0;
	//�G�t�F�N�g�J�E���g�̏�����
	m_EffCnt = 0;
	//�A�j���[�V�����؂�ւ��t���O�̏�����
	m_AnimChange = false;

	//�A�j���[�V�����̊J�n�n�_�̌Œ�
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;
}

//�o�g���J�n���o��V�[���ł̏�����
void CYui::AppearanceInitialize()
{
	//���W�̐ݒ�
	SetPosition(APPEALANCE_POS);
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
	if (!CNurtureManager::GetInstance().GetIsDataLoaded()) 
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
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	//�`��
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

#if DEBUG
	ImGui::Begin(JAPANESE("Yui"));
	ImGui::Text(JAPANESE("�ʒux:%f"), m_vPosition.x);
	ImGui::Text(JAPANESE("�ʒuy:%f"), m_vPosition.y);
	ImGui::Text(JAPANESE("�ʒuz:%f"), m_vPosition.z);
	ImGui::End();
#endif

}

//�o��V�[���̃A�j���[�V����
void CYui::AppearanceAnimation()
{
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_AnimSpeed = 0.01f;
	
	//�A�j���[�V�����̌o�ߎ��Ԃ����Z		
	m_AnimTime += m_pMesh->GetAnimSpeed();

	//�A�j���[�V�����ԍ��̐ݒ�	
	if (m_vPosition.z >= APPEALANCE_GOAL_Z) {
		//�����A�j���[�V������
		if (m_AnimNo != Walk)
		{
			AnimChange(Walk);
		}
		//�J�����Ɍ����đO�i
		m_vPosition.z -= APPEALANCE_SPEED;
	}
	else
	{
		if (m_AnimNo == Walk)
		{
			AnimChange(Wait);
		}
		m_AppealanceAnimEnd = true;
	}
}

//�琬�V�[���̃A�j���[�V����
void CYui::NurtureAnimation(int no)
{
	//�A�j���[�V�����̌o�ߎ��Ԃ����Z		
	m_AnimTime += m_pMesh->GetAnimSpeed();
}

void CYui::MoveSelectAnim()
{
	if (m_AnimNo == Wait)
	{
		m_AnimTime += m_pMesh->GetAnimSpeed();
	}
}

//�U��1���̃A�j���[�V����
void CYui::PowerAttackAnim(float vector)
{
	//�A�j���[�V�����I����ɖ߂������ʒu
	D3DXVECTOR3 InitPos;
	
	//�G�t�F�N�g�n���h���̗p��
	static ::EsHandle hTornado = 2;	//�����G�t�F�N�g

	//�G�����������Ŗ߂������ʒu�����߂�
	if (vector == 1.0f)
	{
		InitPos = BATTLEINIT_POS; 
	}
	else 
	{ 
		InitPos = ENEMYINIT_POS; 
	}

	if (!m_AttackAnimEnd) 
	{
		m_AnimCnt++;

		//�����G�t�F�N�g
		CEffect* Eff = CEffect::GetInstance();
		Eff->Speed(hTornado, 1.0f);
		Eff->Scale(hTornado, TORNADE_SCALE);

		if (m_AnimCnt >= CHANGE_TSHARP) {
			AnimChange(TSharp);
		}

		if (m_AnimNo == TSharp)
		{
			m_EffCnt++;

			if (m_EffCnt == PLAY_TSHARP_SE)
			{
				//T��SE�̍Đ�
				CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_TPose);
				CSoundManager::GetInstance()->Volume(CSoundManager::SE_TPose, 80);
			}

			if (m_EffCnt  == TORNADE_PLAY) 
			{
				//����SE�̍Đ�
				CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Tornade);
				CSoundManager::GetInstance()->Volume(CSoundManager::SE_Tornade, 80);

				hTornado = CEffect::Play(CEffect::Yui_Power, D3DXVECTOR3(m_vPosition.x, m_vPosition.y, m_vPosition.z));
			}

			if (m_AnimCnt >= MOVECHANGE_FASTTIME)
			{
				if (m_AnimCnt % ROTATE_ADDSPEED_INTERVAL == 0)
				{
					if (m_RotateSpeedY <= ROTATE_ADDSPEED_MAX) 
					{
						m_RotateSpeedY += ROTATE_ADDSPEED;
					}
				}
				m_MoveRotateY += m_RotateSpeedY;

				if (m_AnimCnt <= MOVECHANGE_SECONDTIME) {
					m_MoveX -= MOVESPEED_BACK * vector;
					if (m_MoveRotateZ <= TILT_BACK_MAX) {
						m_MoveRotateZ += TILT_BACK_SPEED;
					}
				}
				if (m_AnimCnt >= MOVECHANGE_THIRDTIME)
				{
					if (m_MoveRotateZ >= -TILT_FORWARD_MAX)
					{
						m_MoveRotateZ -= TILT_FORWARD_SPEED;
					}
				}
				if (m_AnimCnt >= MOVECHANGE_FOURTHTIME)
				{
					m_MoveX += (MOVESPEED_RUSH * vector);
				}

				SetRotation(BATTLE_ROTATE.x, m_MoveRotateY, m_MoveRotateZ * vector);
			}
		}

		if (m_AnimCnt >= FASTATTACK_ANIM_END)
		{
			m_AnimCnt = 0;
			m_EffCnt = 0;
			m_AttackAnimEnd = true;
		}
	}

	if (!m_AttackAnimEnd) {
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
		
		if (m_AnimNo == TSharp)
		{
			AnimChange(Wait);
		}
	}

}

//�U��2
void CYui::MagicAttackAnim(float vector)
{
	//�G�t�F�N�g�n���h���̗p��
	static ::EsHandle hAttackTornade = -1;	//�΋��G�t�F�N�g
	//�G�t�F�N�g�̎���]
	float EffRoteZ;
	if (vector == 1) { EffRoteZ = -ATTACKTORNADE_ROTATE_Y; }
	else { EffRoteZ = ATTACKTORNADE_ROTATE_Y; }

	//�A�j���[�V�����I����ɖ߂������ʒu
	D3DXVECTOR3 InitPos;

	//�G�����������Ŗ߂������ʒu�����߂�
	if (vector == 1.0f) { InitPos = BATTLEINIT_POS; }
	else { InitPos = ENEMYINIT_POS; }

	//�A�j���[�V�����I���܂ł̃J�E���g
	if (!m_AttackAnimEnd)
	{
		m_AnimCnt++;

		//�W�����v�ȊO�̃A�j���[�V�����ԍ����ݒ肳��Ă���ꍇ�W�����v��
		if (m_AnimNo == Wait)
		{
			AnimChange(Jump);
		}

		if (m_AnimNo == Jump)
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

				m_EffCnt++;

				CEffect* Eff = CEffect::GetInstance();
				Eff->Speed(hAttackTornade, 2.0f);
				Eff->Scale(hAttackTornade, ATTACKTORNADE_SCALE);
				Eff->Rotate(hAttackTornade, D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(EffRoteZ)));

				if (m_EffCnt == 1)
				{
					//�U���p����SE�̍Đ�
					CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_AttackTornade);
					CSoundManager::GetInstance()->Volume(CSoundManager::SE_AttackTornade, 300);

					hAttackTornade = CEffect::Play(CEffect::Yui_Magic, D3DXVECTOR3(m_vPosition.x - (5.0f * vector), m_vPosition.y + 0.4f, m_vPosition.z));
				}
			}
		}

		if (!m_AttackAnimEnd)
		{
			SetPosition(m_MoveX, m_MoveY, m_MoveZ);
		}

		//�J�E���g�����𒴂�����
		if (m_AnimCnt >= SECONDATTACK_ANIM_END)
		{
			//�ʒu�̏C��
			SetPositionY(InitPos.y);
			//�ϓ�����Y���W�̏�����
			m_MoveY = InitPos.y;
			//�A�j���[�V�����I��
			m_AttackAnimEnd = true;
			//�A�j���[�V�����J�E���g�̏�����
			m_AnimCnt = 0;
			//�G�t�F�N�g�J�E���g�̏�����
			m_EffCnt = 0;
		}
	}

	//�A�j���[�V�������I�������ۃA�j���[�V�����ɖ߂�
	if (m_AttackAnimEnd)
	{
		AnimChange(Wait);
	}

}

void CYui::DamageAnim(float vector)
{

	//�ǂ̃A�j���[�V�����̌�ł��Đ����x��ς��Ȃ�
	m_AnimSpeed = 0.01f;

	D3DXVECTOR3 InitRotate;

	if (vector != 1.0f) { InitRotate = BATTLE_ROTATE; }
	else { InitRotate = ENEMY_ROTATE; }

	//��]�����킹��
	SetRotation(InitRotate);

	//���̃A�j���[�V�����Ŏg�p���Ă���A�j���[�V�����łȂ��ꍇ
	bool NotUseAnim = m_AnimNo != 0 && m_AnimNo != 1;

	m_DamageSECnt++;

	if (m_DamageSECnt == 1)
	{
		//�_���[�WSE�̍Đ�
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Damage);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Damage, 80);
	}
	//�ҋ@�A�j���[�V������
	if (NotUseAnim && !m_AnimChange) {

		AnimChange(Jump);
	}

	if (m_AnimNo == Jump && !m_AnimChange)
	{
		//�A�j���[�V�����̌o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		//�������Œ肷��
		m_MoveY = 0.0f;

		if (m_pMesh->GetAnimPeriod(m_AnimNo) - 0.4 < m_AnimTime)
		{
			AnimChange(Run);
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

		bool Return      = m_MoveX <= BATTLEINIT_POS.x; //�������̏ꍇ
		bool EnemyReturn = m_MoveX >= ENEMYINIT_POS.x;	//�G���̏ꍇ

		//�ŏ��̈ʒu�ɖ߂�
		if (Return || EnemyReturn)
		{
			m_MoveX -= (0.08f * vector);
		}
		else
		{
			//�����A�j���[�V�����ԍ��ł��ʂ̏������ł���悤��
			m_AnimChange = true;
			AnimChange(Wait);
		}
	}

	if (m_AnimNo == Wait && m_AnimChange)
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
			m_DamageSECnt = 0;
		}
	}

	SetPosition(m_MoveX, m_MoveY, m_MoveZ);

}

//�A�j���[�V�����Ɋւ��鏉����
void CYui::AnimInit()
{
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_AnimSpeed = 0.01f;
	//���߂̃A�j���[�V�����̐ݒ�
	m_AnimNo = Wait;
	//�o��A�j���[�V����
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
}

//�A�j���[�V�����؂�ւ��֐�
void CYui::AnimChange(int animno)
{
	CHeroBase::AnimChange(animno);
}


