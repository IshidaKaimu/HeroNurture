#pragma once
#include "Scene\CSceneBase.h"					//シーンベースクラス
#include "Camera\CameraManager\CCameraManager.h"//カメラマネージャクラス
#include "StaticMeshObject\Sky\CSky.h"			//スカイボックスクラス
#include "WriteText\WriteText.h"				//テキスト描画クラス
#include "StaticMeshObject\Ground\CGround.h"	//地面クラス
#include "SkinMeshObject\Hero\CHeroManager.h"		//プレイヤークラス
#include <memory>
#include <Windows.h>

//jsonクラス
class CJson;

//シーン選択シーン
class CTitle
	:public CSceneBase
{
public:
	CTitle();
	~CTitle();


	//構築関数
	void Create()	  override;
	//破棄関数
	void Releace()	  override;
	//データ設定関数
	void LoadData()	  override;
	//初期化関数
	void Initialize() override;
	//更新関数
	void Update()     override;
	//描画関数
	void Draw()		  override;

public:

	//文字の動き
	float Easing(float x);

	//アカウント名入力処理
	void  InputName();

	//wstringからstringへの変換
	std::string WstringToString(std::wstring owstring);

private:

	//カメラクラス
	CCameraManager* m_pCamera;

	//スカイボックス
	CSky* m_pSky;

	//地面
	CGround* m_pGround;

	//ユーザー名入力
	std::wstring m_UserName;

	//Jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//プレイヤー
	std::unique_ptr<CHeroManager> m_pHero;

	//----フラグ----
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

