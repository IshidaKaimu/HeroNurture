#include "CWooo.h"
#include "CEffect.h"

CWooo::CWooo()
	: m_BonePos()
	, m_Run()
	, m_AnimChange()
	, m_EffPosZ(1.0f)
{
	SetScale(2.0f, 2.0f, 2.0f);
}

CWooo::~CWooo()
{
}

void CWooo::Update()
{

	//--------------------------
	//スキンメッシュ
	//--------------------------

	//Wooo
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

void CWooo::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw(View, Proj, Light, Camera);
}

bool CWooo::SceneChange()
{
	if (m_EffPosZ >= 10.0f)
	{
		return true;
	}
	return false;
}

void CWooo::AnimChange()
{
	m_AnimChange = true;
}


void CWooo::SpAnim()
{
	if (m_AnimNo == 0)
	{
		m_AnimSpeed = 0.0003;

		//アニメーション経過時間を加算
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//登場アニメーションの終了時間を超えた?
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_Run = true;
			m_AnimNo = 3;	  //移動アニメーションへ
			m_AnimTime = 0.0; //アニメーション経過時間初期化
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}
	}

}

//必殺技シーンでの位置の初期化
void CWooo::SpInit()
{
	SetPosition(0.0f, 0.0f, 0.0f);
}


