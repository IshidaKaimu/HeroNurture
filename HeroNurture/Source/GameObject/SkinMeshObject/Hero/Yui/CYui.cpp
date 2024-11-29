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

	//パラメータの読み込み
	LoadParam(jsondata, "Yui");
}

//更新関数
void CYui::Update()
{
}

//描画関数
void CYui::Draw()
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw();
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



