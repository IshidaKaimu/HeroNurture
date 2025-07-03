#pragma once
#include "Scene\CSceneBase.h"					
#include "Camera\CameraManager\CCameraManager.h"
#include "StaticMeshObject\Sky\CSky.h"			
#include "WriteText\WriteText.h"				
#include "StaticMeshObject\Ground\CGround.h"	
#include "SkinMeshObject\Hero\Yui\CYui.h"       
#include "SkinMeshObject\Hero\Kaito\CKaito.h"   
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
//========================

// =======================
// 定数宣言
// =======================
namespace Constant_TitleScene
{
	//----カメラ----
	const D3DXVECTOR3 CAM_POS		  = { 1.0f, 5.0f, -7.0f }; //座標
	const D3DXVECTOR3 CAM_LOOK		  = { 2.0f, 5.0f, 0.0f };  //注視点
	//--------------
	
	//----スキンメッシュオブジェクト---- 
	//ユイ				   
	const D3DXVECTOR3 YUI_POS		  = { 0.0f, 0.0f, 0.0f };    //座標
	const D3DXVECTOR3 YUI_ROT		  = { 0.0f, -0.5f, 0.0f };   //回転
	const D3DXVECTOR3 YUI_SCALE		  = { 0.04f, 0.04f, 0.04f }; //拡縮
	//カイト				  
	const D3DXVECTOR3 KAITO_POS		  = { -1.0f, 0.3f, 2.0f }; //座標
	const D3DXVECTOR3 KAITO_ROT		  = { 0.0f, -0.5f, 0.0f }; //回転
	const D3DXVECTOR3 KAITO_SCALE	  = { 0.3f, 0.3f, 0.3f };  //拡縮
	//-----------------------------------
	
	//----UI---- 
	//タイトルテキスト		   
	const D3DXVECTOR2 TITLE_POS = { 30.0f, -50.0f }; //座標

	//選択肢テキスト
	const D3DXVECTOR2 SELECT_POS	  = { 900.0f, 400.0f }; //基準値
	constexpr float   SELECT_INTERVAL = 80.0f;				//間隔	

	//選択矢印
	const D3DXVECTOR3 SELECTARROW_POS   = { 810.0f, 425.0f, 0.0f }; //座標
	const D3DXVECTOR3 SELECTARROW_SCALE = { 0.7f, 0.7f, 0.7f };		//拡縮
	const D3DXVECTOR2 SELECTARROW_DISP  = { 1.0f, 1.0f };			//幅
	const float		  SELECTARROW_RANGE = 3.0f;						//移動範囲	
	//----------

}
//========================

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
	//UIの描画
	void DrawUI();

	//選択矢印を動かす
	void MoveArrow();

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
	//----------------------------

	//----スキンメッシュ----
	//ユイ
	std::unique_ptr<CYui> m_pYui;
	//カイト
	std::unique_ptr<CKaito> m_pKaito;
	//----------------------

	//----UI----
	//選択矢印
	std::unique_ptr<CUIObject> m_pSelectArrow;
	float m_MoveArrow;		//座標を動かす値
	bool m_SwitchArrowFlag; //矢印の移動フラグ
	//----------
	//========================


	//表示ヒーロー
	int m_HeroNo;

};

