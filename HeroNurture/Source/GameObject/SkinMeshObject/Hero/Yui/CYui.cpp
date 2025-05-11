#include "CYui.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Scene\CSceneManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"

//定数の名前空間
using namespace Constant_Yui;

CYui::CYui()
	: m_AnimChange  ()
	, m_MoveRotateY (0.0f)
	, m_RotateSpeedY(1.0f)
	, m_DamageSECnt ()
{
	SetScale(0.1f, 0.1f, 0.1f);
}

CYui::~CYui()
{
}

//初期化関数
void CYui::Initialize()
{
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	//アニメーションの初期化
	AnimInit();

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
	SetScale(BATTLE_SCALE);
	//回転の設定
	SetRotation(BATTLE_ROTATE);

	//アニメーションの軸ごとの回転値の初期化
	m_MoveRotateY = 0.0f; //Y軸
	m_MoveRotateZ = 0.0f; //Z軸

	//回転スピードの初期化
	m_RotateSpeedY = 1.0f;

	//アニメーション終了フラグの初期化
	m_AttackAnimEnd = false;
	//ダメージアニメーション終了フラグの初期化
	m_DamageAnimEnd = false;
	//ダメージフラグの初期化
	m_Damage = false;
	//アニメーションカウントの初期化
	m_AnimCnt = 0;
	//アニメーション切り替えフラグの初期化
	m_AnimChange = false;

	//アニメーションの開始地点の固定
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;
}

//敵になった際の初期化関数
void CYui::EnemyInitialize()
{
	//アニメーション関連の初期化
	AnimInit();

	//座標の設定
	SetPosition(ENEMYINIT_POS);
	//拡縮の設定
	SetScale(BATTLE_SCALE);
	//回転の設定
	SetRotation(ENEMY_ROTATE);
	
	//アニメーションの軸ごとの回転値の初期化
	m_MoveRotateY = 0.0f; //Y軸
	m_MoveRotateZ = 0.0f; //Z軸

	//回転スピードの初期化
	m_RotateSpeedY = 1.0f;

	//アニメーション終了フラグの初期化
	m_AttackAnimEnd = false;
	//ダメージアニメーション終了フラグの初期化
	m_DamageAnimEnd = false;
	//ダメージフラグの初期化
	m_Damage = false;
	//アニメーションカウントの初期化
	m_AnimCnt = 0;
	//エフェクトカウントの初期化
	m_EffCnt = 0;
	//アニメーション切り替えフラグの初期化
	m_AnimChange = false;

	//アニメーションの開始地点の固定
	m_MoveX = m_vPosition.x;
	m_MoveY = m_vPosition.y;
	m_MoveZ = m_vPosition.z;
}

//バトル開始時登場シーンでの初期化
void CYui::AppearanceInitialize()
{
	//座標の設定
	SetPosition(APPEALANCE_POS);
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
	//アニメーションスピードの設定
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	//描画
	CSkinMeshObject::Draw();
}

//デバッグ関数
void CYui::Debug()
{
#if DEBUG
	ImGui::Begin(JAPANESE("Yui"));
	ImGui::InputFloat3(JAPANESE("位置"),DebugPos);
	ImGui::InputFloat3(JAPANESE("拡縮"), DebugScale);
	ImGui::End();
	SetPosition(DebugPos);
	SetScale(DebugScale);
#endif

#if DEBUG
	ImGui::Begin(JAPANESE("Yui"));
	ImGui::Text(JAPANESE("位置x:%f"), m_vPosition.x);
	ImGui::Text(JAPANESE("位置y:%f"), m_vPosition.y);
	ImGui::Text(JAPANESE("位置z:%f"), m_vPosition.z);
	ImGui::End();
#endif

}

//育成ヒーロー選択シーンのアニメーション
void CYui::NatureHeroSelectAnimation()
{
}

//バトルヒーロー選択シーンのアニメーション
void CYui::BattleHeroSelectAnimation()
{
}

//登場シーンのアニメーション
void CYui::AppearanceAnimation()
{
	//アニメーションスピードの設定
	m_AnimSpeed = 0.01f;
	
	//アニメーションの経過時間を加算		
	m_AnimTime += m_pMesh->GetAnimSpeed();

	//アニメーション番号の設定	
	if (m_vPosition.z >= -13.0f) {
		//歩くアニメーションに
		if (m_AnimNo != 2)
		{
			AnimChange(2);
		}
		//カメラに向けて前進
		m_vPosition.z -= APPEALANCE_SPEED;
	}
	else
	{
		if (m_AnimNo == 2)
		{
			AnimChange(3);
		}
		m_AppealanceAnimEnd = true;
	}
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
	//アニメーション終了後に戻す初期位置
	D3DXVECTOR3 InitPos;
	
	//エフェクトハンドルの用意
	static ::EsHandle hTornado = 2;	//竜巻エフェクト

	//敵側か自分かで戻す初期位置を決める
	if (vector == 1.0f) { InitPos = BATTLEINIT_POS; }
	else { InitPos = ENEMYINIT_POS; }

	if (!m_AttackAnimEnd) 
	{
		m_AnimCnt++;

		//竜巻エフェクト
		CEffect* Eff = CEffect::GetInstance();
		Eff->Speed(hTornado, 1.0f);
		Eff->Scale(hTornado, 0.3f, 0.3f, 0.3f);
		Eff->Rotate(hTornado,0.0f, 0.0f, 0.0f);

		if (m_AnimCnt >= 60) {
			AnimChange(4);
		}

		if (m_AnimNo == 4)
		{
			m_EffCnt++;

			if (m_EffCnt == 1)
			{
				//T字SEの再生
				CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_TPose);
				CSoundManager::GetInstance()->Volume(CSoundManager::SE_TPose, 80);
			}

			if (m_EffCnt  == 60) 
			{
				//竜巻SEの再生
				CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Tornade);
				CSoundManager::GetInstance()->Volume(CSoundManager::SE_Tornade, 80);

				hTornado = CEffect::Play(CEffect::Yui_Power, D3DXVECTOR3(m_vPosition.x, m_vPosition.y, m_vPosition.z));
			}

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
			m_EffCnt = 0;
			m_AttackAnimEnd = true;
		}
	}

	if (!m_AttackAnimEnd) {
		SetPosition(m_MoveX, m_MoveY, m_MoveZ);
	}
	else
	{
		//位置を戻す
		SetPosition(InitPos);
		//変動していた値を戻す
		m_MoveX = InitPos.x; //X座標
		m_MoveY = InitPos.y; //Y座標
		m_MoveZ = InitPos.z; //Z座標
		//回転値を戻す
		SetRotation(BATTLE_ROTATE.x, BATTLE_ROTATE.y, BATTLE_ROTATE.z * vector);
		
		if (m_AnimNo == 4)
		{
			AnimChange(3);
		}
	}

}

