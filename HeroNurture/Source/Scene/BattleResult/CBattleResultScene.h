#pragma once
#include "Scene\CSceneBase.h"					//シーンベースクラス
#include "Camera\CameraManager\CCameraManager.h"//カメラマネージャクラス
#include "StaticMeshObject\Sky\CSky.h"			//スカイボックスクラス
#include "WriteText\WriteText.h"				//テキスト描画クラス
#include "StaticMeshObject\Ground\CGround.h"	//地面クラス
#include "SkinMeshObject\Hero\CHeroManager.h"	//プレイヤークラス
#include <Windows.h>

//=====================================
// 定数宣言 
//=====================================
//----勝敗テキストUI----
const D3DXVECTOR2 RESULTTEXT_POS = { 250.0f,300.0f }; //座標


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


};

