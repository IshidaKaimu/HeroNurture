#include "CHeroBase.h"
#include "Sound/CSoundManager.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include "KeyManager/CKeyManager.h"
#include <fstream>
#include <codecvt>


CHeroBase::CHeroBase()	
{
	m_pJson = std::make_unique<CJson>();
}

CHeroBase::~CHeroBase()
{
}

//�X�V�֐�
void CHeroBase::Update()
{
	CKeyManager::GetInstance()->Update();
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
			m_Para.Power = hero["Paramater"]["Power"];
			m_Para.Magic = hero["Paramater"]["Magic"];
			m_Para.Speed = hero["Paramater"]["Speed"];
			m_Para.Hp    = hero["Paramater"]["Hp"];
			return;
		}
	}

}


