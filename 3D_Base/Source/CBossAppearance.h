#pragma once
#include "CSceneBase.h"
#include "CFastBoss.h"
#include "CSky.h"
#include "WriteText.h"


class CBossAppearance
	:public CSceneBase
{
public:
	enum enCut
	{
		Ape,
		Left,
		Right,
		Center,
		Zoom,
		SceneChange
	};

public:
	CBossAppearance();
	~CBossAppearance();


	void Create() override;
	void LoadData() override;
	void Init();

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

private:
	//�{�X�N���X
	CFastBoss* m_pFastBoss;

	//�X�J�C�{�b�N�X�N���X
	CSky*	   m_pSky;

	float m_CameraPosZ;

	float m_CameraLookY;

	enCut m_Cut;

};
