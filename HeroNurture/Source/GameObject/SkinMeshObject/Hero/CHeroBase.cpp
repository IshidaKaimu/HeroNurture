#include "CHeroBase.h"
#include "Sound/CSoundManager.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include "KeyManager/CKeyManager.h"
#include <fstream>
#include <codecvt>


CHeroBase::CHeroBase()	
{
	SetScale(0.1f, 0.1f, 0.1f);
	m_pJson = std::make_unique<CJson>();
	LoadStatus(m_UserName);
}

CHeroBase::~CHeroBase()
{
}

void CHeroBase::Update()
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

void CHeroBase::Draw( LIGHT& Light )
{
	CSkinMeshObject::Draw( Light );
}

void CHeroBase::Animation()
{
}


//�f�[�^�ǂݍ��݊֐�
void CHeroBase::Fromjson(const json& j)
{
	if (!m_UserName.empty()) {
		j.at("Power").get_to(m_Para.Power);
		j.at("Magic").get_to(m_Para.Magic);
		j.at("Speed").get_to(m_Para.Speed);
		j.at("HP").get_to(m_Para.HP);
	}
}


//�f�[�^�ۑ��֐�
void CHeroBase::Tojson(json& j)
{
	j["Power"]    = m_Para.Power;
	j["Magic"]    = m_Para.Magic;
	j["Speed"]    = m_Para.Speed;
	j["HP"]		  = m_Para.HP;
}

//�X�e�[�^�X�Z�b�g�֐�
bool CHeroBase::LoadStatus(const string& name)
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

bool CHeroBase::SaveStatus(const string& name)
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

//�X�e�[�^�X�㏸�֐�
void CHeroBase::UpStatus(float sta, float inc)
{
	//�X�e�[�^�X���㏸������
	sta += inc;
}

