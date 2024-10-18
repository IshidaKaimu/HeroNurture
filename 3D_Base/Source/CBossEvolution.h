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
	//場面構造体
	enum enCut 
	{
		ZoomOut,
		Change,
		Evolution
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
	CBossEvolution();
	~CBossEvolution();

	void Create() override;
	void LoadData() override;

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	void PlayWhiteFade();

private:
	//変身前Boss
	CBeEvoBoss* m_pBeEvoBoss;
	//変身後Boss
	CBoss*     m_pBoss;
	//白フェード
	CUIObject* m_pWhiteFade;	
	//スカイボックス
	CSky*      m_pSky;
	//場面
	enCut      m_Cut;

	//カメラワーク
	enCamera   m_CameraWork;

	//カメラZ値変動用
	float     m_CameraPosZ;

	//カメラY値変動用
	float     m_CameraPosY;

	//白フェードのフェード値
	float	  m_Alpha;
	//α値増減切り替えフラグ
	bool      m_AlphaChange;
	//白フェード終了フラグ
	bool      m_EndChange;

	//シーン切り替えフラグ
	bool      m_CameraChange;
};

