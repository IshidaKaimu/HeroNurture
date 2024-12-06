#include "CKaito.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"

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
	//アニメーションスピードの設定
	m_AnimSpeed = 0.01f;
	//待機アニメーション
	m_AnimNo = 0;	
	//アニメーションを設定
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
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

//ヒーロー選択シーンのアニメーション
void CKaito::SelectAnimation()
{
}

//育成シーンのアニメーション
void CKaito::NatureAnimation(int no)
{
	//アニメーションの経過時間を加算
	m_AnimTime += m_pMesh->GetAnimSpeed();
}

bool CKaito::SceneChange()
{
	if (m_EffPosZ >= 10.0f)
	{
		return true;
	}
	return false;
}

void CKaito::AnimChange()
{
	m_AnimChange = true;
}



