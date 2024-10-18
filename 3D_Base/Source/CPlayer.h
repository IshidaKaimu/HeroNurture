#pragma once

#include "CCharacter.h"

/**************************************************
*	プレイヤークラス.
**/
class CPlayer
	: public CCharacter
{
public :
	//移動状態列挙型
	enum enMoveState
	{
		Stop = 0,	//停止
		ForWard,	//前進
		BackWard,	//後退
		TurnLeft,	//左回転
		TurnRight	//右回転
	};

public:
	CPlayer();
	virtual ~CPlayer() override;

	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera ) override;

	//ラジコン操作
	void RadioControl();

protected:
	//回転速度
	float m_TurnSpeed;	//回転速度
	float m_MoveSpeed;	//移動速度
	enMoveState m_MoveState;
};