#include "CHeroBase.h"
#include "Sound/CSoundManager.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include <fstream>
#include <codecvt>


CHeroBase::CHeroBase()	
	: m_Param          ()
	, m_pJson          ()
	, m_UserName       ()
	, m_EventCnt	   ()
	, m_BeforeParam	   ()
	, m_Correction	   (1.0)
	, m_Failure		   (false)
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
void CHeroBase::PowerUp( float stamina )
{
	//スタミナ量による補正処理
	CorrectionByStamina(stamina);
	//トレーニング結果
	TraningResult(stamina, m_App.PowerApp, m_Param.Power);
}

//魔力上昇
void CHeroBase::MagicUp( float stamina )
{
	//スタミナ量による補正処理
	CorrectionByStamina(stamina);
	//トレーニング結果
	TraningResult(stamina, m_App.MagicApp, m_Param.Magic);
}

//素早さ上昇
void CHeroBase::SpeedUp( float stamina )
{
	//スタミナ量による補正処理
	CorrectionByStamina(stamina);
	//トレーニング結果
	TraningResult(stamina, m_App.SpeedApp, m_Param.Speed);
}

//体力上昇
void CHeroBase::HpUp( float stamina )
{
	//スタミナ量による補正処理
	CorrectionByStamina(stamina);
	//トレーニング結果
	TraningResult(stamina, m_App.HpApp, m_Param.Hp);
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

//スタミナ量による補正処理
void CHeroBase::CorrectionByStamina(float stamina)
{
	if (stamina <= 0.5 * MAX_STAMINA)
	{
		m_Correction = m_Correction * 0.8;
	}
	else
	{
		m_Correction = 1.0f;
	}
}

//失敗率を返す関数
int CHeroBase::FailureRate(float stamina)
{
	if (stamina <= 0) return 99;
	if (stamina <= 30) return 75;
	if (stamina <= 50) return 50;
	if (stamina <= 80) return 20;
	return 0;
}

//トレーニング結果
void CHeroBase::TraningResult(float stamina, float app, float& param)
{
	//この乱数で成功するかを決める
	int Succes = CUtility::GenerateRandomValue(0, 100);

	if (Succes >= FailureRate(stamina)) {
		float AppBonus = INCREASE_VALUE * ( 1.0 + ( app / 100.0 ) );
		param += AppBonus * m_Correction;
	}
	else
	{
		m_Failure = true;
	}
}



