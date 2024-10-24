#pragma once
#include "Scene/CSceneBase.h"
#include "SkinMeshObject/Kaito/CKaito.h"
#include "Camera/CCamera.h"
#include "StaticMeshObject/Sky/CSky.h"
#include "WriteText/WriteText.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "json.hpp"
#include "SkinMeshObject/Player/CPlayer.h"
#include "Scene/GameMain/CGameMain.h"

using namespace nlohmann;

//シーン選択シーン
class CTitle
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
	CTitle();
	~CTitle();


	//構築関数
	void Create() override;

	void Releace() override;

	//データ設定関数
	void LoadData() override;
	//破棄関数
	//更新関数
	void Update() override;
	//描画関数
	void Draw() override;
	//文字の動き
	float Easing(float x);

	//アカウント名入力処理
	void  InputName();

private:
	//スカイボックス
	CSky* m_pSky;

	//地面
	CGround* m_pGround;

	//ゲームメイン
	CGameMain* m_pGameMain;

	//ユーザー名入力
	std::wstring m_UserName;

	//プレイヤー
	CPlayer* m_pPlayer;

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

