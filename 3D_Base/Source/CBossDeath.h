#pragma once
#include "CSceneBase.h"
#include "CBeEvoBoss.h"
#include "CCamera.h"
#include "CBoss.h"
#include "CSky.h"
#include "CCamera.h"
#include "WriteText.h"

//�{�X���S�V�[���N���X
class CBossDeath
	:public CSceneBase
{
public:
	//��ʍ\����
	enum enCut
	{
		KnockBack,
		ZoomUp,
		FallingDown,
		Falled
	};

	//�J�������[�N�\����
	enum enCamera
	{
		Fast,
		Second,
		Third,
		Force,
		Fifth,
	};

public:
	CBossDeath();
	~CBossDeath();

	void Create() override;
	void LoadData() override;

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	//���t�F�[�h
	void PlayWhiteFade(int max, float speed, float alpha);

private:
	//Boss
	CBoss* m_pBoss;

	//���t�F�[�h
	CUIObject* m_pWhiteFade;

	//�X�J�C�{�b�N�X
	CSky* m_pSky;

	//�J�����N���X
	CCamera* m_pCamera;

	//���
	enCut      m_Cut;

	//�J�������[�N
	enCamera   m_CameraWork;

	//�J����Z�l�ϓ��p
	float     m_CameraPosZ;

	//�J����Y�l�ϓ��p
	float     m_CameraPosY;

	//�J����X�l�ϓ��p
	float    m_CameraPosX;

	//�t�F�[�h�_�ŉ񐔗p�J�E���g
	int       m_FlashCnt;

	//���t�F�[�h�̃t�F�[�h�l
	float	  m_Alpha;
	//���l�����؂�ւ��t���O
	bool      m_AlphaChange;
	//���t�F�[�h�I���t���O
	bool      m_EndChange;

	//�V�[���؂�ւ��t���O
	bool      m_CameraChange;
};

