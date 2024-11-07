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

	ImGui::Begin(JAPANESE("パラメータ"));
	ImGui::InputInt(JAPANESE("筋力"), &m_Para.Power);	
	ImGui::InputInt(JAPANESE("魔力"), &m_Para.Magic);	
	ImGui::InputInt(JAPANESE("素早さ"), &m_Para.Speed);	
	ImGui::InputInt(JAPANESE("体力"), &m_Para.HP);	
	if (ImGui::Button(JAPANESE("保存")))
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


//データ読み込み関数
void CPlayer::Fromjson(const json& j)
{
	if (!m_UserName.empty()) {
		j.at("Power").get_to(m_Para.Power);
		j.at("Magic").get_to(m_Para.Magic);
		j.at("Speed").get_to(m_Para.Speed);
		j.at("HP").get_to(m_Para.HP);
	}
}


//データ保存関数
void CPlayer::Tojson(json& j)
{
	j["Power"]    = m_Para.Power;
	j["Magic"]    = m_Para.Magic;
	j["Speed"]    = m_Para.Speed;
	j["HP"]		  = m_Para.HP;
}

//ステータスセット関数
bool CPlayer::LoadStatus(const string& name)
{
	//読み込むファイル名の指定
	std::ifstream Ifile(name + ".json");

	//開けなかったらfalseへ
	if (!Ifile.is_open()) { return false; }

	json j;
	Ifile >> j;
	Ifile.close();

	//jsonのデータをセット
	Fromjson(j);

	return true;
}

bool CPlayer::SaveStatus(const string& name)
{
	//書き込むファイル名の指定
	std::ofstream Ofile(name + ".json");

	//開けなかったらfalseへ
	if (!Ofile.is_open()) { return false; }

	json j;
	Ofile << j;
	Ofile.close();

	//jsonのデータを記録
	Tojson(j);

	return true;
}

