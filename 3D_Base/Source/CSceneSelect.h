#pragma once
#include "CSceneBase.h"
#include "CKaito.h"
#include "CCamera.h"
#include "CSky.h"
#include "WriteText.h"



//シーン選択シーン
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
	//スカイボックス
	CSky* m_pSky;
	//オープニングに移らせるフラグ
	bool m_Opening;
	//ボス出現シーンに移らせるフラグ
	bool m_BossApp;
	//ボス進化シーンに移らせるフラグ
	bool m_BossEvo;
	//必殺技シーンに移らせるフラグ
	bool m_Special;
	//ボス撃破シーンに移らせるフラグ
	bool m_BossDeath;

	//時間経過でかわるX
	float m_Time;
};

