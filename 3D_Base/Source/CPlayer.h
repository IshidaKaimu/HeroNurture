#pragma once

#include "CCharacter.h"

/**************************************************
*	プレイヤークラス.
**/
class CPlayer
	: public CCharacter
{
public :
	//パラメータ列挙型
	enum enParamater
	{
		Power,
		Magic,
		Speed,
		HP,
		max,
	};

public:
	CPlayer();
	virtual ~CPlayer() override;

	//データ設定関数
	void SetData();


	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera ) override;


	

protected:

};