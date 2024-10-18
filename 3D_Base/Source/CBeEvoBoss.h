#pragma once
#include "CSkinMeshObject.h"

constexpr float BEEVOBOSS_SPEED = 0.05f;

/*****************************************
* 進化前ボスクラス
**/
class CBeEvoBoss
	:public CSkinMeshObject
{
public:
	CBeEvoBoss();
	virtual ~CBeEvoBoss() override;


	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	void EvoAnim();

	void EffStart();

protected:
	D3DXVECTOR3    m_BonePos;			//ボス:ボーン座標
	bool           m_AnimChange;		//アニメーション切り替えフラグ
	float          m_EffPosZ;			//エフェクトのZ軸位置
	float          m_EffScaX;			//エフェクトスケールX
	float          m_EffScaY;			//エフェクトスケールY
	float          m_EffScaZ;			//エフェクトスケールZ
	int            m_EffCnt;			//エフェクトの時間;
	bool           m_EffStart;			//エフェクト発動
	

};
