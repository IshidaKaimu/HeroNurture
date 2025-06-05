#pragma once
#include <Windows.h>
#include "UIObject\CUIObject.h"
#include "SpriteObject\CSpriteObject.h"
#include "Effect\CEffect.h"
#include <memory>

//=====================================
// �O���錾
//=====================================
//----�}�l�[�W���[�N���X----
class CSprite3DManager;
class CStaticMeshManager;
class CUIManager;
class CEffect;
class WriteText;
//--------------------------

//----�I�u�W�F�N�g�N���X----
class CSky;
//--------------------------

//=====================================
// �萔�錾
//=====================================
//���C�g���
const D3DXVECTOR3 LIGHT_POS = { 0.0f, 1.0f, 0.0f };
const D3DXVECTOR3 LIGHT_DIR = { 0.0f, 1.0f, 0.0f };

//----UI----
//���
//��
const D3DXVECTOR3 ARROW_LEFT_POS_NS    = { 300.0f, 490.0f, 0.0f };        //�琬�q�[���[�I�������W
const D3DXVECTOR3 ARROW_LEFT_POS_BS    = { 200.0f, 490.0f, 0.0f };        //���W
const D3DXVECTOR3 ARROW_LEFT_ROTATE = { 0.0f, 0.0f, D3DXToRadian(180.0f)};//��]
//�E
const D3DXVECTOR3 ARROW_RIGHT_POS_NS = { 1000.0f, 400.0f, 0.0f };//�琬�q�[���[�I�������W
const D3DXVECTOR3 ARROW_RIGHT_POS_BS = { 1100.0f, 400.0f, 0.0f };//�o�g���q�[���[�I�������W
//��󋤒�
const D3DXVECTOR3 ARROW_SCALE = { 1.0f, 1.0f, 1.0f };//�g�k
const D3DXVECTOR2 ARROW_DISP  = { 1.0f, 1.0f };		 //��
constexpr float   ARROW_ALPHA = 1.0f;			     //���l
//������@�w���o�[
const D3DXVECTOR3 CONTROLBAR_POS   = { 0.0f, 690.0f, 0.0f }; //���W
const D3DXVECTOR3 CONTROLBAR_SCALE = { 1.0f, 1.0f, 1.0f };   //�g�k
const D3DXVECTOR2 CONTROLBAR_DISP  = { 1.0f, 0.6f };		 //��
constexpr float   CONTROLBAR_ALPHA = 1.0f;					 //���l
//�uEnter ����v�e�L�X�g
const D3DXVECTOR2 ENTERTEXT_POS  = { 970.0f, 675.0f }; //���W
//�uEsc �߂�v�e�L�X�g
const D3DXVECTOR2 ESCAPETEXT_POS = { 1150.0f, 675.0f }; //���W
//-------

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
	//�ėp�w�i�̕`��
	void DrawBasicBackGround();
	//������@�w���o�[�e���v���[�g�̕`��
	void DrawControlBar( bool basictext);
	//��̕`��
	void DrawSky();
public:
	//���t�F�[�h�֘A�̏�����
	void InitWhiteFade();
	//���t�F�[�h
	void PlayWhiteFade(int max, float speed, float alpha);
	//���t�F�[�h�����̎擾
	bool GetWhiteFadeNow() { return m_WhiteFadeNow; }

protected:
	//���C�g���
	LIGHT       m_Light;

	//----�J�������ړ�������l----
	D3DXVECTOR3 m_MoveCamPos; //���W
	D3DXVECTOR3 m_MoveCamLook;//�����_
	//----------------------------

	//----�f�o�b�O�p���----
	//�I�u�W�F�N�g�ʒu
	D3DXVECTOR3 m_DebugPos;
	//�I�u�W�F�N�g��]
	D3DXVECTOR3 m_DebugRotate;
	//UI�ʒu
	D3DXVECTOR2 m_DebugUiPos;
	//�J�����ʒu
	D3DXVECTOR3 m_DebugCamPos;
	//�J���������_
	D3DXVECTOR3	m_DebugCamLook;
	//-----------------------

	//----�t���O----
	//�V�[���J�ڗp
	bool        m_IsScene;  
    //�V�[���J�ڃt���O
    bool        m_SceneTransitionFlg;
	//--------------

	//----�C�x���g�V�[��----
	//�C�x���g���A�j���[�V�����̃J�b�g�ԍ�
	int m_Scene;
	//�A�j���[�V�����J�E���g
	float       m_AnimCnt;
	//----------------------

	//�I�𒆔ԍ�
	int         m_SelectNo;

private:
	//----�t�F�[�h----
	//�V�[���J��	
	std::unique_ptr<CUIObject> m_pFade;         //�t�F�[�h�p�摜
	int			m_FadeTime;		                //�V�[���؂�ւ��p�̃^�C�}�[	
	float		m_FadeAlpha;	                //�A���t�@�l	
    bool        m_FadeOutFlg;                   //�t�F�[�h�A�E�g�t���O(�t�F�[�h�A�E�g���Ƀt�F�[�h�C�������Ȃ�����)
	//���t�F�[�h
	std::unique_ptr<CUIObject> m_pWhiteFade;	//���t�F�[�h�p�摜
	int			m_WhiteFadeTime;		        //�V�[���؂�ւ��p�̃^�C�}�[	
	bool		m_AlphaChange;					//�t�F�[�h�񐔐���p�t���O
	int         m_WhiteFadeCnt;					//�t�F�[�h�񐔂̃J�E���g
	float       m_WhiteFadeAlpha;				//�t�F�[�h�摜�̃��l
	bool        m_WhiteFadeNow;				    //���t�F�[�h���ł��邩
	//----------------

	//----UI-----
	std::unique_ptr<CUIObject> m_pBasicBackGround; 	//�ėp�w�i
	std::unique_ptr <CUIObject> m_pControlBar;      //������@�w���o�[�摜
	//-----------

	//----�X�^�e�B�b�N���b�V��----
	std::unique_ptr<CSky> m_pSky; //��
	//----------------------------
};

