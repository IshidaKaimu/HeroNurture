#pragma once
#include "CSceneBase.h"
#include "CBeEvoBoss.h"
#include "CCamera.h"
#include "CBoss.h"
#include "CSky.h"
#include "WriteText.h"

class CBossEvolution
	:public CSceneBase
{
public:
	//��ʍ\����
	enum enCut 
	{
		ZoomOut,
		Change,
		Evolution
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
	CBossEvolution();
	~CBossEvolution();

	void Create() override;
	void LoadData() override;

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	void PlayWhiteFade();

private:
	//�ϐg�OBoss
	CBeEvoBoss* m_pBeEvoBoss;
	//�ϐg��Boss
	CBoss*     m_pBoss;
	//���t�F�[�h
	CUIObject* m_pWhiteFade;	
	//�X�J�C�{�b�N�X
	CSky*      m_pSky;
	//���
	enCut      m_Cut;

	//�J�������[�N
	enCamera   m_CameraWork;

	//�J����Z�l�ϓ��p
	float     m_CameraPosZ;

	//�J����Y�l�ϓ��p
	float     m_CameraPosY;

	//���t�F�[�h�̃t�F�[�h�l
	float	  m_Alpha;
	//���l�����؂�ւ��t���O
	bool      m_AlphaChange;
	//���t�F�[�h�I���t���O
	bool      m_EndChange;

	//�V�[���؂�ւ��t���O
	bool      m_CameraChange;
};

