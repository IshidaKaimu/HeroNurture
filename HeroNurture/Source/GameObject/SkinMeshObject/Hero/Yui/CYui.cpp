#include "CYui.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"

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

//メッシュデータ読み込み関数
void CYui::LoadMeshData()
{
	//メッシュデータの読み込み
	AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
}

//パラメータ情報の読み込み
void CYui::LoadParamData(const json& jsondata)
{
	if (!CSceneManager::GetInstance()->GetIsDataLoaded()) 
	{
		//パラメータの読み込み
		LoadParam(jsondata, "Yui");
	}
	else
	{
		//パラメータの更新
		UpdateParam(jsondata, "Yui");
	}
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

//ヒーロー選択シーンのアニメーション
void CYui::SelectAnimation()
{
}

//育成シーンのアニメーション
void CYui::NatureAnimation(int no)
{
	//アニメーションの経過時間を加算		
	m_AnimTime += m_pMesh->GetAnimSpeed();
}

void CYui::AnimChange()
{
	m_AnimChange = true;
}



