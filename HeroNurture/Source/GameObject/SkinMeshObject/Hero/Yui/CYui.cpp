#include "CYui.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"

CYui::CYui()
	: m_BonePos()
	, m_Run()
	, m_AnimChange()
	, m_EffPosZ(1.0f)

{
	SetScale(0.1f, 0.1f, 0.1f);
}

CYui::~CYui()
{
}

//初期化関数
void CYui::Initialize()
{
	//アニメーションスピードの設定
	m_AnimSpeed = 0.01f;
	//初めのアニメーションの設定
	m_AnimNo = 3;
	//登場アニメーション
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

}

//データ読み込み関数
void CYui::LoadData( const json& jsondata )
{
	//メッシュデータの読み込み
	AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
	
	//各パラメータの代入
	m_Para.Power = jsondata["Paramater"]["Power"];
	m_Para.Magic = jsondata["Paramater"]["Magic"];
	m_Para.Speed = jsondata["Paramater"]["Speed"];
	m_Para.Hp    = jsondata["Paramater"]["Hp"];


}

//更新関数
void CYui::Update()
{
}

//描画関数
void CYui::Draw(LIGHT& Light)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw(Light);
}

//アニメーション関数
void CYui::Animation()
{
	if (m_AnimNo == 3)
	{

	}

	//アニメーションの経過時間を加算		
	m_AnimTime += m_pMesh->GetAnimSpeed();
}

void CYui::AnimChange()
{
	m_AnimChange = true;
}



