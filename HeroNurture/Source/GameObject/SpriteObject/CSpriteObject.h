#pragma once

#include "CGameObject.h"

#include "Sprite3D/CSprite3D.h"

/************************************************************
*	�X�v���C�g�I�u�W�F�N�g�N���X.
**/
class CSpriteObject
	: public CGameObject
{
public:
	CSpriteObject();
	virtual ~CSpriteObject() override;

	//CGameObject�ŏ������z�֐��̐錾������Ă�̂ł�����Œ�`������.
	virtual void Update() override;
	//CSpriteObject�Ő錾�����֐��ŁA�ȍ~�͂����override������.
	virtual void Draw( );

	//�X�v���C�g��ڑ�����.
	void AttachSprite( CSprite3D& pSprite ){
		m_pSprite = &pSprite;
	}
	//�X�v���C�g��؂藣��.
	void DetachSprite(){
		m_pSprite = nullptr;
	}

protected:

protected:
	CSprite3D*	m_pSprite;

};
