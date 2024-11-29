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

//更新関数
void CHeroBase::Update()
{
	CKeyManager::GetInstance()->Update();
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
	//各パラメータの代入
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


