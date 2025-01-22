#pragma once
#include "Scene\CSceneBase.h"					//シーンベースクラス
#include "Camera\CameraManager\CCameraManager.h"//カメラマネージャクラス
#include "StaticMeshObject\Sky\CSky.h"			//スカイボックスクラス
#include "WriteText\WriteText.h"				//テキスト描画クラス
#include "StaticMeshObject\Ground\CGround.h"	//地面クラス
#include "SkinMeshObject\Hero\Yui\CYui.h"       //ユイクラス
#include "SkinMeshObject\Hero\Kaito\CKaito.h"   //カイトクラス
#include <memory>
#include <Windows.h>

// =======================
// 前方宣言
// =======================		
class CJson;
class CUtility;
class CUIManager;
class CHeroManager;
class CSoundManager;
class CSceneManager;

// =======================
// 定数宣言
// =======================
//共通の初期位置
const D3DXVECTOR3 TITLE_POS = { 0.0f, 0.0f, 1.0f };
//ユイの初期設定
const D3DXVECTOR3 TITLE_YUI_SCALE = { 0.04f, 0.04f, 0.04f }; //拡縮
//カイトの初期設定
const D3DXVECTOR3 TITLE_KAITO_SCALE = { 0.3f, 0.3f, 0.3f };  //拡縮

//=====================================
// タイトルシーンクラス
//=====================================
class CTitleScene
	:public CSceneBase
{
public:
	CTitleScene();
	~CTitleScene();


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

private:

	//文字の動き
	float Easing(float x);
	//アカウント名入力処理
	void  InputName();	
	//UIの描画
	void DrawUI();

	//wstringからstringへの変換
	std::string WstringToString(std::wstring owstring);

private:

	//カメラクラス
	CCameraManager* m_pCamera;

	// =======================
	// オブジェクトクラス
	// =======================		
	//----スタティックメッシュ----
	//空
	std::unique_ptr<CSky> m_pSky;	
	//地面
	std::unique_ptr<CGround> m_pGround;

	//----スキンメッシュ----
	//ユイ
	std::unique_ptr<CYui> m_pYui;
	//カイト
	std::unique_ptr<CKaito> m_pKaito;

	//----UI----
	//タイトル背景
	std::unique_ptr<CUIObject> m_pTitleBack;
	//タイトル指示テキスト背景
	std::unique_ptr<CUIObject> m_pTitleInfoBack;

	//ユーザー名入力
	std::wstring m_UserName;

	//Jsonクラス
	std::unique_ptr<CJson> m_pJson;


	//表示ヒーロー
	int m_HeroNo;

};

