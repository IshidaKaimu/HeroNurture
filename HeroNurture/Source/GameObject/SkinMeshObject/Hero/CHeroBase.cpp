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

//更新関数
void CHeroBase::Update()
{
}

//描画関数
void CHeroBase::Draw()
{
	CSkinMeshObject::Draw();
}

//アニメーション関数
void CHeroBase::Animation()
{
}


//各ヒーローの初期パラメータの取得
void CHeroBase::LoadParam( const json& jsondata, const std::string& heroname )
{
	//ファイル内に名前があれば代入
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

//各ヒーローのパラメータ更新
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



