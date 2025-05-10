#include "CKaito.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"

//�萔�̖��O���
using namespace Constant_Kaito;

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
	SetScale(BATTLE_SCALE);
	SetRotation(BATTLE_ROTATE);

	//�A�j���[�V�����I���t���O�̏�����
	m_AttackAnimEnd = false;
	//�_���[�W�A�j���[�V�����I���t���O�̏�����
	m_DamageAnimEnd = false;
	//�_���[�W�t���O�̏�����
	m_Damage = false;
	//�A�j���[�V�����؂�ւ��t���O�̏�����
	m_AnimChange = false;
	//�A�j���[�V�����J�E���g�̏�����
	m_AnimCnt = 0;

	//�A�j���[�V�����̊J�n�n�_�̌Œ�
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;

}

//�G�ɂȂ����ۂ̏������֐�
void CKaito::EnemyInitialize()
{
	//�A�j���[�V�����֘A�̏�����
	AnimInit();

	SetPosition(ENEMYINIT_POS);
	SetScale(BATTLE_SCALE);
	SetRotation(ENEMY_ROTATE);

	//�A�j���[�V�����I���t���O�̏�����
	m_AttackAnimEnd = false;
	//�_���[�W�A�j���[�V�����I���t���O�̏�����
	m_DamageAnimEnd = false;
	//�_���[�W�t���O�̏�����
	m_Damage = false;
	//�A�j���[�V�����؂�ւ��t���O�̏�����
	m_AnimChange = false;
	//�A�j���[�V�����J�E���g�̏�����
	m_AnimCnt = 0;

	//�A�j���[�V�����̊J�n�n�_�̌Œ�
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;

}

void CKaito::AppearanceInitialize()
{
	//���W�̐ݒ�
	SetPosition(APPEALANCE_POS);

	//�A�j���[�V�����֘A�̏�����
	AnimInit();
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
#if _DEBUG
	ImGui::Begin(JAPANESE("Kaito"));
	ImGui::Text(JAPANESE("�ʒux:%f"), m_vPosition.x);
	ImGui::Text(JAPANESE("�ʒuy:%f"), m_vPosition.y);
	ImGui::Text(JAPANESE("�ʒuz:%f"), m_vPosition.z);
	ImGui::End();
#endif
}

//�琬�q�[���[�I���V�[���̃A�j���[�V����
void CKaito::NatureHeroSelectAnimation()
{
}

//�o�g���q�[���[�I���V�[���̃A�j���[�V����
void CKaito::BattleHeroSelectAnimation()
{
}

//�o�g���J�n���o��V�[���̃A�j���[�V����
void CKaito::AppearanceAnimation()
{
	//�A�j���[�V�����ԍ���0�ȊO�������ꍇ0��
	if (m_AnimNo != 0)
	{
		AnimChange(0);
	}

	if (m_vPosition.y <= AFTER_POS_Y)
	{
		m_vPosition.y += APPEALANCE_SPEED;
	}

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
		if (m_AnimCnt >= 180)
		{
			AnimChange(3);
			m_AnimCnt = 0;
		}
	}

	if (m_AnimNo == 3)
	{
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			AnimChange(0);
		}
	}
}

//�U��1
float CKaito::PowerAttack()
{
	return CHeroBase::PowerAttack();
}

//�U��2
float CKaito::MagicAttack()
{
	return CHeroBase::MagicAttack();
}

//�U��1�A�j���[�V����
void CKaito::PowerAttackAnim(float vector)
{
	//�G�t�F�N�g�n���h���̗p��
	static ::EsHandle hSlash = 0;	//�a���G�t�F�N�g


	//�ҋ@�A�j���[�V������
	if (!m_AttackAnimEnd) 
	{
		m_AnimCnt++;

		//�ҋ@���̎a��A�j���[�V�����������ꍇ
		if (m_AnimNo == 3)
		{
			AnimChange(0);
		}

		if (m_AnimNo == 0)
		{
			m_AnimTime += m_pMesh->GetAnimSpeed();

			if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
			{
				AnimChange(2);
				m_AnimCnt = 0;
			}
		}

		if (m_AnimNo == 2)
		{
			//�A�j���[�V�����I���܂ł̃J�E���g
			if (!m_AttackAnimEnd) { m_AnimCnt++; }

			m_EffCnt++;

			CEffect* Eff = CEffect::GetInstance();
			Eff->Speed(hSlash, 1.0f);
			Eff->Scale(hSlash, 0.6f, 0.6f, 0.6f);
			Eff->Rotate(hSlash, D3DXToRadian(-80.0f), 0.0f, 90.0f);

			if (m_EffCnt == 1) {
				//�a��SE�̍Đ�
				CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Slash);
				CSoundManager::GetInstance()->Volume(CSoundManager::SE_Slash, 80);
				hSlash = CEffect::Play(CEffect::Kaito_Power, D3DXVECTOR3(m_vPosition.x - (-1.0f * vector), m_vPosition.y + 1.5f, m_vPosition.z));
			}

			if (m_pMesh->GetAnimPeriod(m_AnimNo) - 0.8f < m_AnimTime)
			{
				m_AnimSpeed = 0.0f;
			}
			else
			{
				//�A�j���[�V�����̌o�ߎ��Ԃ����Z
				m_AnimTime += m_pMesh->GetAnimSpeed();
			}

			if (m_AnimCnt > 90)
			{
				m_AnimCnt = 0;
				m_EffCnt = 0;
				m_AttackAnimEnd = true;
			}
		}
	}
}

