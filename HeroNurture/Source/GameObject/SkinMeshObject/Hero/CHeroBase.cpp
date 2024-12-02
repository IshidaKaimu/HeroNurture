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
	//�e�p�����[�^�̑��
	for (const auto& hero : jsondata)
	{
		if ( hero["Name"] == heroname )
		{
			m_Param.Power = hero["Paramater"]["Power"];
			m_Param.Magic = hero["Paramater"]["Magic"];
			m_Param.Speed = hero["Paramater"]["Speed"];
			m_Param.Hp    = hero["Paramater"]["Hp"];
			return;
		}
	}

}


