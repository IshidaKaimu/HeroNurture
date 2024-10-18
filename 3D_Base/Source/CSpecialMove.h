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
	//場面構造体
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

	//カイト
	CKaito* m_pKaito;

	//変身後Boss
	CBoss* m_pBoss;


	//白フェード
	CUIObject* m_pWhiteFade;

	//場面
	enSpCut      m_Cut;

	//スカイボックス
	CSky*       m_pSky;

	//黒
	CSky*       m_pBlack;

	//カメラZ値変動用
	float     m_CameraPosZ;

	//カメラY値変動用
	float     m_CameraPosY;

	//カメラX値変動用
	float    m_CameraPosX;

	//カメラ注視点Y変動用
	float   m_CameraLookY;

	//白フェードのフェード値
	float	  m_Alpha;

	//α値増減切り替えフラグ
	bool      m_AlphaChange;

	//白フェード終了フラグ
	bool      m_EndChange;

	//シーン切り替えフラグ
	bool      m_CameraChange;

};

