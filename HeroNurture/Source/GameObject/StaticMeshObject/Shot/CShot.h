#pragma once
#include "StaticMeshObject/CStaticMeshObject.h"

/**************************************************
*	弾クラス.
**/
class CShot
	: public CStaticMeshObject
{
public:
	CShot();
	virtual ~CShot() override;

	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera ) override;

	//弾の再設定.
	void Reload( const D3DXVECTOR3& Pos,float RotY);

	void SetDisplay( bool disp ) { m_Display = disp; }

	void SetPlayerRotateY(float RotY) { m_MoveDirection.y = RotY; }

protected:
	bool	m_Display;	//表示切替.
	//移動方向
	D3DXVECTOR3 m_MoveDirection;
	
	float		m_MoveSpeed;//移動速度
	int m_DisplayTime;	    //表示する時間
};
