#include "CYui.h"
#include "Effect/CEffect.h"
#include "Sound/CSoundManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"

CYui::CYui()
	: m_BonePos()
	, m_Run()
	, m_AnimChange()
	, m_EffPosZ(1.0f)
{
}

CYui::~CYui()
{
}

//初期化関数
void CYui::Initialize()
{
}

//データ読み込み関数
void CYui::LoadData()
{
	//メッシュデータの読み込み
	AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
}

//更新関数
void CYui::Update()
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
void CYui::Draw(LIGHT& Light)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw(Light);
}

//アニメーション関数
void CYui::Animation()
{
	if (GetAsyncKeyState('N') & 0x8000)
	{
		m_AnimNo = 2;	//登場アニメーションへ
		m_AnimTime = 0; //アニメーション経過時間初期化
		//登場アニメーション
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
	}

}

void CYui::AnimChange()
{
	m_AnimChange = true;
}



