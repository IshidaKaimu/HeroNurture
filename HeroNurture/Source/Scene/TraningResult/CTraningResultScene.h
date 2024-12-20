#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json.hpp"
#include "Utility\CUtility.h"

//=====================================
// 前方宣言
//=====================================
//----マネージャークラス----
//UI
class CUIManager;
//スキンメッシュ
class CSkinMeshManager;
//サウンド
class CSoundManager;
//ImGui
class ImGuiManager;
//カメラ
class CCameraManager;
//ヒーロー
class CHeroManager;

//=====================================
// 定数宣言
//=====================================
//-----カメラ情報----
//カメラ位置
const D3DXVECTOR3 RESULT_CAMPOS  = { 0.0, 5.0, -4.0 };
//カメラ注視点
const D3DXVECTOR3 RESULT_CAMLOOK = { 2.0, 5.0, 3.0 };
//----育成評価描画関連(_TR = トレーニング結果シーンで用いることを示す)----
//最終ランクX座標
constexpr float RANK_POSX = 900.0f;
//最終ランクY座標
constexpr float RANK_POSY_TR = 30.0f;
//各パラメータランクX座標
constexpr float PARAMRANK_POSX_TR = 830.0f;
//各パラメータランクY座標
constexpr float PARAMRANK_POSY_TR = 230.0f;
//各パラメータランク配置間隔
constexpr float PARAMRANK_INTERVAL_TR = 125.0f;
//パラメータ背景X座標
const float PARAMBACK_POSX_TR = 725.0f;
//パラメータ背景Y座標
const float PARAMBACK_POSY_TR = 125.0f;
//パラメータ背景拡縮
const D3DXVECTOR3 PARAMBACK_SCALE_TR = { 1.1f, 1.1f , 1.1f };
//パラメータの値X座標
const float PARAMVALUE_POSX_TR = 725.0f;
//パラメータの値Y座標
const float PARAMVALUE_POSY_TR = 200.0f;
//パラメータの値配置間隔
const float PARAMVALUE_INTERVAL_TR = 200.0f;
//「最終評価」テキストX座標
const D3DXVECTOR2 RESULTTEXT_POS = { 890.0f,0.0f };
 
//=====================================
// 育成結果シーンクラス
//=====================================
class CTraningResultScene
	:public CSceneBase
{
public:
	CTraningResultScene();
	~CTraningResultScene();

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

	//デバッグ処理
	void Debug();

private:
	//育成結果の描画
	void DrawResult();
	//パラメータの合計値を返す
	float ParamTotal();
	//パラメータUIの描画
	void DrawParamUI(float paramvalue, int no);


private:
	//カメラマネージャ
	CCameraManager* m_pCamera;

	//パラメータ背景UI
	std::unique_ptr<CUIObject> m_pParamList;

	//スタミナゲージの幅
	float m_GageWidth;

};