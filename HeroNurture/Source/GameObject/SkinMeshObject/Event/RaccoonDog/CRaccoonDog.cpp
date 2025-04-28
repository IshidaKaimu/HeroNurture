#include "CRaccoonDog.h"
using namespace Constant_RaccoonDog;

CRaccoonDog::CRaccoonDog()
{
}

CRaccoonDog::~CRaccoonDog()
{
}

void CRaccoonDog::Initialize()
{
	m_AnimNo = 1;
	m_AnimSpeed = 0.85f;
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

	//初期設定
	SetPosition(INIT_POS);    //座標
	SetScale(INIT_SCALE);     //拡縮
	SetRotation(INIT_ROTATE); //回転

	m_MoveZ = INIT_POS.z;
}

void CRaccoonDog::AppearanceAnim(float camz)
{
	//アニメーションの経過時間を加算		
	m_AnimTime += m_pMesh->GetAnimSpeed();
	//カメラと同じz軸になるまで
	if (m_vPosition.z >= camz) 
	{
		//z軸を加算
		m_MoveZ -= MOVE_SPEED;
	}

	//座標の更新
	SetPositionZ(m_MoveZ);
}


void CRaccoonDog::Draw()
{
	//アニメーションスピードの設定
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	//描画
	CSkinMeshObject::Draw();
}
