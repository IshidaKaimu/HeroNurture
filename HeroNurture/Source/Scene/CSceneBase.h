#pragma once
#include <Windows.h>
#include "Sprite3D\CSprite3D.h"
#include "Sprite2D\CSprite2D.h"
#include "UIObject\CUIObject.h"
#include <memory>

//=====================================
//�V�[�����N���X
//����ҁF�Γc�D��
//=====================================
class CSceneBase
{
	//�t�F�[�h�̍ő厞��
	static constexpr int	FADE_TIME = FPS;	//��1�b��
	static constexpr bool	DEBUG_FLG = false;	//�f�o�b�O�t���O
	static constexpr float  FADESPEED = 0.05f;	//�t�F�[�h�X�s�[�h

public:
	CSceneBase();
	virtual ~CSceneBase();

	//�������֐�
	virtual void Initialize();

	//�X�V�֐�
	virtual void Update();

	//�`��֐�
	virtual void Draw();

	//�\�z�֐�
	virtual void Create() {};

	//�f�[�^�ǂݍ��݊֐�
	virtual void  LoadData() {};

	//�j���֐�
	virtual void Releace();

protected:
    //�t�F�[�h�A�E�g
    bool FadeOut();
    //�t�F�[�h�C��
    bool FadeIn();
public:
	//���t�F�[�h�֘A�̏�����
	void InitWhiteFade();
	//���t�F�[�h
	void PlayWhiteFade(int max, float speed, float alpha);


protected:
	//���C�g���
	LIGHT       m_Light;

	//----�f�o�b�O�p�J�������----
	//�ʒu
	D3DXVECTOR3 m_CamPos;
	//�����_
	D3DXVECTOR3	m_CamLook;

	//----�t���O----
	//�V�[���J�ڗp
	bool        m_IsScene;  
    //�V�[���J�ڃt���O
    bool        m_SceneTransitionFlg;
	//���t�F�[�h�t���O
	bool        m_WhiteFlag;

	//�I�𒆔ԍ�
    int         m_SelectNo;

	//�A�j���[�V�����J�E���g
	float       m_AnimCnt;		
private:
	//----�t�F�[�h----
	//�V�[���J��	
	std::unique_ptr<CUIObject> m_pFade;        //�t�F�[�h�pUI
	int			m_FadeTime;		                //�V�[���؂�ւ��p�̃^�C�}�[	
	float		m_FadeAlpha;	                //�A���t�@�l	
    bool        m_FadeOutFlg;                   //�t�F�[�h�A�E�g�t���O(�t�F�[�h�A�E�g���Ƀt�F�[�h�C�������Ȃ�����)
	//���t�F�[�h
	std::unique_ptr<CUIObject> m_pWhiteFade;	//���t�F�[�h�pUI
	int			m_WhiteFadeTime;		        //�V�[���؂�ւ��p�̃^�C�}�[	
	bool		m_AlphaChange;					//�t�F�[�h�񐔐���p�t���O
	int         m_WhiteFadeCnt;					//�t�F�[�h�񐔂̃J�E���g
	float       m_WhiteFadeAlpha;				//�t�F�[�h�摜�̃��l
};

