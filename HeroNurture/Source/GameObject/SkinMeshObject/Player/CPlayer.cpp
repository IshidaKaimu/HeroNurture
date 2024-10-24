#include "CPlayer.h"
#include "Sound/CSoundManager.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include "KeyManager/CKeyManager.h"
#include <fstream>
#include <codecvt>

CPlayer::CPlayer()	
{
	SetScale(0.1f, 0.1f, 0.1f);
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
		WriteData(m_UserName,m_Para.Power,m_Para.Magic,m_Para.Speed,m_Para.HP);
	}
	ImGui::End();


}

//�f�[�^�̏�������
void CPlayer::WriteData(std::wstring name, int power, int magic, int speed, int hp)
{

	//�t�@�C���̍쐬
	//wstring��string�ւ̕ϊ��p
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	//�ϊ�
	string FileName = converter.to_bytes(name);

	//�ۑ���w��
	string Folda = "Data/Acount/";

	//�g���q
	string Directory = ".json";

	string Path = Folda + FileName + Directory;

	//�p�����[�^���Ƃɏ�������
	//�ؗ�
	Status["Paramater"]["Power"] = power;
	//����
	Status["Paramater"]["Magic"] = magic;
	//�f����
	Status["Paramater"]["Speed"] = speed;
	//�̗�
	Status["Paramater"]["Hp"] = hp;

	//�쐬�����t�@�C��
	ofstream StatusFile;
	//��������
	StatusFile.open(Path, std::ios::out);
	StatusFile << Status.dump();
	//����
	StatusFile.close();


}

//�f�[�^�̓ǂݍ���
void CPlayer::SetData(std::wstring& name)
{
	//�ǂݍ��ރt�@�C���̖��O
	wstring StatusFile = name;

	//�t�@�C����ǂݍ���œ��e����ʂɕ\��
	//c_str null�����ɕϊ�
	ifstream Loader(StatusFile.c_str());
	//����ɓǂݍ��߂Ă����
	if (Loader.good())
	{
		json Status;
		Loader >> Status;

		//�ǂݍ��񂾃f�[�^����
		if (!Status.empty()) {
			m_Para.Power = Status["Paramater"]["Power"];
			m_Para.Magic = Status["Paramater"]["Magic"];
			m_Para.Speed = Status["Paramater"]["Speed"];
			m_Para.HP = Status["Paramater"]["Hp"];
		}
	}
}

//�A�J�E���g�f�[�^�̍쐬
void CPlayer::MakeData(std::wstring& name)
{
	//�t�@�C���̍쐬
	//wstring��string�ւ̕ϊ��p
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	//�ϊ�
	string FileName = converter.to_bytes(name);
	//�ۑ���w��
	string Folda = "Data/Acount/";
	//�g���q
	string Directory = ".json";

	string Path = Folda + FileName + Directory;

	//�쐬�����t�@�C��
	ofstream StatusFile;
	StatusFile.open(Path, ios::out);
	//����
	StatusFile.close();

}



void CPlayer::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera )
{
	CSkinMeshObject::Draw( View, Proj, Light, Camera );
}
