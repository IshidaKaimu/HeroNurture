#include "CHeroBase.h"
#include "Sound/CSoundManager.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include <fstream>
#include <codecvt>


CHeroBase::CHeroBase()	
	: m_Param          ()
	, m_pJson          ()
	, m_UserName       ()
	, m_Stamina		   ( 100.0f )
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


//筋力上昇
void CHeroBase::PowerUp()
{
	float AppBonus = INCREASE_VALUE * (1.0 + (m_App.PowerApp / 100.0));
	m_Param.Power += AppBonus;
}

//魔力上昇
void CHeroBase::MagicUp()
{
	float AppBonus = INCREASE_VALUE * (1.0 + (m_App.MagicApp / 100.0));
	m_Param.Magic += AppBonus;
}

//素早さ上昇
void CHeroBase::SpeedUp()
{
	float AppBonus = INCREASE_VALUE * (1.0 + (m_App.SpeedApp / 100.0));
	m_Param.Speed += AppBonus;
}

//体力上昇
void CHeroBase::HpUp()
{
	float AppBonus = INCREASE_VALUE * (1.0 + (m_App.HpApp / 100.0));
	m_Param.Hp += AppBonus;
}

//各ヒーローの初期パラメータの取得
void CHeroBase::LoadParam( const json& jsondata, const std::string& heroname )
{
	//ファイル内に名前があれば代入
	for (const auto& hero : jsondata)
	{
		if ( hero.contains("Name") && hero["Name"] == heroname)
		{
			//----パラメータ読み込み----
			m_Param.Power  = hero["Parameter"]["Power"].get<float>();
			m_Param.Magic  = hero["Parameter"]["Magic"].get<float>();
			m_Param.Speed  = hero["Parameter"]["Speed"].get<float>();
			m_Param.Hp     = hero["Parameter"]["Hp"].get<float>();
			//----適正率の読み込み----
			m_App.PowerApp = hero["Appropriate"]["Power"].get<float>();
			m_App.MagicApp = hero["Appropriate"]["Magic"].get<float>();
			m_App.SpeedApp = hero["Appropriate"]["Speed"].get<float>();
			m_App.HpApp    = hero["Appropriate"]["Hp"].get<float>();
			return;
		}
	}

}

//各ヒーローのパラメータ更新
void CHeroBase::UpdateParam(const json& jsondata, const std::string& heroname)
{
	if (jsondata.contains("Name") && jsondata["Name"] == heroname)
	{
		//----パラメータ読み込み----
		m_Param.Power = jsondata["Parameter"]["Power"].get<float>();
		m_Param.Magic = jsondata["Parameter"]["Magic"].get<float>();
		m_Param.Speed = jsondata["Parameter"]["Speed"].get<float>();
		m_Param.Hp    = jsondata["Parameter"]["Hp"].get<float>();
		//----適正率の読み込み----
		m_App.PowerApp = jsondata["Appropriate"]["Power"].get<float>();
		m_App.MagicApp = jsondata["Appropriate"]["Magic"].get<float>();
		m_App.SpeedApp = jsondata["Appropriate"]["Speed"].get<float>();
		m_App.HpApp = jsondata["Appropriate"]["Hp"].get<float>();

		return;
	}
}



