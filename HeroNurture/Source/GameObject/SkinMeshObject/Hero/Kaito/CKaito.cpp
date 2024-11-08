#include "CKaito.h"
#include "Effect/CEffect.h"
#include "Sound/CSoundManager.h"

CKaito::CKaito()
	: m_BonePos		()
	, m_Run			()
	, m_AnimChange	()
	, m_EffPosZ		(1.0f)
	, m_EffCnt		()
	, m_MagicCnt	()
	, m_SlashCnt	()
	, m_RootCnt		()
	, m_White		()
	, m_Magic		()
	, m_Setup		()
	, m_Slash		()
	, m_Root		()
{
}

CKaito::~CKaito()
{
}

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

void CKaito::Draw( LIGHT& Light )
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw( Light );
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

//オープニングでの位置の初期化
void CKaito::OpInit()
{
	SetPosition(0.0f, 0.0f, 8.0f);
	SetScale(0.5f, 0.5f, 0.5f);
}

void CKaito::OPAnim()
{
	if (m_AnimNo == 0)
	{
		m_AnimSpeed = 0.01;

		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//登場アニメーションの終了時間を超えた?
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_Run = true;
			m_AnimNo = 1;	  //移動アニメーションへ
			m_AnimTime = 0.0; //アニメーション経過時間初期化
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}

	}
   if(m_AnimNo == 1)
	{
	   if (m_AnimChange == true)
	   {
		   m_Run = false;
		   m_AnimNo = 2;	  //移動アニメーションへ
		   m_AnimTime = 0.0f; //アニメーション経過時間初期化
		   m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		   //斬撃SE
		   CSoundManager::PlaySE(CSoundManager::SE_Slash);
		   CSoundManager::Volume(CSoundManager::SE_Slash, 300);

	   }
	}

	if (m_AnimNo == 2)
	{
		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		//アニメーション経過時間を加算
		if (0.3 < m_AnimTime)
		{
			m_SlashCnt++;

			m_AnimSpeed = 0.0f;
			//エフェクトごとに必要なハンドル
			//※3つ表示して制御するなら3つ必要になる
			static ::EsHandle hEffect = -1;
			CEffect* Eff = CEffect::GetInstance();
			Eff->Scale(hEffect, 1.0f, 1.0f, 1.0f);
			Eff->Rotate(hEffect, 0.0f, 0.0f, D3DXToRadian(90));
			Eff->Speed(hEffect, 0.5);
			m_EffPosZ += 0.08f;
			hEffect = CEffect::Play(CEffect::Sword, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 3.0f, m_vPosition.z - m_EffPosZ));


		}
	}

	if (m_Run == true)
	{
		m_vPosition.z -= KAITO_SPEED;
	}

}

