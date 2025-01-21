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
// 前方宣言
// =======================
//共通の初期位置
const D3DXVECTOR3 TITLE_POS = { 0.0f, 0.0f, 1.0f };
//ユイの初期設定
const D3DXVECTOR3 TITLE_YUI_SCALE = { 0.04f, 0.04f, 0.04f }; //拡縮
//カイトの初期設定
const D3DXVECTOR3 TITLE_KAITO_SCALE = { 0.3f, 0.3f, 0.3f };  //拡縮

//=====================================
// モードセレクトシーンクラス
// 作成者:石田櫂夢
//=====================================
class CModeSelectScene
	:public CSceneBase
{
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
	//UIの描画
	void DrawUI();
private:
	// =======================
	// オブジェクトクラス
	// =======================		
	//----UI----
	//タイトル背景
	std::unique_ptr<CUIObject> m_pTitleBack;
	//タイトル指示テキスト背景
	std::unique_ptr<CUIObject> m_pTitleInfoBack;

};

