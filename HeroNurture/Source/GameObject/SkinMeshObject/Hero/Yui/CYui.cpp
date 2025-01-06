#include "CYui.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"

CYui::CYui()
	: m_AnimChange()

{
	SetScale(0.1f, 0.1f, 0.1f);
}

CYui::~CYui()
{
}

//初期化関数
void CYui::Initialize()
{
	//クラスインスタンスを変数に代入
    //シーンマネージャー
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	//アニメーションスピードの設定
	m_AnimSpeed = 0.01f;
	//初めのアニメーションの設定
	m_AnimNo = 3;
	//登場アニメーション
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

	//白フェードの初期化
	SceneMng->InitWhiteFade();
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

//育成ヒーロー選択シーンのアニメーション
void CYui::NatureHeroSelectAnimation()
{
	//アニメーションスピードの設定
	m_AnimSpeed = 0.01f;
}

//バトルヒーロー選択シーンのアニメーション
void CYui::BattleHeroSelectAnimation()
{
	//アニメーションスピードの設定
	m_AnimSpeed = 0.01f;
}

//育成シーンのアニメーション
void CYui::NatureAnimation(int no)
{
	//アニメーションの経過時間を加算		
	m_AnimTime += m_pMesh->GetAnimSpeed();
}

//筋力トレーニングアニメーション
void CYui::PowerTraningAnimation()
{
}
//魔力トレーニングアニメーション
void CYui::MagicTraningAnimation()
{
}
//素早さトレーニングアニメーション
void CYui::SpeedTraningAnimation()
{
	//クラスインスタンスを変数に代入
	//シーンマネージャー
	CSceneManager* SceneMng = CSceneManager::GetInstance();
	//ヒーローマネージャー
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	m_EventCnt++;

	if (m_EventCnt <= 1)
	{
		HeroMng->SetPosition(-10.0f, 0.0f, 0.0f);
	}

	SceneMng->PlayWhiteFade(1, 0.01f, 0.8f);
}
//体力トレーニングアニメーション
void CYui::HpTraningAnimation()
{
}

void CYui::AnimChange()
{
	m_AnimChange = true;
}



