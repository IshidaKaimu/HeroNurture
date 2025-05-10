#include "CKaito.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"

//定数の名前空間
using namespace Constant_Kaito;

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
	SetScale(BATTLE_SCALE);
	SetRotation(BATTLE_ROTATE);

	//アニメーション終了フラグの初期化
	m_AttackAnimEnd = false;
	//ダメージアニメーション終了フラグの初期化
	m_DamageAnimEnd = false;
	//ダメージフラグの初期化
	m_Damage = false;
	//アニメーション切り替えフラグの初期化
	m_AnimChange = false;
	//アニメーションカウントの初期化
	m_AnimCnt = 0;

	//アニメーションの開始地点の固定
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;

}

//敵になった際の初期化関数
void CKaito::EnemyInitialize()
{
	//アニメーション関連の初期化
	AnimInit();

	SetPosition(ENEMYINIT_POS);
	SetScale(BATTLE_SCALE);
	SetRotation(ENEMY_ROTATE);

	//アニメーション終了フラグの初期化
	m_AttackAnimEnd = false;
	//ダメージアニメーション終了フラグの初期化
	m_DamageAnimEnd = false;
	//ダメージフラグの初期化
	m_Damage = false;
	//アニメーション切り替えフラグの初期化
	m_AnimChange = false;
	//アニメーションカウントの初期化
	m_AnimCnt = 0;

	//アニメーションの開始地点の固定
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;

}

void CKaito::AppearanceInitialize()
{
	//座標の設定
	SetPosition(APPEALANCE_POS);

	//アニメーション関連の初期化
	AnimInit();
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
#if _DEBUG
	ImGui::Begin(JAPANESE("Kaito"));
	ImGui::Text(JAPANESE("位置x:%f"), m_vPosition.x);
	ImGui::Text(JAPANESE("位置y:%f"), m_vPosition.y);
	ImGui::Text(JAPANESE("位置z:%f"), m_vPosition.z);
	ImGui::End();
#endif
}

//育成ヒーロー選択シーンのアニメーション
void CKaito::NatureHeroSelectAnimation()
{
}

//バトルヒーロー選択シーンのアニメーション
void CKaito::BattleHeroSelectAnimation()
{
}

//バトル開始時登場シーンのアニメーション
void CKaito::AppearanceAnimation()
{
	//アニメーション番号が0以外だった場合0に
	if (m_AnimNo != 0)
	{
		AnimChange(0);
	}

	if (m_vPosition.y <= AFTER_POS_Y)
	{
		m_vPosition.y += APPEALANCE_SPEED;
	}

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
		if (m_AnimCnt >= 180)
		{
			AnimChange(3);
			m_AnimCnt = 0;
		}
	}

	if (m_AnimNo == 3)
	{
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			AnimChange(0);
		}
	}
}

//攻撃1
float CKaito::PowerAttack()
{
	return CHeroBase::PowerAttack();
}

//攻撃2
float CKaito::MagicAttack()
{
	return CHeroBase::MagicAttack();
}

//攻撃1アニメーション
void CKaito::PowerAttackAnim(float vector)
{
	//エフェクトハンドルの用意
	static ::EsHandle hSlash = 0;	//斬撃エフェクト


	//待機アニメーション時
	if (!m_AttackAnimEnd) 
	{
		m_AnimCnt++;

		//待機中の斬るアニメーションだった場合
		if (m_AnimNo == 3)
		{
			AnimChange(0);
		}

		if (m_AnimNo == 0)
		{
			m_AnimTime += m_pMesh->GetAnimSpeed();

			if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
			{
				AnimChange(2);
				m_AnimCnt = 0;
			}
		}

		if (m_AnimNo == 2)
		{
			//アニメーション終了までのカウント
			if (!m_AttackAnimEnd) { m_AnimCnt++; }

			m_EffCnt++;

			CEffect* Eff = CEffect::GetInstance();
			Eff->Speed(hSlash, 1.0f);
			Eff->Scale(hSlash, 0.6f, 0.6f, 0.6f);
			Eff->Rotate(hSlash, D3DXToRadian(-80.0f), 0.0f, 90.0f);

			if (m_EffCnt == 1) {
				//斬撃SEの再生
				CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Slash);
				CSoundManager::GetInstance()->Volume(CSoundManager::SE_Slash, 80);
				hSlash = CEffect::Play(CEffect::Kaito_Power, D3DXVECTOR3(m_vPosition.x - (-1.0f * vector), m_vPosition.y + 1.5f, m_vPosition.z));
			}

			if (m_pMesh->GetAnimPeriod(m_AnimNo) - 0.8f < m_AnimTime)
			{
				m_AnimSpeed = 0.0f;
			}
			else
			{
				//アニメーションの経過時間を加算
				m_AnimTime += m_pMesh->GetAnimSpeed();
			}

			if (m_AnimCnt > 90)
			{
				m_AnimCnt = 0;
				m_EffCnt = 0;
				m_AttackAnimEnd = true;
			}
		}
	}
}