//攻撃2
void CYui::MagicAttackAnim(float vector)
{
	//エフェクトハンドルの用意
	static ::EsHandle hFireBall = -1;	//火球エフェクト
	//エフェクトの軸回転
	float EffRoteZ;
	if (vector == 1) { EffRoteZ = -90.0f; }
	else { EffRoteZ = 90.0f; }

	//アニメーション終了後に戻す初期位置
	D3DXVECTOR3 InitPos;

	//敵側か自分かで戻す初期位置を決める
	if (vector == 1.0f) { InitPos = BATTLEINIT_POS; }
	else { InitPos = ENEMYINIT_POS; }

	//アニメーション終了までのカウント
	if (!m_AttackAnimEnd)
	{
		m_AnimCnt++;


		if (m_AnimNo == 3)
		{
			AnimChange(0);
		}

		if (m_AnimNo == 0)
		{
			//アニメーションの経過時間を加算		
			m_AnimTime += m_pMesh->GetAnimSpeed();

			if (m_MoveY <= 0.5f) {
				m_MoveY += 0.02f;
			}
			else
			{
				//アニメーション停止
				m_AnimSpeed = 0.0f;

				m_EffCnt++;

				CEffect* Eff = CEffect::GetInstance();
				Eff->Speed(hFireBall, 2.0f);
				Eff->Scale(hFireBall, 0.3f, 0.3f, 0.3f);
				Eff->Rotate(hFireBall, 0.0f, 0.0f, D3DXToRadian(EffRoteZ));

				if (m_EffCnt == 1)
				{
					//火球SEの再生
					CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_FireBall);
					CSoundManager::GetInstance()->Volume(CSoundManager::SE_FireBall, 100);

					hFireBall = CEffect::Play(CEffect::Yui_Magic, D3DXVECTOR3(m_vPosition.x - (5.0f * vector), m_vPosition.y + 0.4f, m_vPosition.z));
				}
			}
		}

		if (!m_AttackAnimEnd)
		{
			SetPosition(m_MoveX, m_MoveY, m_MoveZ);
		}

		//カウントが一定を超えたら
		if (m_AnimCnt >= 200)
		{
			//位置の修正
			SetPositionY(InitPos.y);
			//変動したY座標の初期化
			m_MoveY = InitPos.y;
			//アニメーション終了
			m_AttackAnimEnd = true;
			AnimChange(0);
			//アニメーションカウントの初期化
			m_AnimCnt = 0;
			//エフェクトカウントの初期化
			m_EffCnt = 0;
		}
	}
}

void CYui::DamageAnim(float vector)
{

	//どのアニメーションの後でも再生速度を変えない
	m_AnimSpeed = 0.01f;

	D3DXVECTOR3 InitRotate;

	if (vector != 1.0f) { InitRotate = BATTLE_ROTATE; }
	else { InitRotate = ENEMY_ROTATE; }

	//回転を合わせる
	SetRotation(InitRotate);

	//このアニメーションで使用しているアニメーションでない場合
	bool NotUseAnim = m_AnimNo != 0 && m_AnimNo != 1;

	m_DamageSECnt++;

	if (m_DamageSECnt == 1)
	{
		//ダメージSEの再生
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Damage);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Damage, 80);
	}
	//待機アニメーション時
	if (NotUseAnim && !m_AnimChange) {

		AnimChange(0);
	}

	if (m_AnimNo == 0 && !m_AnimChange)
	{
		//アニメーションの経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		//高さを固定する
		m_MoveY = 0.0f;

		if (m_pMesh->GetAnimPeriod(m_AnimNo) - 0.4 < m_AnimTime)
		{
			AnimChange(1);
		}
		else
		{
			//位置を後ろ向きに下げる
		    m_MoveX += (0.08f * vector);
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
			AnimChange(3);
		}
	}

	if (m_AnimNo == 3 && m_AnimChange)
	{
		//戻ってきてからアニメーション終了まで少し開ける
		m_AnimCnt++;
		//アニメーションの経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();
		if (m_AnimCnt >= 60) 
		{
			m_DamageAnimEnd = true;
			m_AnimChange = false;
			m_AnimCnt = 0;
			m_DamageSECnt = 0;
		}
	}

	SetPosition(m_MoveX, m_MoveY, m_MoveZ);

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


