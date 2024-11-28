#include "CKaito.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"

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

//データ読み込み関数
void CKaito::LoadData( const json& jsondata )
{
	//メッシュデータの読み込み
	AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));

	//各パラメータの代入
	m_Para.Power = jsondata["Paramater"]["Power"];
	m_Para.Magic = jsondata["Paramater"]["Magic"];
	m_Para.Speed = jsondata["Paramater"]["Speed"];
	m_Para.Hp    = jsondata["Paramater"]["Hp"];

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
void CKaito::Draw( LIGHT& Light )
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw( Light );
}

//アニメーション関数
void CKaito::Animation()
{
	if (m_AnimNo == 0)
	{
		
	}

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



