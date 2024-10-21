#pragma once
#include "SkinMeshObject/CSkinMeshObject.h"

/*****************************************
* ザコクラス
**/
class CZako
	:public CSkinMeshObject
{
public:
	CZako();
	virtual ~CZako() override;


	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	void SetAnimSpeed( double speed ){ m_AnimSpeed = speed; }

protected:
	int            m_AnimNo;			//ザコ:アニメーション番号
	double         m_AnimTime;			//ザコ:アニメーション経過時間
	double         m_AnimSpeed;			//アニメーション速度
	D3DXVECTOR3    m_BonePos;			//ザコ:ボーン座標

};

