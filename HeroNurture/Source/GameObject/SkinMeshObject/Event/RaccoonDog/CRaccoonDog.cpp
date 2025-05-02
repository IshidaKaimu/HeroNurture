#include "CRaccoonDog.h"
#include "Effect\CEffect.h"

using namespace Constant_RaccoonDog;

CRaccoonDog::CRaccoonDog()
	: m_ReachCamFlag()
	, m_HiddenFlag  ()
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

	m_MoveY = INIT_POS.y;
	m_MoveZ = INIT_POS.z;
}

void CRaccoonDog::AppearanceAnim(float camz)
{
	//エフェクトハンドルの用意
	static ::EsHandle hSteam = -1;	//煙エフェクト
	//煙エフェクト
	CEffect* Eff = CEffect::GetInstance();
	Eff->Speed(hSteam, 1.0f);
	Eff->Scale(hSteam, 0.1f, 0.1f, 0.1f);
	Eff->Rotate(hSteam, 0.0f, 0.0f, 0.0f);

	//アニメーションの経過時間を加算		
	m_AnimTime += m_pMesh->GetAnimSpeed();

	//上下の動き
	UpDown();

	//カメラと同じz軸になるまで
	if (m_vPosition.z >= camz) 
	{
		//z軸を加算
		m_MoveZ -= MOVE_SPEED;
	}
	else
	{
		m_ReachCamFlag = true;
	}

	//タヌキがカメラに到達したら
	if (m_ReachCamFlag)
	{
		SetRotation(UPRIGHT_ROTATE);
		m_AnimNo = 0;
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		m_AnimCnt++;

		if (m_AnimCnt == STEAM_TIME)
		{
			//煙エフェクトの再生
			hSteam = Eff->Play(CEffect::enList::Steam, D3DXVECTOR3(m_vPosition.x,m_vPosition.y,m_vPosition.z - STEAM_DELAY));
		}
	}

	//カメラに到達してから数秒後
	if (m_AnimCnt > HIDDEN_TIME)
	{
		//非表示にする
		m_HiddenFlag = true;
	}

	//座標の更新
	SetPositionY(m_MoveY);
	SetPositionZ(m_MoveZ);
}


void CRaccoonDog::Draw()
{
	//アニメーションスピードの設定
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	//描画
	if (!m_HiddenFlag)
	{
		CSkinMeshObject::Draw();
	}
}

//上下の動き
void CRaccoonDog::UpDown()
{
	//カメラに到達するまでの間
	if (!m_ReachCamFlag) 
	{
		//一定の高さまで上昇
		if (m_MoveY < MAX_UP && !m_Up)
		{
			m_MoveY += UP_SPEED;
		}
		else
		{
			//上がり切ったらフラグを立てる
			m_Up = true;
		}

		//フラグが上がっている間下降
		if (m_Up)
		{
			m_MoveY -= UP_SPEED;
			if (m_MoveY <= INIT_POS.y)
			{
				m_Up = false;
			}
		}
	}
	else
	{
		//カメラに到達したら高さを固定
		m_MoveY = INIT_POS.y;
	}
}
