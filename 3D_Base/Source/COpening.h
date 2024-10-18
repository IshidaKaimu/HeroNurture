#pragma once
#include "CSceneBase.h"
#include "CKaito.h"
#include "CCamera.h"
#include "CSky.h"

//�I�[�v�j���O�V�[���N���X
class COpening
	:public CSceneBase
{
public:
    //��ʍ\����
	enum enCut 
	{
		Back,
		Left,
		Right,
		Center,
		CenterBack,
		Slash
	};
public:

	COpening();
	~COpening();

	void Create() override;
	void LoadData() override;

	void Init();

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;


private:
	//�J�C�g�N���X
	CKaito*  m_pKaito;

	//�J�����N���X
	CCamera* m_pCamera;

	//�X�J�C�{�b�N�X
	CSky*    m_pSky;

	//�����_Y
	float m_LookPointY;

	//�J�����ʒuZ��
	float m_CameraPosZ;

	//���
	enCut m_Cut;

};

