#pragma once
#pragma once
#include "CSkinMeshObject.h"

constexpr float WOOO_SPEED = 0.05f;

/*****************************************
*woooクラス
**/
class CWooo
	:public CSkinMeshObject
{
public:
	CWooo();
	virtual ~CWooo() override;


	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	bool SceneChange();

	void AnimChange();

	void SpAnim();

	void SpInit();

protected:
	D3DXVECTOR3    m_BonePos;			//カイト:ボーン座標
	bool           m_Run;				//走り出すフラグ
	bool           m_AnimChange;		//アニメーション切り替えフラグ
	float          m_EffPosZ;			//エフェクトのZ軸位置
};