//攻撃2アニメーション
void CKaito::MagicAttackAnim(float vector)
{
	//エフェクトハンドルの用意
	static ::EsHandle hMagicLight = 1;	//光魔法エフェクト

	//エフェクトの軸回転
	float EffRoteY;
	if (vector == 1.0f) { EffRoteY = 0.0f; }
	else { EffRoteY = -180.0f; }

	//どのアニメーションの後でも再生速度を変えない
	m_AnimSpeed = 0.01f;

	if (!m_AttackAnimEnd)
	{
		//待機中の斬るアニメーションだった場合
		if (m_AnimNo == 3)
		{
			AnimChange(0);
		}

		if (m_AnimNo == 0)
		{
			m_AnimTime += m_pMesh->GetAnimSpeed();

			if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
			{
				AnimChange(6);
				m_AnimCnt = 0;
			}
		}

		if (m_AnimNo == 6)
		{
			//アニメーション終了までのカウント
			if (!m_AttackAnimEnd) { m_AnimCnt++; }

			m_AnimTime += m_pMesh->GetAnimSpeed();

			if (m_pMesh->GetAnimPeriod(m_AnimNo) - 0.6f < m_AnimTime)
			{
				m_EffCnt++;

				CEffect* Eff = CEffect::GetInstance();
				Eff->Speed(hMagicLight, 1.0f);
				Eff->Scale(hMagicLight, 0.2f, 0.2f, 0.2f);
				Eff->Rotate(hMagicLight, 0.0f, D3DXToRadian(EffRoteY), 0.0f);

				if (m_EffCnt == 1) {
					//ダメージSEの再生
					CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Thunder);
					CSoundManager::GetInstance()->Volume(CSoundManager::SE_Thunder, 80);

					hMagicLight = CEffect::Play(CEffect::Kaito_Magic, D3DXVECTOR3(m_vPosition.x - (-2.0f * vector), m_vPosition.y + 1.8f, m_vPosition.z + (0.2f * vector)));
				}

				m_AnimSpeed = 0.0f;
			}
		}

		if (m_EffCnt >= 120)
		{
			m_AttackAnimEnd = true;
			m_EffCnt = 0;
		}
	}
}

//ダメージ中アニメーション
void CKaito::DamageAnim(float vector)
{
	//どのアニメーションの後でも再生速度を変えない
	m_AnimSpeed = 0.01f;

	//このアニメーションで使用しているアニメーションでない場合
	bool NotUseAnim = m_AnimNo != 0 && m_AnimNo != 7 && m_AnimNo != 1;

	//待機アニメーション時
	if (NotUseAnim && !m_AnimChange) {
		AnimChange(0);
	}

	if (m_AnimNo == 0 && !m_AnimChange)
	{
		//ダメージSEの再生
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Damage);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Damage, 80);

		AnimChange(7);
	}

	if (m_AnimNo == 7)
	{

		//アニメーションの経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//位置を後ろ向きに下げる
		m_MoveX += (0.08f * vector);
		//アニメーションカウントの初期化
		m_AnimCnt = 0;

		if (m_pMesh->GetAnimPeriod(m_AnimNo)- 0.2 < m_AnimTime)
		{
			AnimChange(1);
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
		//戻ってからアニメーション終了までに間を置く
		if (!m_DamageAnimEnd) 
		{
			m_AnimCnt++;
		}
		//アニメーションの経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (m_AnimCnt >= 120) 
		{
			m_DamageAnimEnd = true;
			m_AnimChange = false;
			m_AnimCnt = 0;
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


