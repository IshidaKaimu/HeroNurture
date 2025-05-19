#pragma once
#include "Scene\CSceneBase.h"					//シーンベースクラス
#include "StaticMeshObject\Sky\CSky.h"			//スカイボックスクラス
#include "WriteText\WriteText.h"				//テキスト描画クラス
#include "StaticMeshObject\Ground\CGround.h"	//地面クラス
#include <Windows.h>

//=====================================
// 前方宣言 
//=====================================
//----マネージャークラス----
//バトルモード
class CBattleManager;
//ヒーロー
class CHeroManager;
//敵のヒーロー
class CEnemyHeroManager;
//カメラ
class CCameraManager;


//=====================================
// 定数宣言 
//=====================================
namespace Constant_BattleResultScene
{
	//カメラ
	const D3DXVECTOR3 WIN_CAM_POS    = { -2.4f, 2.0f, 1.1f };  //勝利時座標
	const D3DXVECTOR3 WIN_CAM_LOOK   = { -5.0f, 2.0f, -1.0f }; //勝利時注視点
	const D3DXVECTOR3 LOSE_CAM_POS   = { -0.3f, 1.8f, 1.8f };  //敗北時座標
	const D3DXVECTOR3 LOSE_CAM_LOOK  = { 2.0f, 2.0f, 1.0f };   //敗北時注視点
	//----勝敗テキストUI----
	const D3DXVECTOR2 RESULTTEXT_POS = { 150.0f,220.0f };      //座標
}

//=====================================
// バトル結果シーンクラス
// 制作者:石田櫂夢
//=====================================
class CBattleResultScene
	:public CSceneBase
{
public:
	CBattleResultScene();
	~CBattleResultScene();

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
	//デバッグ
	void Debug();

	//UIの描画
	void DrawUI();

private:
	//カメラクラス
	CCameraManager* m_pCamera;

	// =======================
	// オブジェクトクラス
	// =======================		
	//----スタティックメッシュ----
	std::unique_ptr<CSky> m_pSky;		//空
	std::unique_ptr<CGround> m_pGround; //地面
};

