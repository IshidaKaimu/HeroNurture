#pragma once

#include "CGameObject.h"

#include "Sprite3D/CSprite3D.h"

/************************************************************
*	スプライトオブジェクトクラス.
**/
class CSpriteObject
	: public CGameObject
{
public:
	CSpriteObject();
	virtual ~CSpriteObject() override;

	//CGameObjectで純粋仮想関数の宣言がされてるのでこちらで定義を書く.
	virtual void Update() override;
	//CSpriteObjectで宣言した関数で、以降はこれをoverrideさせる.
	virtual void Draw( );

	//スプライトを接続する.
	void AttachSprite( CSprite3D& pSprite ){
		m_pSprite = &pSprite;
	}
	//スプライトを切り離す.
	void DetachSprite(){
		m_pSprite = nullptr;
	}

protected:

protected:
	CSprite3D*	m_pSprite;

};
