#include "CHeroBase.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include <fstream>
#include <codecvt>

CHeroBase::CHeroBase()	
	: m_Param            ()
	, m_pJson            ()
	, m_UserName         ()
	, m_BeforeParam	     ()
	, m_Hp               ()
	, m_Correction	     (1.0f)
	, m_Failure		     (false)
	, m_MoveX		     ()
	, m_MoveY		     ()
	, m_MoveZ		     ()
	, m_Damage		     ()
	, m_AttackAnimEnd    ()
	, m_DamageAnimEnd    ()
	, m_AppealanceAnimEnd()
{
	m_pJson = std::make_unique<CJson>();
}

CHeroBase::~CHeroBase()
{
}

//�X�V�֐�
void CHeroBase::Update()
{
}

//�`��֐�
void CHeroBase::Draw()
{
	CSkinMeshObject::Draw();
}


float CHeroBase::PowerAttack()
{
	float Damage = m_BattleParam.Power * CUtility::GetInstance().GenerateRandomValue(1.0f, 1.5f);
	return Damage;
}

float CHeroBase::MagicAttack()
{
	float Damage = m_BattleParam.Magic * CUtility::GetInstance().GenerateRandomValue(1.0f, 1.5f);
	return Damage;
}

//�ؗ͏㏸
void CHeroBase::PowerUp( float stamina )
{
	//�X�^�~�i�ʂɂ��␳����
	CorrectionByStamina(stamina);
	//�g���[�j���O����
	TraningResult(stamina, m_App.PowerApp, m_Param.Power);
}

//���͏㏸
void CHeroBase::MagicUp( float stamina )
{
	//�X�^�~�i�ʂɂ��␳����
	CorrectionByStamina(stamina);
	//�g���[�j���O����
	TraningResult(stamina, m_App.MagicApp, m_Param.Magic);
}

//�f�����㏸
void CHeroBase::SpeedUp( float stamina )
{
	//�X�^�~�i�ʂɂ��␳����
	CorrectionByStamina(stamina);
	//�g���[�j���O����
	TraningResult(stamina, m_App.SpeedApp, m_Param.Speed);
}

//�̗͏㏸
void CHeroBase::HpUp( float stamina )
{
	//�X�^�~�i�ʂɂ��␳����
	CorrectionByStamina(stamina);
	//�g���[�j���O����
	TraningResult(stamina, m_App.HpApp, m_Param.Hp);
}

//�_���[�W�֐�
void CHeroBase::Damage(float damage)
{
	m_Hp -= damage;
	m_Damage = true;
}

//�A�j���[�V�����؂�ւ�
void CHeroBase::AnimChange(int animno)
{
	m_AnimNo = animno;
	m_AnimTime = 0;
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
}

//�e�q�[���[�̏����p�����[�^�̎擾
void CHeroBase::LoadParam( const json& jsondata, const std::string& heroname )
{
	//�t�@�C�����ɖ��O������Α��
	for (const auto& hero : jsondata)
	{
		if ( hero.contains("Name") && hero["Name"] == heroname)
		{
			//----�p�����[�^�ǂݍ���----
			m_Param.Power  = hero["Parameter"]["Power"].get<float>();
			m_Param.Magic  = hero["Parameter"]["Magic"].get<float>();
			m_Param.Speed  = hero["Parameter"]["Speed"].get<float>();
			m_Param.Hp     = hero["Parameter"]["Hp"].get<float>();
			//--------------------------

			//----�K�����̓ǂݍ���----
			m_App.PowerApp = hero["Appropriate"]["Power"].get<float>();
			m_App.MagicApp = hero["Appropriate"]["Magic"].get<float>();
			m_App.SpeedApp = hero["Appropriate"]["Speed"].get<float>();
			m_App.HpApp    = hero["Appropriate"]["Hp"].get<float>();
			//------------------------

			return;
		}
	}
}

//�o�g���Ɏg�p����p�����[�^���̐ݒ�
void CHeroBase::SetBattleParam(const json& jsondata)
{
	//----�p�����[�^�ǂݍ���----
	m_BattleParam.Power = jsondata["Parameter"]["Power"].get<float>();
	m_BattleParam.Magic = jsondata["Parameter"]["Magic"].get<float>();
	m_BattleParam.Speed = jsondata["Parameter"]["Speed"].get<float>();
	m_BattleParam.Hp = jsondata["Parameter"]["Hp"].get<float>();
	//--------------------------
}

//�e�q�[���[�̃p�����[�^�X�V
void CHeroBase::UpdateParam(const json& jsondata, const std::string& heroname)
{
	if (jsondata.contains("Name") && jsondata["Name"] == heroname)
	{
		//----�p�����[�^�ǂݍ���----
		m_Param.Power = jsondata["Parameter"]["Power"].get<float>();
		m_Param.Magic = jsondata["Parameter"]["Magic"].get<float>();
		m_Param.Speed = jsondata["Parameter"]["Speed"].get<float>();
		m_Param.Hp    = jsondata["Parameter"]["Hp"].get<float>();
		//--------------------------

		//----�K�����̓ǂݍ���----
		m_App.PowerApp = jsondata["Appropriate"]["Power"].get<float>();
		m_App.MagicApp = jsondata["Appropriate"]["Magic"].get<float>();
		m_App.SpeedApp = jsondata["Appropriate"]["Speed"].get<float>();
		m_App.HpApp = jsondata["Appropriate"]["Hp"].get<float>();
		//------------------------

		return;
	}
}

//�X�^�~�i�ʂɂ��␳����
void CHeroBase::CorrectionByStamina(float stamina)
{
	if (stamina <= 0.5f * MAX_STAMINA)
	{
		m_Correction = m_Correction * 0.8f;
	}
	else
	{
		m_Correction = 1.0f;
	}
}

//��������Ԃ��֐�
int CHeroBase::SuccessRate(float stamina)
{
	if (stamina <= 0.0f) return 1;
	if (stamina <= 10.0f) return 25;
	if (stamina <= 25.0f) return 50;
	if (stamina <= 60.0f) return 65;
	if (stamina <= 80.0f) return 80;
	if (stamina <= 90.0f) return 90;
	return 100;
}

//�g���[�j���O����
void CHeroBase::TraningResult(float stamina, float app, float& param)
{
	//���̗����Ő������邩�����߂�
	int Succes = CUtility::GenerateRandomValue(0, 100);

	if (Succes < SuccessRate(stamina)) {
		float AppBonus = INCREASE_VALUE * ( 1.0f + ( app / 100.0f ) );
		param += AppBonus * m_Correction;
	}
	else
	{
		m_Failure = true;
	}
}



