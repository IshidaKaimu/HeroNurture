#pragma once
#include "CGameObject.h"
#include "Sprite2D\CSprite2D.h"
#include "Global\Global.h"

/************************************************************
*	UI�I�u�W�F�N�g�N���X.
**/
class CUIObject
	: public CGameObject
{
public:
	CUIObject();
	virtual ~CUIObject() override;

	//CGameObject�ŏ������z�֐��̐錾������Ă�̂ł�����Œ�`������.
	virtual void Update() override;
	//CUIObject�Ő錾�����Ŋ֐��ŁA�ȍ~�͂����override������.
	virtual void Draw();

	//�X�v���C�g��ڑ�����.
	void AttachSprite( CSprite2D& pSprite ){
		m_pSprite = &pSprite;
	}
	//�X�v���C�g��؂藣��.
	void DetachSprite(){
		m_pSprite = nullptr;
	}
	//�p�^�[���ԍ���ݒ�.
	void SetPatternNo( SHORT x, SHORT y ){
		m_PatternNo.x = x;
		m_PatternNo.y = y;
	}

	//UI�̕��A������ݒ�
	void SetDisplay(float w, float h)
	{
		m_DisplaySize.x = w;
		m_DisplaySize.y = h;
	}
	//UI�̕���ݒ�
	void SetWidth(float w)
	{
		m_DisplaySize.x = w;
	}
	//UI�̍�����ݒ�
	void SetHeight(float h)
	{
		m_DisplaySize.y = h;
	}

	//�f�B�X�v���C�T�C�Y�擾
	D3DXVECTOR2 GetDisplay()
	{
		return m_DisplaySize;
	}

	//�A���t�@�l��ݒ肷��
	void SetAlpha(float value) { m_pSprite->SetAlpha(value); }

protected:
	CSprite2D*	m_pSprite;		//�X�v���C�g2D�N���X
	POINTS		m_PatternNo;	//�p�^�[���ԍ�(�}�X��).
	D3DXVECTOR2 m_DisplaySize;	//UI�̕��A����
};
