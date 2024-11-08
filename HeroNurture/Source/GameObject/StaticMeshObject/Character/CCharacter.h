#pragma once
#include "StaticMeshObject/CStaticMeshObject.h"

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
	virtual void Draw( LIGHT& Light ) override;

	//Y軸方向へ伸ばしたレイを取得
	RAY GetRayY() const { return *m_pRayY; }

protected:
	RAY*	m_pRayY; //Y方向へ飛ばしたレイ

};

