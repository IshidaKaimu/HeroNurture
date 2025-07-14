#pragma once
#include "Scene\CSceneBase.h"					//シーンベースクラス
#include "Camera\CameraManager\CCameraManager.h"//カメラマネージャクラス
#include "StaticMeshObject\Sky\CSky.h"			//スカイボックスクラス
#include "WriteText\WriteText.h"				//テキスト描画クラス
#include "StaticMeshObject\Ground\CGround.h"	//地面クラス
#include "SkinMeshObject\Hero\CHeroManager.h"	//プレイヤークラス
#include "SkinMeshObject\Hero\Yui\CYui.h"       //ユイクラス
#include "SkinMeshObject\Hero\Kaito\CKaito.h"   //カイトクラス
#include <memory>
#include <Windows.h>

// =======================
// 前方宣言
// =======================		
//json
class CJson;
//汎用クラス
class CUtility;
//UIマネージャー
class CUIManager;

// =======================
// 定数宣言
// =======================
namespace Constant_ModeSelectScene 
{
	//----UI----
	//育成モード		
	const D3DXVECTOR3 NURTURE_POS	 = { 0.0f,0.0f,-1.0f };	 //座標 
	//バトルモード
	const D3DXVECTOR3 BATTLEMODE_POS = { 640.0f,0.0f,-1.0f };//座標
	//被せる画像
	const D3DXVECTOR3 COVER_POS   = { 640.0f,0.0f,0.0f };	 //座標
	constexpr float   COVER_ALPHA = 0.8f;					 //α値
	//共通
	const D3DXVECTOR3 MODE_SCALE = { 1.0f,1.0f,1.0f };		 //拡縮
	const D3DXVECTOR2 MODE_DISP  = { 1.0f, 1.0f };			 //幅
	constexpr float   MODE_ALPHA = 1.0f;					 //α値
	//シーン名												 
	const D3DXVECTOR2 SCENENAME_POS  = { 430.0f,0.0f };		 //座標
	//「A・D 選択」テキスト
	const D3DXVECTOR2 SELECTTEXT_POS  = { 800.0f, 675.0f };  //座標
	//---------
}

//=====================================
// モードセレクトシーンクラス
// 作成者:石田櫂夢
//=====================================
class CModeSelectScene
	:public CSceneBase
{
private:
	//=====================================
	// 列挙型
	//=====================================
	//モードリスト
	enum enModeList :char
	{
		NurtureMode,
		BattleMode,
		Max
	};

public:
	CModeSelectScene();
	~CModeSelectScene();

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
	// =======================
	// オブジェクトクラス
	// =======================		
	//----UI----
	std::unique_ptr<CUIObject> m_pNurtureMode; //育成モード
	std::unique_ptr<CUIObject> m_pBattleMode;  //対戦モード
	std::unique_ptr<CUIObject> m_pCover;       //選択されていないほうにかぶせる画像
	std::unique_ptr<CUIObject> m_pControlBar;  //操作方法指示バー
	//----------
};

