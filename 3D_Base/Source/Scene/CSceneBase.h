#pragma once
#include <Windows.h>
#include "Sprite3D/CSprite3D.h"
#include "Sprite2D/CSprite2D.h"
#include "UIObject/CUIObject.h"

//CPU�񋓌^
enum class enCPUList
{
    Kicker = 0, //�L�b�J�[
    Keeper,     //�L�[�p�[
    none = -1,
};

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

	//����������

	virtual void Initialize();

	virtual void Update() {};
	virtual void Draw();

	virtual void Create() {};

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
	//�J�������.
	CAMERA		m_Camera;	
	//���C�g���
	LIGHT       m_Light;
	//�s��.
	D3DXMATRIX	m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX	m_mProj;	//�ˉe�i�v���W�F�N�V�����j�s��.



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

