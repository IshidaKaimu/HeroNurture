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

	ImGui::Begin(JAPANESE("パラメータ"));
	ImGui::InputInt(JAPANESE("筋力"), &m_Para.Power);	
	ImGui::InputInt(JAPANESE("魔力"), &m_Para.Magic);	
	ImGui::InputInt(JAPANESE("素早さ"), &m_Para.Speed);	
	ImGui::InputInt(JAPANESE("体力"), &m_Para.HP);	
	if (ImGui::Button(JAPANESE("保存")))
	{
		WriteData(m_UserName,m_Para.Power,m_Para.Magic,m_Para.Speed,m_Para.HP);
	}
	ImGui::End();


}

//データの書き込み
void CPlayer::WriteData(std::wstring name, int power, int magic, int speed, int hp)
{

	//ファイルの作成
	//wstring→stringへの変換用
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	//変換
	string FileName = converter.to_bytes(name);

	//保存先指定
	string Folda = "Data/Acount/";

	//拡張子
	string Directory = ".json";

	string Path = Folda + FileName + Directory;

	//パラメータごとに書き込み
	//筋力
	Status["Paramater"]["Power"] = power;
	//魔力
	Status["Paramater"]["Magic"] = magic;
	//素早さ
	Status["Paramater"]["Speed"] = speed;
	//体力
	Status["Paramater"]["Hp"] = hp;

	//作成したファイル
	ofstream StatusFile;
	//書き込み
	StatusFile.open(Path, std::ios::out);
	StatusFile << Status.dump();
	//閉じる
	StatusFile.close();


}

//データの読み込み
void CPlayer::SetData(std::wstring& name)
{
	//読み込むファイルの名前
	wstring StatusFile = name;

	//ファイルを読み込んで内容を画面に表示
	//c_str null文字に変換
	ifstream Loader(StatusFile.c_str());
	//正常に読み込めていれば
	if (Loader.good())
	{
		json Status;
		Loader >> Status;

		//読み込んだデータを代入
		if (!Status.empty()) {
			m_Para.Power = Status["Paramater"]["Power"];
			m_Para.Magic = Status["Paramater"]["Magic"];
			m_Para.Speed = Status["Paramater"]["Speed"];
			m_Para.HP = Status["Paramater"]["Hp"];
		}
	}
}

//アカウントデータの作成
void CPlayer::MakeData(std::wstring& name)
{
	//ファイルの作成
	//wstring→stringへの変換用
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	//変換
	string FileName = converter.to_bytes(name);
	//保存先指定
	string Folda = "Data/Acount/";
	//拡張子
	string Directory = ".json";

	string Path = Folda + FileName + Directory;

	//作成したファイル
	ofstream StatusFile;
	StatusFile.open(Path, ios::out);
	//閉じる
	StatusFile.close();

}



void CPlayer::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera )
{
	CSkinMeshObject::Draw( View, Proj, Light, Camera );
}
