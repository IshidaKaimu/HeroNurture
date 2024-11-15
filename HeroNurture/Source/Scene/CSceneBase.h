#pragma once
#include <Windows.h>
#include "Sprite3D/CSprite3D.h"
#include "Sprite2D/CSprite2D.h"
#include "UIObject/CUIObject.h"

//==============================//
//		�V�[���x�[�X�N���X		//
//==============================//

class CSceneBase
{
public:
	//�t�F�[�h�̍ő厞��
	static constexpr int	FADE_TIME = FPS;	//��1�b��
	static constexpr bool	DEBUG_FLG = false;	//�f�o�b�O�t���O
public:
	CSceneBase();
	virtual ~CSceneBase();

	//�������֐�
	virtual void Initialize();

	//�X�V�֐�
	virtual void Update() {};

	//�`��֐�
	virtual void Draw();

	//�\�z�֐�
	virtual void Create() {};

	//�f�[�^�ǂݍ��݊֐�
	virtual void  LoadData() {};

	//�V�[���ǂݍ��݊֐�
	virtual void LoadScene(){};

	//�j���֐�
	virtual void Releace();


protected:
    //�t�F�[�h�A�E�g
    bool FadeOut();
    //�t�F�[�h�C��
    bool FadeIn();

protected:
	//���C�g���
	LIGHT       m_Light;

	//�V�[���J�ڗp
	bool        m_IsScene;  
    //�V�[���J�ڃt���O
    bool        m_SceneTransitionFlg;
    //�I�𒆔ԍ�
    int         m_SelectNo;

	float       m_AnimCnt;				//�A�j���[�V�����J�E���g

    //UI
    CUIObject* m_pLogo;         //���S
    CUIObject* m_pBlueFrame;    //�I�𒆐g

private:
	//�t�F�[�h	
    static constexpr float FADESPEED = 0.05f;	//�t�F�[�h�X�s�[�h
	CUIObject*	m_pFade;
	int			m_FadeTime;		        //�V�[���؂�ւ��p�̃^�C�}�[	
	float		m_FadeAlpha;	        //�A���t�@�l	
    bool        m_FadeOutFlg;           //�t�F�[�h�A�E�g�t���O(�t�F�[�h�A�E�g���Ƀt�F�[�h�C�������Ȃ�����)

};