void CKaito::SpAnim()
{

	//エフェクトハンドルの用意
	static ::EsHandle hEffect = -1;	//パワーアップ
	static ::EsHandle hEffect2 = 1; //風魔法ぽいの
	static ::EsHandle hEffect3 = 2; //斬撃
	static ::EsHandle hEffect4 = 3; //軌道


	//アニメーション番号0 1
	if (m_AnimNo == 0 && !m_White)
	{
		m_AnimSpeed = 0.01;

		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//登場アニメーションの終了時間を超えた?
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			AnimNoChange(4);
		}
	}

	//アニメーション番号0 2
	if (m_AnimNo == 0 && m_White)
	{
		m_AnimSpeed = 0.01;

		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//登場アニメーションの終了時間を超えた?
		if (m_Run == true)
		{
			AnimNoChange(1);
		}
	}

	if (m_AnimNo == 1)
	{
		m_AnimSpeed = 0.01;

		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

	}

	if(m_AnimNo == 4 && m_White == false)
	{
		m_AnimSpeed = 0.01;
		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (0.3 < m_AnimTime)
		{
			m_EffCnt++;
			m_AnimSpeed = 0.0f;
			if (m_EffCnt > 1)
			{
				//パワーアップエフェクト
				CEffect* Eff = CEffect::GetInstance();
				Eff->Scale(hEffect,4.0f, 4.0f, 4.0f);
				if (m_EffCnt == 3) {
					hEffect = CEffect::Play(CEffect::Power, D3DXVECTOR3(m_vPosition.x, m_vPosition.y, m_vPosition.z));
					CSoundManager::PlaySE(CSoundManager::SE_Sp);
					CSoundManager::Volume(CSoundManager::SE_Sp, 300);
				}
				if (m_EffCnt > 60)
				{
					m_White = true;
					m_EffCnt = 0;
				}
			}
		}

	}

	if (m_AnimNo == 3 && m_Slash == false)
	{
		m_AnimSpeed = 0.001;
		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();
		if ((0.001 < m_AnimTime))
		{
			m_AnimSpeed = 0.0f;
			m_Setup = true;
		}
	}

	if (m_AnimNo == 3 && m_Slash == true)
	{
		m_AnimSpeed = 0.01;
		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();

		m_SlashCnt++;
		if (m_SlashCnt > 1) {
			CEffect* Eff = CEffect::GetInstance();
			Eff->Scale(hEffect3,7.0, 7.0f, 7.0f);
			Eff->Rotate(hEffect3, 0.0, 0.0, D3DXToRadian(120));
			if (m_SlashCnt == 2) {
				hEffect3 = CEffect::Play(CEffect::BigSlash, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 3.0f, m_vPosition.z - 4.5));
				//軌道用SE
				CSoundManager::PlaySE(CSoundManager::SE_Slash);
				//音量
				CSoundManager::Volume(CSoundManager::SE_Slash, 300);

			}
		}

		if (0.3 < m_AnimTime)
		{
			m_AnimSpeed = 0.0f;
		}
	}

	//移動処理
	if (m_Run == true)
	{
		m_vPosition.z -= KAITO_SPEED * 5;
	}

	//魔法
	if (m_Magic == true)
	{
		m_MagicCnt++;
		if ( m_MagicCnt >= 1) 
		{
			CEffect* Eff = CEffect::GetInstance();
			Eff->Speed(hEffect2, 1.0f);
			Eff->Scale(hEffect2, 1.0f, 1.0f, 1.0f);
			Eff->Rotate(hEffect2, 1.0f, D3DXToRadian(30), 1.0f);
			if (m_MagicCnt == 2) {
				hEffect2 = CEffect::Play(CEffect::Magic, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 2.0f, m_vPosition.z));
				//軌道用SE
				CSoundManager::PlaySE(CSoundManager::SE_Charge);
				//音量
				CSoundManager::Volume(CSoundManager::SE_Charge, 300);

			}
		}
	}
	else
	{
		CEffect::GetInstance()->Stop(hEffect2);
	}

	//軌道表示
	if (m_Root == true)
	{
		m_RootCnt++;
		if (m_RootCnt >= 1)
		{
			CEffect* Eff = CEffect::GetInstance();
			Eff->Speed(hEffect4, 0.8f);
			Eff->Scale(hEffect4, 1.0f, 1.0f, 1.0f);
			Eff->Rotate(hEffect4, 0.0f, D3DXToRadian(90), 0.0f);
			if (m_RootCnt == 2) {
				hEffect4 = CEffect::Play(CEffect::Root, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 2.0f, m_vPosition.z + 5.0f));
				//軌道用SE
				CSoundManager::PlaySE(CSoundManager::SE_Root);
				//音量
				CSoundManager::Volume(CSoundManager::SE_Root, 300);

			}
		}
	}
	else
	{
		CEffect::GetInstance()->Stop(hEffect4);
	}

}

//必殺技シーンでの位置の初期化
void CKaito::SpInit()
{
	SetPosition(0.0f, 0.0f, 0.0f);
	SetScale(0.5f, 0.5f, 0.5f);
	m_AnimNo = 0;
}

//白フェード開始
bool CKaito::WhiteStart()
{
	if (m_White == true)
	{
		return true;
	}
	return false;
}

void CKaito::Run(bool run)
{
	m_Run = run;
}

void CKaito::Wait()
{
	AnimNoChange(0);
}

//アニメーション変更関数
void CKaito::AnimNoChange(int no)
{
	m_AnimNo = no;	  //移動アニメーションへ
	m_AnimTime = 0.0; //アニメーション経過時間初期化
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

}

//アニメーションが終わったら
bool CKaito::EndAnim(int no)
{
	if (m_pMesh->GetAnimPeriod(no) < m_AnimTime)
	{
		return true;
	}
	return false;
}

//構え完了したら
bool CKaito::Setup()
{
	if (m_Setup == true)
	{
		return true;
	}
	return false;
}

//魔法陣召喚
void CKaito::Magic(bool magic)
{
	m_Magic = magic;
}


void CKaito::Slash()
{
	m_Slash = true;
}

void CKaito::Root()
{
	m_Root = true;
}

