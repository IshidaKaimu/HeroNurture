#pragma once
#include "Scene/CSceneBase.h"
#include "SkinMeshObject/Kaito/CKaito.h"
#include "Camera/CCamera.h"
#include "StaticMeshObject/Sky/CSky.h"
#include "WriteText/WriteText.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "json.hpp"


using namespace nlohmann;

//シーン選択シーン
class CSceneSelect
	:public CSceneBase
{
public:
	//シーン列挙型
	enum enSelectScene
	{
		Opening,
		BossApp,
	};

public:
	CSceneSelect();
	~CSceneSelect();


	//構築関数
	void Create() override;
	//データ設定関数
	void LoadData() override;
	//破棄関数
	void Releace() override;
	//更新関数
	void Update() override;
	//描画関数
	void Draw() override;
	//文字の動き
	float Easing(float x);

private:
	//スカイボックス
	CSky* m_pSky;

	//地面
	CGround* m_pGround;

	//行格納用
	std::vector<std::wstring> m_Lines;
	std::wstring m_Line;

	//文字列格納用
	std::vector<std::wstring> m_Statuses;


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

