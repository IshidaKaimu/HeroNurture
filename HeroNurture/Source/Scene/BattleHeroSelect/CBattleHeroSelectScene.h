#pragma once
#include "Scene\CSceneBase.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json\CJson.h"
#include "Utility\CUtility.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"

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
//キー入力
class CKeyManager;
//テキスト描画クラス
class WriteText;
//汎用クラス
class CUtility;
//------------------------

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

//=====================================
//  定数宣言
//=====================================
namespace Constant_BattleHeroSelectScene 
{
	//カメラ
	const D3DXVECTOR3 CAMPOS  = { 0.0f, 5.0f, -4.0f };			  //座標
	const D3DXVECTOR3 CAMLOOK = { 2.0f, 5.0f, 3.0f };			  //注視点

	//----UI----
	//パラメータの背景
	const D3DXVECTOR3 PARAMBACK_POS   = { 840.0f, 165.0f, 0.0f }; //座標
	const D3DXVECTOR3 PARAMBACK_SCALE = { 1.1f, 1.1f, 1.1f };	  //注視点
	//パラメータの数値
	const D3DXVECTOR2 PARAMVALUE_POS    = { 955.0f,185.0f };	  //座標
	constexpr float PARAMVALUE_INTERVAL = 130.0f;				  //配置間隔
	//パラメータランク											  
	const D3DXVECTOR2 PARAMRANK_POS    = { 860.0f, 185.0f };	  //座標
	constexpr float PARAMRANK_INTERVAL = 130.0f;				  //配置間隔
	//育成ランク												  	 
	const D3DXVECTOR2 RANK_POS = { 900.0f,-5.0f };				  //座標
	//「育成ランク」テキスト									   
	const D3DXVECTOR2 RESULTTEXT_POS = { 895.0f,-20.0f };		  //座標
	//現在の選択番号											   
	const D3DXVECTOR2 SELECTNO_POS = { 1140.0f, 0.0f };			  //座標
	//育成データの最大数										     
	const D3DXVECTOR2 NurtureDATA_MAX_POS = { 1200.0f, 0.0f };	  //座標
	//「A・D 選択」テキスト									   	  
	const D3DXVECTOR2 SELECTTEXT_POS = { 800.0f, 675.0f };		  //座標
	//背景													   	  
	static D3DXVECTOR3 BACK_POS   = { 0.0f,0.0f,0.0f };			  //座標
	static D3DXVECTOR3 BACK_SCALE = { 1.0f, 1.0f, 1.0f };		  //拡縮
	static D3DXVECTOR2 BACK_DISP  = { 1.0f,1.0f };				  //幅
	//----------
}
//==============================
// バトルヒーロー選択クラス
//==============================
class CBattleHeroSelectScene
	:public CSceneBase
{
private:
	//パラメータ表示更新用構造体
	struct enParamWriter
	{
		//筋力
		float Power;
		//魔力
		float Magic;
		//素早さ
		float Speed;
		//体力
		float Hp;
	};

public:

	CBattleHeroSelectScene();
	~CBattleHeroSelectScene();

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
	//育成データの各要素描画処理
	void DrawResultData();

	//保存されているヒーローのパラメータを表示する
	void DrawSaveParameter(const json& jsondata, int number);

	//保存されている名前ごとのヒーローの描画
	void DrawHero();

	//矢印の描画
	void DrawArrow();

	//パラメータUIの描画
	void DrawParamUI(float paramvalue, int no);

private:
	//経過ターン数
	int m_BattleTurn;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//保存されている育成結果のファイルデータ
	json m_ResultData;
	//バトルに使用するデータを格納し、書き込みに用いる変数
	json m_BattleDataWriter;

	//カメラマネージャクラス
	CCameraManager* m_pCamera;

	// =======================
	// オブジェクトクラス
	// =======================	
	//----スキンメッシュ----
	//ユイ
	std::unique_ptr<CYui>	m_pYui;
	//カイト
	std::unique_ptr<CKaito> m_pKaito;
	//----------------------

	//----UI----
	//パラメータ背景
	std::unique_ptr<CUIObject> m_pParamBack;
	//矢印左
	std::unique_ptr<CUIObject> m_pLeftArrow;
	//矢印右
	std::unique_ptr<CUIObject> m_pRightArrow;
	//----------


	//前のシーンに戻す場合のフラグ
	bool m_BackSceneFlag;

};