#include "CBeEvoBoss.h"
#include "CEffect.h"
#include "CSceneManager.h"
#include "CSoundManager.h"

CBeEvoBoss::CBeEvoBoss()
	: m_BonePos()
	, m_AnimChange()
	, m_EffPosZ(1.0f)
	, m_EffScaX()
	, m_EffScaY()
	, m_EffScaZ()
	, m_EffCnt()
	, m_EffStart()
{
	SetScale(0.5f, 0.5f, 0.5f);
	SetPosition(0.0f, 0.0f, 0.0f);
	m_AnimNo = 4;
}

CBeEvoBoss::~CBeEvoBoss()
{
}

void CBeEvoBoss::Update()
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

void CBeEvoBoss::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw(View, Proj, Light, Camera);
}

void CBeEvoBoss::EvoAnim()
{
	if (m_AnimNo == 4)
	{
		m_AnimSpeed = 0.01;

		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();


	}

	
	if (m_EffStart == true) 
	{

		m_EffCnt++;

		if (m_EffCnt >= 60)
		{
			static ::EsHandle hEffect3 = 1;
			CEffect* Eff = CEffect::GetInstance();
			Eff->Scale(hEffect3, 3.5f, 3.5f,3.5f);
			Eff->Rotate(hEffect3, 0.0f, 0.0f, 0.0);
			Eff->Speed(hEffect3, 0.5);
			if (m_EffCnt == 65) 
			{
				hEffect3 = CEffect::Play(CEffect::Aura, D3DXVECTOR3(m_vPosition.x , m_vPosition.y, m_vPosition.z));
			}
		}


	}
}

void CBeEvoBoss::EffStart()
{
	m_EffStart = true;
}




