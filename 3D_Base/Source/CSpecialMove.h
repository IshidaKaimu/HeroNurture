#pragma once
#include "CSceneBase.h"
#include "CCamera.h"
#include "CBoss.h"
#include "CKaito.h"
#include "CSky.h"
#include "WriteText.h"

class CSpecialMove
	:public CSceneBase
{
public:
	//��ʍ\����
	enum enSpCut
	{
		KaitoUp,
		Fade,
		Fast,
		Second,
		Third,
		fource,
	};

public:
	CSpecialMove();
	~CSpecialMove();

	void Create() override;
	void LoadData() override;

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	void PlayWhiteFade();


private:

	//�J�C�g
	CKaito* m_pKaito;

	//�ϐg��Boss
	CBoss* m_pBoss;


	//���t�F�[�h
	CUIObject* m_pWhiteFade;

	//���
	enSpCut      m_Cut;

	//�X�J�C�{�b�N�X
	CSky*       m_pSky;

	//��
	CSky*       m_pBlack;

	//�J����Z�l�ϓ��p
	float     m_CameraPosZ;

	//�J����Y�l�ϓ��p
	float     m_CameraPosY;

	//�J����X�l�ϓ��p
	float    m_CameraPosX;

	//�J���������_Y�ϓ��p
	float   m_CameraLookY;

	//���t�F�[�h�̃t�F�[�h�l
	float	  m_Alpha;

	//���l�����؂�ւ��t���O
	bool      m_AlphaChange;

	//���t�F�[�h�I���t���O
	bool      m_EndChange;

	//�V�[���؂�ւ��t���O
	bool      m_CameraChange;

};

