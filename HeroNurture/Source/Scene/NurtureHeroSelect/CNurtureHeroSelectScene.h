#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json.hpp"
//=====================================
// 前方宣言
//=====================================
//----各ヒーローのクラス----
//ユイ
class CYui;
//カイト
class CKaito;
//----マネージャークラス----
//UI
class CUIManager;
//サウンド
class CSoundManager;

// =======================
// 定数宣言
// =======================	
namespace Constant_NurtureHeroSelectScene 
{
	//----各ヒーローのカメラ配置・注視点----
	static const D3DXVECTOR3 CAMPOS_NS = { 0.0f, 5.2f, -2.8f };
	static const D3DXVECTOR3 CAMLOOK_NS = { 0.0f, 6.2f,  3.0f };
	//--------------------------------------
	
	//----UI----
	//シーン名表示位置
	const D3DXVECTOR2 SCENENAME_POS_NS = { 350.0f, -10.0f };
	//ヒーロー名表示位置
	const D3DXVECTOR2 HERONAME_POS_NS = { 350.0f,450.0f };
	//背景
	static D3DXVECTOR3 BACK_POS = { 0.0f,0.0f,0.0f };    //座標
	static D3DXVECTOR3 BACK_SCALE = { 1.0f, 1.0f, 1.0f };//拡縮
	static D3DXVECTOR2 BACK_DISP = { 1.0f,1.0f };		 //幅
	//---------

	//「A・D 選択」テキスト
	const D3DXVECTOR2 SELECTTEXT_POS = { 800.0f, 675.0f };  //座標

}

class CNurtureHeroSelectScene
	:public CSceneBase
{
private:
	// =======================
	// 列挙型
	// =======================	

	//選択可能なヒーロー
	enum enSelectHeroName
	{
		Yui,
		Kaito
	};

public:
	CNurtureHeroSelectScene();
	~CNurtureHeroSelectScene();

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
	//アカウント名取得
	void SetUserName(std::wstring name) { m_UserName = name; }

private:
	//矢印の描画
	void DrawArrow();
private:

	//カメラマネージャ
	CCameraManager* m_pCamera;

    //=====================================
	// オブジェクトクラス
	//=====================================
	//----スキンメッシュ----
	//ユイ
	std::unique_ptr<CYui>	m_pYui;
	//カイト
	std::unique_ptr<CKaito> m_pKaito;
	//----------------------

	//----UI----
	//矢印左
	std::unique_ptr<CUIObject> m_pLeftArrow;
	//矢印右
	std::unique_ptr<CUIObject> m_pRightArrow;
	//----------

	//ユーザー名
	std::wstring m_UserName;


};