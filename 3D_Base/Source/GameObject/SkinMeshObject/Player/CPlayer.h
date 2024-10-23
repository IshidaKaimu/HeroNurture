#pragma once
#include "SkinMeshObject/CSkinMeshObject.h"

/**************************************************
*	プレイヤークラス.
**/
class CPlayer
	: public CSkinMeshObject
{
public :
	//パラメータ構造体
	struct enParamater
	{
		//ちから
		int Power;
		//魔力
		int Magic;
		//素早さ
		int Speed;
		//体力
		int HP;
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
	//プレイヤーのパラメータ構造体
	enParamater m_Paramater;

};