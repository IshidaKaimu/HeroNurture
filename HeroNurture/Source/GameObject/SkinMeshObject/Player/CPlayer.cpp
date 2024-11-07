#include "CPlayer.h"
#include "Sound/CSoundManager.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include "KeyManager/CKeyManager.h"
#include <fstream>
#include <codecvt>


CPlayer::CPlayer()	
{
	SetScale(0.1f, 0.1f, 0.1f);
	m_pJson = std::make_unique<CJson>();
	LoadStatus(m_UserName);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{

	CKeyManager::GetInstance()->Update();

	ImGui::Begin(JAPANESE("�p�����[�^"));
	ImGui::InputInt(JAPANESE("�ؗ�"), &m_Para.Power);	
	ImGui::InputInt(JAPANESE("����"), &m_Para.Magic);	
	ImGui::InputInt(JAPANESE("�f����"), &m_Para.Speed);	
	ImGui::InputInt(JAPANESE("�̗�"), &m_Para.HP);	
	if (ImGui::Button(JAPANESE("�ۑ�")))
	{
		m_pJson->Save(m_UserName);
	}
	ImGui::End();


}

void CPlayer::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera )
{
	CSkinMeshObject::Draw( View, Proj, Light, Camera );
}


//�f�[�^�ǂݍ��݊֐�
void CPlayer::Fromjson(const json& j)
{
	if (!m_UserName.empty()) {
		j.at("Power").get_to(m_Para.Power);
		j.at("Magic").get_to(m_Para.Magic);
		j.at("Speed").get_to(m_Para.Speed);
		j.at("HP").get_to(m_Para.HP);
	}
}


//�f�[�^�ۑ��֐�
void CPlayer::Tojson(json& j)
{
	j["Power"]    = m_Para.Power;
	j["Magic"]    = m_Para.Magic;
	j["Speed"]    = m_Para.Speed;
	j["HP"]		  = m_Para.HP;
}

//�X�e�[�^�X�Z�b�g�֐�
bool CPlayer::LoadStatus(const string& name)
{
	//�ǂݍ��ރt�@�C�����̎w��
	std::ifstream Ifile(name + ".json");

	//�J���Ȃ�������false��
	if (!Ifile.is_open()) { return false; }

	json j;
	Ifile >> j;
	Ifile.close();

	//json�̃f�[�^���Z�b�g
	Fromjson(j);

	return true;
}

bool CPlayer::SaveStatus(const string& name)
{
	//�������ރt�@�C�����̎w��
	std::ofstream Ofile(name + ".json");

	//�J���Ȃ�������false��
	if (!Ofile.is_open()) { return false; }

	json j;
	Ofile << j;
	Ofile.close();

	//json�̃f�[�^���L�^
	Tojson(j);

	return true;
}

