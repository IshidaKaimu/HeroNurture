#include "CFastBoss.h"
#include "CEffect.h"
#include "CSceneManager.h"

CFastBoss::CFastBoss()
	: m_BonePos()
	, m_AnimChange()
	, m_EffPosZ(1.0f)
{
	SetScale(0.5f, 0.5f, 0.5f);
	SetPosition(0.0f, 40.0f, 8.0f);
}

CFastBoss::~CFastBoss()
{
}

void CFastBoss::Update()
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

void CFastBoss::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw(View, Proj, Light, Camera);
}

void CFastBoss::AnimChange()
{
	m_AnimChange = true;
}

void CFastBoss::ApeAnim()
{
	if (m_AnimNo == 0)
	{
		m_AnimSpeed = 0.01;

		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();
	}

	if (m_AnimNo == 1)
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

	if (m_vPosition.y >= 0.0f)
	{
		m_EffCnt++;

		//エフェクトごとに必要なハンドル
		//※3つ表示して制御するなら3つ必要になる
		static ::EsHandle hEffect = 1;
		CEffect* Eff = CEffect::GetInstance();
		Eff->Scale(hEffect, 1.0f, 1.0f, 1.0f);
		Eff->Speed(hEffect, 1.0f);
		if (m_EffCnt >= 1) {
			hEffect = CEffect::Play(CEffect::Dark, D3DXVECTOR3(m_vPosition.x, m_vPosition.y, m_vPosition.z));
		}

	}

	if (m_vPosition.y >= 0.0f)
	{
		m_vPosition.y -= FASTBOSS_SPEED;
	}

}

void CFastBoss::EvoAnim()
{
	SetPosition(0.0f, 0.0f, 8.0f);
}


