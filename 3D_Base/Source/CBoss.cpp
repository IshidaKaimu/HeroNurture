#include "CBoss.h"
#include "CEffect.h"
#include "CSoundManager.h"

CBoss::CBoss()
	: m_BonePos    ()
	, m_AnimChange ()
	, m_EffPosZ    (1.0f)
	, m_EffCnt     ()
	, m_DeathCnt   ()
	, m_EffStart   ()
	, m_BossRadianX()
	, m_RotateCnt  ()
	, m_Fell	   ()
	, m_FellCnt	   ()
{
}

CBoss::~CBoss()
{
}

void CBoss::Update()
{

	//--------------------------
	//スキンメッシュ
	//--------------------------

	//Boss
	//アニメーション番号メモ
	//0:待機
	//1:?
	//2:ダメージ
	//3:大ダメージ

}

void CBoss::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw(View, Proj, Light, Camera);
}

void CBoss::AnimChange()
{
	m_AnimChange = true;
}

void CBoss::EvoAnim()
{
	if (m_AnimNo == 0)
	{
		m_AnimSpeed = 0.01f;
		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (m_AnimChange == true)
		{
			m_AnimNo = 2;	  //移動アニメーションへ
			m_AnimTime = 0.0; //アニメーション経過時間初期化
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}
	}

	if (m_AnimNo == 2)
	{
		
		m_AnimSpeed = 0.01f;
		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();
		


		if (m_AnimTime >= 0.41f)
		{
			m_EffStart = true;
			m_AnimSpeed = 0.0f;
		}


		if (m_EffStart == true)
		{
			m_EffCnt++;
		}

		if (m_EffCnt == 1) 
		{
			//エフェクトごとに必要なハンドル
			//※3つ表示して制御するなら3つ必要になる
			static ::EsHandle hEffect = 1;
			CEffect* Eff = CEffect::GetInstance();
			Eff->Scale(hEffect, 3.0f, 3.0f, 3.0f);
			Eff->Speed(hEffect, 0.01f);
			hEffect = CEffect::Play(CEffect::Howling, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 6.0f, m_vPosition.z - 5.0f));
			//咆哮SE
			CSoundManager::PlaySE(CSoundManager::SE_BossVo);
			CSoundManager::Volume(CSoundManager::SE_BossVo, 300);

		}
	}


}

bool CBoss::SceneChange()
{
	if (m_EffCnt >= 115)
	{
		return true;
	}
	return false;
}

//進化シーンでの初期化
void CBoss::EvoInit()
{
	SetPosition(0.0f, 0.0f, 0.0f);
	SetScale(0.5f, 0.5f, 0.5f);

}

//必殺技シーンでの初期化
void CBoss::SpInit()
{
	SetPosition(0.0f, 0.0f, -15.0f);
	SetScale(0.5f, 0.5f, 0.5f);
	SetRotation(0.0f, D3DXToRadian(180), 0.0f);

}

//死亡シーンでの初期化
void CBoss::DeathInit()
{
	SetPosition(0.0f, 0.0f, 0.0f);
	SetScale(0.5f, 0.5f, 0.5f);
	AnimNoChange(3);
}

//必殺技シーンでのアニメーション
void CBoss::SpAnim()
{
	//エフェクトハンドルの用意
	static ::EsHandle hEffect = -1;	//爆発エフェクト

	if (m_AnimNo == 0)
	{
		m_AnimSpeed = 0.01;

		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		//登場アニメーションの終了時間を超えた?
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_AnimNo = 0;	  //移動アニメーションへ
			m_AnimTime = 0.0; //アニメーション経過時間初期化
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}

	}

	if (m_Death == true)
	{
		m_DeathCnt++;
		if (m_DeathCnt >= 1)
		{
			CEffect* Eff = CEffect::GetInstance();
			Eff->Speed(hEffect, 1.0f);
			Eff->Scale(hEffect, 1.0f, 1.0f, 1.0f);
			Eff->Rotate(hEffect, D3DXToRadian(40), 0.0, 0.0f);

			if (m_DeathCnt == 110)
			{
				hEffect = CEffect::Play(CEffect::BossDeath, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 4.0f, m_vPosition.z - 7.0));
				//ボス爆発前SE
				CSoundManager::PlaySE(CSoundManager::SE_BeforeDeath);
				//音量
				CSoundManager::Volume(CSoundManager::SE_BeforeDeath, 300);

			}
			if (m_DeathCnt == 320)
			{
				CSoundManager::Stop(CSoundManager::SE_BeforeDeath);

				//爆発SE
				CSoundManager::PlaySE(CSoundManager::SE_BossDeath);
				//音量
				CSoundManager::Volume(CSoundManager::SE_BossDeath, 300);
			}
		}
	}

	if (m_AnimNo == 2)
	{
		m_AnimSpeed = 0.01;

		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		

		if (0.3 < m_AnimTime)
		{
			m_AnimSpeed = 0.0f;
		}

	}

}

//ボス撃破アニメーション
void CBoss::DeathAnim()
{
	//エフェクトハンドルの用意
	static ::EsHandle hEffect = -1;	//消滅エフェクト


	//ダメージモーション
	if (m_AnimNo == 3)
	{
		//途中からアニメーション速度をゆっくりにする
		if (m_AnimTime <= 0.2) 
		{
			m_AnimSpeed = 0.007;
		}
		else 
		{
			m_AnimSpeed = 0.0015;
		}

		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		//アニメーションの経過時間が一定時間を超えたら傾け始める
		if (m_AnimTime > 0.4) 
		{
			if (m_BossRadianX >= -10) {
				m_RotateCnt++;
			    m_BossRadianX -= 0.5;
			}
		}

		//ボスの回転の設定
		SetRotation(D3DXToRadian(m_BossRadianX), 0.0f, 0.0f);

		//アニメーションを終わる直前で止める
		if ((m_pMesh->GetAnimPeriod(m_AnimNo) - 0.05) < m_AnimTime)
		{
			m_AnimSpeed = 0.0f;

			//倒れ切ったフラグを立てる
			m_Fell = true;
		}
	}
	
	//倒れ切ったら
	if (m_Fell == true)
	{

		m_FellCnt++;
		if(m_FellCnt >= 45)
		{
			CEffect* Eff = CEffect::GetInstance();
			Eff->Speed(hEffect, 1.0f);
			Eff->Scale(hEffect, 3.0f,3.0f, 3.0f);
			if (m_FellCnt == 46)
			{
				hEffect = CEffect::Play(CEffect::Extinction, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 3.0f, m_vPosition.z));
				//消滅時
				CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_BossDeath);
				//消滅時音量
				CSoundManager::GetInstance()->Volume(CSoundManager::SE_BossDeath, 300);

			}
		}
	}

}

//爆発エフェクト再生
void CBoss::Death()
{
	m_Death = true;
}

bool CBoss::AfterDeath()
{
	if (m_DeathCnt > 420) {
		return true;
	}
	return false;
}

//アニメーション変更関数
void CBoss::AnimNoChange(int no)
{
	m_AnimNo = no;	  //移動アニメーションへ
	m_AnimTime = 0.0; //アニメーション経過時間初期化
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

}

//倒れ切っていれば
bool CBoss::BossFell()
{
	if (m_Fell == true)
	{
		return true;
	}
	return false;
}

