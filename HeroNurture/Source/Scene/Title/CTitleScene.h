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
namespace Constant_TitleScene
{
	//カメラ
	const D3DXVECTOR3 CAM_POS		  = { 1.0f, 5.0f, -7.0f }; //座標
	const D3DXVECTOR3 CAM_LOOK		  = { 2.0f, 5.0f, 0.0f };  //注視点
	//ユイの初期設定				   
	const D3DXVECTOR3 YUI_POS		  = { 0.0f, 0.0f, 0.0f };    //座標
	const D3DXVECTOR3 YUI_ROT		  = { 0.0f, -0.5f, 0.0f };   //回転
	const D3DXVECTOR3 YUI_SCALE		  = { 0.04f, 0.04f, 0.04f }; //拡縮
	//カイトの初期設定				  
	const D3DXVECTOR3 KAITO_POS		  = { -1.0f, 0.3f, 2.0f }; //座標
	const D3DXVECTOR3 KAITO_ROT		  = { 0.0f, -0.5f, 0.0f }; //回転
	const D3DXVECTOR3 KAITO_SCALE	  = { 0.3f, 0.3f, 0.3f };  //拡縮
	//タイトルテキストの位置		   
	const D3DXVECTOR2 TITLE_POS		  = { 30.0f, -50.0f };
	//選択肢テキストの基準値
	const D3DXVECTOR2 SELECT_POS	  = { 900.0f, 400.0f };
	//選択肢テキスト同士の間隔
	constexpr float   SELECT_INTERVAL = 80.0f;
}

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
	//デバッグ用関数
	void Debug();

private:
	//アカウント名入力処理
	void  InputName();	
	//UIの描画
	void DrawUI();

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
	D3DXVECTOR3 m_YuiPos;
	D3DXVECTOR3 m_YuiRot;
	//カイト
	std::unique_ptr<CKaito> m_pKaito;
	D3DXVECTOR3 m_KaitoPos;
	D3DXVECTOR3 m_KaitoRot;


	//----UI----
	//タイトル背景
	std::unique_ptr<CUIObject> m_pTitleBack;
		

	//表示ヒーロー
	int m_HeroNo;

};

