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

	SetPosition(BATTLEINIT_POS);
	SetScale(BATTLE_SCALE_KAITO);
	SetRotation(BATTLE_ROTATE);

	//アニメーションの開始地点の固定
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;

}

//敵になった際の初期化関数
void CKaito::EnemyInit()
{
	//アニメーション関連の初期化
	AnimInit();

	SetPosition(ENEMYINIT_POS);
	SetScale(BATTLE_SCALE_KAITO);
	SetRotation(ENEMY_ROTATE);

	//アニメーションの開始地点の固定
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;

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

//行動選択中のアニメーション
void CKaito::MoveSelectAnim()
{
	if (m_AnimNo == 0) {
		//アニメーションの経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();
		m_AnimCnt++;
	}

	if (m_AnimCnt >= 180)
	{
		//斬り下ろしアニメーション
		m_AnimNo = 3;
		//アニメーションの経過時間をリセット
		m_AnimTime = 0;
		//アニメーションを設定
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		//カウントをリセット
		m_AnimCnt = 0;
	}

	if (m_AnimNo == 3)
	{
		//アニメーションの経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			//待機アニメーション
			m_AnimNo = 0;
			//アニメーションの経過時間をリセット
			m_AnimTime = 0;
			//アニメーションを設定
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}
	}
}

float CKaito::PowerAttack()
{
	return CHeroBase::PowerAttack();
}

float CKaito::MagicAttack()
{
	return CHeroBase::MagicAttack();
}

float CKaito::UniqueAttack()
{
	float Damage = m_BattleParam.Power * CUtility::GetInstance().GenerateRandomValue(2.0f, 2.5f);
	m_UniqueGage -= 5;
	return Damage;
}

void CKaito::PowerAttackAnim(float vector)
{

}

void CKaito::MagicAttackAnim(float vector)
{
}

void CKaito::UniqueAttackAnim(float vector)
{
}

void CKaito::DamageAnim(float vector)
{
	//待機アニメーション時
	if ((m_AnimNo == 0 || m_AnimNo == 3) && !m_AnimChange) {
		m_AnimNo = 7;
		m_AnimTime = 0;
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
	}

	if (m_AnimNo == 7)
	{
		//アニメーションの経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//位置を後ろ向きに下げる
		if (m_AnimCnt <= 120)
		{
			m_MoveX += (0.08f * vector);
		}

		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_AnimNo = 1;
			m_AnimTime = 0;
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}
	}

	if (m_AnimNo == 1)
	{
		//アニメーションの経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		bool Return = m_MoveX <= BATTLEINIT_POS.x;     //自分側の場合
		bool EnemyReturn = m_MoveX >= ENEMYINIT_POS.x; //敵側の場合

		//最初の位置に戻る
		if (Return || EnemyReturn)
		{
			m_MoveX -= (0.08f * vector);
		}
		else
		{
			//同じアニメーション番号でも別の処理ができるように
			m_AnimChange = true;
			AnimChange(0);
		}
	}

	if (m_AnimNo == 0 && m_AnimChange)
	{
		//アニメーションの経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_AnimEnd = true;
			m_AnimChange = false;
		}
	}

	SetPosition(m_MoveX, m_MoveY, m_MoveZ);
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

//アニメーション切り替え
void CKaito::AnimChange(int animno)
{
	CHeroBase::AnimChange(animno);
}


