#include "CHeroBase.h"
#include "Sound/CSoundManager.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include <fstream>
#include <codecvt>


CHeroBase::CHeroBase()	
	: m_Param          ()
	, m_pJson          ()
	, m_UserName       ()
	, m_Correction	   (1.0)
	, m_Failure		   (false)
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


//�ؗ͏㏸
void CHeroBase::PowerUp( float stamina )
{
	//�X�^�~�i�ʂɂ��␳����
	CorrectionByStamina(stamina);

	//���̗����Ő������邩�����߂�
	int Succes = CUtility::GenerateRandomValue(0,100);

	//���s���̒l�����傫�����
	if (Succes >= FailureRate(stamina)) {
		float AppBonus = INCREASE_VALUE * (1.0 + (m_App.PowerApp / 100.0));
		m_Param.Power += AppBonus * m_Correction;
	}
	else
	{
		m_Failure = true;
	}
}

//���͏㏸
void CHeroBase::MagicUp( float stamina )
{
	//�X�^�~�i�ʂɂ��␳����
	CorrectionByStamina(stamina);

	//���̗����Ő������邩�����߂�
	int Succes = CUtility::GenerateRandomValue(0, 100);
	
	//���s���̒l�����傫�����
	if (Succes >= FailureRate(stamina)) {
		float AppBonus = INCREASE_VALUE * (1.0 + (m_App.MagicApp / 100.0));
		m_Param.Magic += AppBonus * m_Correction;
	}
	else
	{
		m_Failure = true;
	}
}

//�f�����㏸
void CHeroBase::SpeedUp( float stamina )
{
	//�X�^�~�i�ʂɂ��␳����
	CorrectionByStamina(stamina);
	
	//���̗����Ő������邩�����߂�
	int Succes = CUtility::GenerateRandomValue(0, 100);
	//���s���̒l�����傫�����
	if (Succes >= FailureRate(stamina)) {
		float AppBonus = INCREASE_VALUE * (1.0 + (m_App.SpeedApp / 100.0));
		m_Param.Speed += AppBonus * m_Correction;
	}
	else
	{
		m_Failure = true;
	}
}

//�̗͏㏸
void CHeroBase::HpUp( float stamina )
{
	//�X�^�~�i�ʂɂ��␳����
	CorrectionByStamina(stamina);

	//���̗����Ő������邩�����߂�
	int Succes = CUtility::GenerateRandomValue(0, 100);

	float AppBonus = INCREASE_VALUE * (1.0 + (m_App.HpApp / 100.0));
	m_Param.Hp += AppBonus * m_Correction;
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
			//----�K�����̓ǂݍ���----
			m_App.PowerApp = hero["Appropriate"]["Power"].get<float>();
			m_App.MagicApp = hero["Appropriate"]["Magic"].get<float>();
			m_App.SpeedApp = hero["Appropriate"]["Speed"].get<float>();
			m_App.HpApp    = hero["Appropriate"]["Hp"].get<float>();
			return;
		}
	}

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
		//----�K�����̓ǂݍ���----
		m_App.PowerApp = jsondata["Appropriate"]["Power"].get<float>();
		m_App.MagicApp = jsondata["Appropriate"]["Magic"].get<float>();
		m_App.SpeedApp = jsondata["Appropriate"]["Speed"].get<float>();
		m_App.HpApp = jsondata["Appropriate"]["Hp"].get<float>();

		return;
	}
}

//�X�^�~�i�ʂɂ��␳����
void CHeroBase::CorrectionByStamina(float stamina)
{
	if (stamina <= 0.5 * MAX_STAMINA)
	{
		m_Correction = m_Correction * 0.8;
	}
	else
	{
		m_Correction = 1.0f;
	}
}

//���s����Ԃ��֐�
int CHeroBase::FailureRate(float stamina)
{
	if (stamina <= 0) return 99;
	if (stamina <= 30) return 75;
	if (stamina <= 50) return 50;
	if (stamina <= 80) return 20;
	return 0;
}



