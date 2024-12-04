#include "CHeroBase.h"
#include "Sound/CSoundManager.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include <fstream>
#include <codecvt>


CHeroBase::CHeroBase()	
	: m_Param          ()
	, m_pJson          ()
	, m_UserName       ()
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

//�A�j���[�V�����֐�
void CHeroBase::Animation()
{
}


//�e�q�[���[�̏����p�����[�^�̎擾
void CHeroBase::LoadParam( const json& jsondata, const std::string& heroname )
{
	//�t�@�C�����ɖ��O������Α��
	for (const auto& hero : jsondata)
	{
		if ( hero.contains("Name") && hero["Name"] == heroname)
		{
			m_Param.Power = hero["Paramater"]["Power"].get<int>();
			m_Param.Magic = hero["Paramater"]["Magic"].get<int>();
			m_Param.Speed = hero["Paramater"]["Speed"].get<int>();
			m_Param.Hp    = hero["Paramater"]["Hp"].get<int>();
			return;
		}
	}

}

//�e�q�[���[�̃p�����[�^�X�V
void CHeroBase::UpdateParam(const json& jsondata, const std::string& heroname)
{
	if (jsondata.contains("Name") && jsondata["Name"] == heroname)
	{
		m_Param.Power = jsondata["Paramater"]["Power"].get<int>();
		m_Param.Magic = jsondata["Paramater"]["Magic"].get<int>();
		m_Param.Speed = jsondata["Paramater"]["Speed"].get<int>();
		m_Param.Hp    = jsondata["Paramater"]["Hp"].get<int>();
		return;
	}
}



