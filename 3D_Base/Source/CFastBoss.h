#pragma once
#pragma once
#include "CSkinMeshObject.h"

constexpr float FASTBOSS_SPEED = 0.05f;

/*****************************************
* 登場ボスクラス
**/
class CFastBoss
	:public CSkinMeshObject
{
public:
	CFastBoss();
	virtual ~CFastBoss() override;


	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	void AnimChange();

	void ApeAnim();

	void EvoAnim();

protected:
	D3DXVECTOR3    m_BonePos;			//ボス:ボーン座標
	bool           m_AnimChange;		//アニメーション切り替えフラグ
	float          m_EffPosZ;			//エフェクトのZ軸位置
	int            m_EffCnt;			//エフェクトの時間
};

