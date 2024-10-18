#pragma once
#include "CSceneBase.h"
#include "CBeEvoBoss.h"
#include "CCamera.h"
#include "CBoss.h"
#include "CSky.h"
#include "CCamera.h"
#include "WriteText.h"

//ボス死亡シーンクラス
class CBossDeath
	:public CSceneBase
{
public:
	//場面構造体
	enum enCut
	{
		KnockBack,
		ZoomUp,
		FallingDown,
		Falled
	};

	//カメラワーク構造体
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

	//白フェード
	void PlayWhiteFade(int max, float speed, float alpha);

private:
	//Boss
	CBoss* m_pBoss;

	//白フェード
	CUIObject* m_pWhiteFade;

	//スカイボックス
	CSky* m_pSky;

	//カメラクラス
	CCamera* m_pCamera;

	//場面
	enCut      m_Cut;

	//カメラワーク
	enCamera   m_CameraWork;

	//カメラZ値変動用
	float     m_CameraPosZ;

	//カメラY値変動用
	float     m_CameraPosY;

	//カメラX値変動用
	float    m_CameraPosX;

	//フェード点滅回数用カウント
	int       m_FlashCnt;

	//白フェードのフェード値
	float	  m_Alpha;
	//α値増減切り替えフラグ
	bool      m_AlphaChange;
	//白フェード終了フラグ
	bool      m_EndChange;

	//シーン切り替えフラグ
	bool      m_CameraChange;
};