//�U��2�A�j���[�V����
void CKaito::MagicAttackAnim(float vector)
{
	//�G�t�F�N�g�n���h���̗p��
	static ::EsHandle hMagicLight = 1;	//�����@�G�t�F�N�g

	//�G�t�F�N�g�̎���]
	float EffRoteY;
	if (vector == 1.0f) { EffRoteY = 0.0f; }
	else { EffRoteY = -180.0f; }

	//�ǂ̃A�j���[�V�����̌�ł��Đ����x��ς��Ȃ�
	m_AnimSpeed = 0.01f;

	if (!m_AttackAnimEnd)
	{
		//�ҋ@���̎a��A�j���[�V�����������ꍇ
		if (m_AnimNo == 3)
		{
			AnimChange(0);
		}

		if (m_AnimNo == 0)
		{
			m_AnimTime += m_pMesh->GetAnimSpeed();

			if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
			{
				AnimChange(6);
				m_AnimCnt = 0;
			}
		}

		if (m_AnimNo == 6)
		{
			//�A�j���[�V�����I���܂ł̃J�E���g
			if (!m_AttackAnimEnd) { m_AnimCnt++; }

			m_AnimTime += m_pMesh->GetAnimSpeed();

			if (m_pMesh->GetAnimPeriod(m_AnimNo) - 0.6f < m_AnimTime)
			{
				m_EffCnt++;

				CEffect* Eff = CEffect::GetInstance();
				Eff->Speed(hMagicLight, 1.0f);
				Eff->Scale(hMagicLight, 0.2f, 0.2f, 0.2f);
				Eff->Rotate(hMagicLight, 0.0f, D3DXToRadian(EffRoteY), 0.0f);

				if (m_EffCnt == 1) {
					//�_���[�WSE�̍Đ�
					CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Thunder);
					CSoundManager::GetInstance()->Volume(CSoundManager::SE_Thunder, 80);

					hMagicLight = CEffect::Play(CEffect::Kaito_Magic, D3DXVECTOR3(m_vPosition.x - (-2.0f * vector), m_vPosition.y + 1.8f, m_vPosition.z + (0.2f * vector)));
				}

				m_AnimSpeed = 0.0f;
			}
		}

		if (m_EffCnt >= 120)
		{
			m_AttackAnimEnd = true;
			m_EffCnt = 0;
		}
	}
}

//�_���[�W���A�j���[�V����
void CKaito::DamageAnim(float vector)
{
	//�ǂ̃A�j���[�V�����̌�ł��Đ����x��ς��Ȃ�
	m_AnimSpeed = 0.01f;

	//���̃A�j���[�V�����Ŏg�p���Ă���A�j���[�V�����łȂ��ꍇ
	bool NotUseAnim = m_AnimNo != 0 && m_AnimNo != 7 && m_AnimNo != 1;

	//�ҋ@�A�j���[�V������
	if (NotUseAnim && !m_AnimChange) {
		AnimChange(0);
	}

	if (m_AnimNo == 0 && !m_AnimChange)
	{
		//�_���[�WSE�̍Đ�
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Damage);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Damage, 80);

		AnimChange(7);
	}

	if (m_AnimNo == 7)
	{

		//�A�j���[�V�����̌o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//�ʒu���������ɉ�����
		m_MoveX += (0.08f * vector);
		//�A�j���[�V�����J�E���g�̏�����
		m_AnimCnt = 0;

		if (m_pMesh->GetAnimPeriod(m_AnimNo)- 0.2 < m_AnimTime)
		{
			AnimChange(1);
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
			AnimChange(0);
		}
	}

	if (m_AnimNo == 0 && m_AnimChange)
	{
		//�߂��Ă���A�j���[�V�����I���܂łɊԂ�u��
		if (!m_DamageAnimEnd) 
		{
			m_AnimCnt++;
		}
		//�A�j���[�V�����̌o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (m_AnimCnt >= 120) 
		{
			m_DamageAnimEnd = true;
			m_AnimChange = false;
			m_AnimCnt = 0;
		}
	}

	SetPosition(m_MoveX, m_MoveY, m_MoveZ);
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

//�A�j���[�V�����؂�ւ�
void CKaito::AnimChange(int animno)
{
	CHeroBase::AnimChange(animno);
}


