#pragma once
#include "CSceneBase.h"
#include "CKaito.h"
#include "CCamera.h"
#include "CSky.h"
#include "WriteText.h"



//�V�[���I���V�[��
class CSceneSelect
	:public CSceneBase
{
public:
	enum enSelectScene
	{
		Opening,
		BossApp,
	};

public:
	CSceneSelect();
	~CSceneSelect();


	void Create() override;

	void LoadData() override;

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	float Easing(float x);

private:
	//�X�J�C�{�b�N�X
	CSky* m_pSky;
	//�I�[�v�j���O�Ɉڂ点��t���O
	bool m_Opening;
	//�{�X�o���V�[���Ɉڂ点��t���O
	bool m_BossApp;
	//�{�X�i���V�[���Ɉڂ点��t���O
	bool m_BossEvo;
	//�K�E�Z�V�[���Ɉڂ点��t���O
	bool m_Special;
	//�{�X���j�V�[���Ɉڂ点��t���O
	bool m_BossDeath;

	//���Ԍo�߂ł����X
	float m_Time;
};

