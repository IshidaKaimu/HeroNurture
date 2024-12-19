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
//----育成評価描画関連----
//ランクX座標
constexpr float RANK_POSX = 900.0f;
//ランクY座標
constexpr float RANK_POSY = 30.0f;
//パラメータ背景X座標
const float PARAMBACK_POSX = 850.0f;
//パラメータ背景Y座標
const float PARAMBACK_POSY = 600.0f;
//パラメータ背景拡縮
const D3DXVECTOR3 PARAMBACK_SCALE = { 0.3f,0.3f,0.3f };

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
	//パラメータ背景UIの初期設定
	void ParamBackUIInit(std::unique_ptr<CUIObject>& param, int no);
	//パラメータUIの描画
	void DrawParamUI(std::unique_ptr<CUIObject>& param, float paramvalue, int no);


private:
	//カメラマネージャ
	CCameraManager* m_pCamera;

	//筋力パラメータ背景
	std::unique_ptr<CUIObject> m_pPowerParam;
	//魔力パラメータ背景
	std::unique_ptr<CUIObject> m_pMagicParam;
	//素早さパラメータ背景
	std::unique_ptr<CUIObject> m_pSpeedParam;
	//体力パラメータ背景
	std::unique_ptr<CUIObject> m_pHpParam;
	//スタミナゲージ
	std::unique_ptr<CUIObject> m_pStaminaGage;
	//スタミナゲージゲージ背景
	std::unique_ptr<CUIObject> m_pStaminaBack;
	//スタミナゲージの幅
	float m_GageWidth;

};