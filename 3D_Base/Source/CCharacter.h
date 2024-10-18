#pragma once

#include "CStaticMeshObject.h"

/**************************************************
*	キャラクタークラス.
**/
class CCharacter
	: public CStaticMeshObject
{
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	//弾を飛ばしたいか確認.
	bool IsShot() const { return m_Shot; }

	//Y軸方向へ伸ばしたレイを取得
	RAY GetRayY() const { return *m_pRayY; }

protected:
	bool	m_Shot;	 //弾を飛ばすフラグ.

	RAY*	m_pRayY; //Y方向へ飛ばしたレイ
};

