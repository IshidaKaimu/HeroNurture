#pragma once
#include "CSceneBase.h"
#include "CKaito.h"
#include "CCamera.h"
#include "CSky.h"

//オープニングシーンクラス
class COpening
	:public CSceneBase
{
public:
    //場面構造体
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
	//カイトクラス
	CKaito*  m_pKaito;

	//カメラクラス
	CCamera* m_pCamera;

	//スカイボックス
	CSky*    m_pSky;

	//注視点Y
	float m_LookPointY;

	//カメラ位置Z軸
	float m_CameraPosZ;

	//場面
	enCut m_Cut;

};

