#include "CKaito.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"

CKaito::CKaito()
	: m_BonePos		()
	, m_Run			()
	, m_AnimChange	()
	, m_EffPosZ		(1.0f)

{
	SetScale(0.75f, 0.75f, 0.75f);
	SetPosition(0.0f, 0.0f, 1.2f);
}

CKaito::~CKaito()
{
}

//初期化関数
void CKaito::Initialize()
{
	//アニメーション関連の初期化
	AnimInit();
}

//バトルシーンで使用する初期化
void CKaito::BattleInitialize()
{
	//アニメーション関連の初期化
	AnimInit();

	SetPosition(BATTLEINIT_POS_KAITO);
	SetScale(BATTLEINIT_SCALE_KAITO);
	SetRotation(BATTLEINIT_ROTATE_KAITO);
}

//敵になった際の初期化関数
void CKaito::EnemyInit()
{
	//アニメーション関連の初期化
	AnimInit();

	SetPosition(ENEMYINIT_POS_KAITO);
	SetScale(BATTLEINIT_SCALE_KAITO);
	SetRotation(ENEMYINIT_ROTATE_KAITO);
}

//メッシュデータ読み込み関数
void CKaito::LoadMeshData()
{
	//メッシュデータの読み込み
	AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));
}

//パラメータ情報の読み込み
void CKaito::LoadParamData(const json& jsondata)
{
	if (!CSceneManager::GetInstance()->GetIsDataLoaded())
	{
		//パラメータの読み込み
		LoadParam(jsondata, "Kaito");
	}
	else
	{
		//パラメータの更新
		UpdateParam(jsondata, "Kaito");
	}
}

//バトルに使用するデータの読み込み
void CKaito::SetBattleParamData(const json& jsondata)
{
	//バトルに使用するデータの読み込み
	SetBattleParam(jsondata);
}

//更新関数
void CKaito::Update()
{

	//--------------------------
	//スキンメッシュ
	//--------------------------
	
	//Kaito
	//アニメーション番号メモ
	//0:待機
	//1:走り
	//2:斬る(右上から右下)
	//3:斬る(左下から右上に)
	//4:斬り下ろす
	//5:回避
	//6:手つき出す
	//7:ダメージ
	//8:死亡

}

//描画関数
void CKaito::Draw()
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw();
}

//デバッグ関数
void CKaito::Debug()
{
	ImGui::Begin(JAPANESE("Kaito"));
	ImGui::InputFloat3(JAPANESE("位置"), DebugPos);
	ImGui::InputFloat3(JAPANESE("拡縮"), DebugScale);
	ImGui::End();
	SetPosition(DebugPos);
	SetScale(DebugScale);
}

//育成ヒーロー選択シーンのアニメーション
void CKaito::NatureHeroSelectAnimation()
{
}

//バトルヒーロー選択シーンのアニメーション
void CKaito::BattleHeroSelectAnimation()
{
}

//育成シーンのアニメーション
void CKaito::NatureAnimation(int no)
{
	//アニメーションの経過時間を加算
	m_AnimTime += m_pMesh->GetAnimSpeed();
}

//アニメーション関連の初期化
void CKaito::AnimInit()
{
	//アニメーションスピードの設定
	m_AnimSpeed = 0.01f;
	//待機アニメーション
	m_AnimNo = 0;
	//アニメーションを設定
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
}


