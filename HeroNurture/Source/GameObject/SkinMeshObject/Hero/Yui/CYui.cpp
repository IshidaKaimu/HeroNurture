#include "CYui.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"

CYui::CYui()
	: m_AnimChange()
	, m_MoveRotateY(0.0f)
	, m_RotateSpeedY(1.0f)
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

//バトルシーンで使用する初期化
void CYui::BattleInitialize()
{
	//アニメーション関連の初期化
	AnimInit();

	//座標の設定
	SetPosition(BATTLEINIT_POS);
	//拡縮の設定
	SetScale(BATTLE_SCALE_YUI);
	//回転の設定
	SetRotation(BATTLE_ROTATE);

	//アニメーションの開始地点の固定
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;
}

//敵になった際の初期化関数
void CYui::EnemyInit()
{
	//アニメーション関連の初期化
	AnimInit();

	//座標の設定
	SetPosition(ENEMYINIT_POS);
	//拡縮の設定
	SetScale(BATTLE_SCALE_YUI);
	//回転の設定
	SetRotation(ENEMY_ROTATE);
	
	//アニメーションの開始地点の固定
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;

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

//バトルに使用するデータの読み込み
void CYui::SetBattleParamData(const json& jsondata)
{
	//バトルに使用するデータの読み込み
	SetBattleParam(jsondata);
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

//デバッグ関数
void CYui::Debug()
{
	ImGui::Begin(JAPANESE("Yui"));
	ImGui::InputFloat3(JAPANESE("位置"),DebugPos);
	ImGui::InputFloat3(JAPANESE("拡縮"), DebugScale);
	ImGui::End();
	SetPosition(DebugPos);
	SetScale(DebugScale);
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

void CYui::MoveSelectAnim()
{
	if (m_AnimNo == 3)
	{
		m_AnimTime += m_pMesh->GetAnimSpeed();
	}
}

//攻撃1中のアニメーション
void CYui::PowerAttackAnim(float vector)
{
	if (!m_AnimEnd) {
		m_AnimCnt++;
	}

	if (m_AnimCnt >= 60) {
		AnimChange(4);
	}

	if(m_AnimNo == 4)
	{
		if (m_AnimCnt >= 80) 
		{
			if (m_AnimCnt % 30 == 0)
			{
				if (m_RotateSpeedY <= 8.0f) {
					m_RotateSpeedY += 0.05f;
				}
			}
			m_MoveRotateY += m_RotateSpeedY;

			if (m_AnimCnt <= 120) {
				m_MoveX -= 0.1f * vector;
				if (m_MoveRotateZ <= 0.5f) {
					m_MoveRotateZ += 0.005f;
				}
			}
			if (m_AnimCnt >= 150)
			{
				if (m_MoveRotateZ >= -0.35f)
				{
					m_MoveRotateZ -= 0.01f;
				}
			}
			if (m_AnimCnt >= 240)
			{
				m_MoveX += (0.2f * vector);
			}

			SetRotation(BATTLE_ROTATE.x, m_MoveRotateY, m_MoveRotateZ * vector);
		}
	}

	if (m_AnimCnt >= 300)
	{
		m_AnimCnt = 0;
		m_MoveRotateZ = 0;
		m_AnimEnd = true;
	}

	SetPosition(m_MoveX, m_MoveY, m_MoveZ);
}

void CYui::MagicAttackAnim(float vector)
{
}

void CYui::UniqueAttackAnim(float vector)
{
}

//攻撃1
float CYui::PowerAttack()
{
	return CHeroBase::PowerAttack();
}

//攻撃2
float CYui::MagicAttack()
{
	return CHeroBase::MagicAttack();
}

//固有攻撃
float CYui::UniqueAttack()
{
	float Damage = m_BattleParam.Magic * CUtility::GetInstance().GenerateRandomValue(2.0f, 2.5f);
	m_UniqueGage -= 5;
	return Damage;
}

//アニメーションに関する初期化
void CYui::AnimInit()
{
	//アニメーションスピードの設定
	m_AnimSpeed = 0.01f;
	//初めのアニメーションの設定
	m_AnimNo = 3;
	//登場アニメーション
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
}

//アニメーション切り替え関数
void CYui::AnimChange(int animno)
{
	CHeroBase::AnimChange(animno);
}


