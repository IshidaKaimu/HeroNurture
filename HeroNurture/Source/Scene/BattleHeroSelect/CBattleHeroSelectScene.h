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

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

//=====================================
//  定数宣言 (_BS = トレーニング結果シーンで用いることを示す)
//=====================================
//----各ヒーローのカメラ配置・注視点----
//-----カメラ情報----
//カメラ位置
const D3DXVECTOR3 CAMPOS_BS = { 0.0, 5.0, -4.0 };
//カメラ注視点
const D3DXVECTOR3 CAMLOOK_BS = { 2.0, 5.0, 3.0 };

//----UI情報----
//パラメータの背景UI
const D3DXVECTOR3 PARAMBACK_POS_BS = { 725.0f,125.0f, 0.0f };
const D3DXVECTOR3 PARAMBACK_SCALE_BS = { 1.1f,1.1f,1.1f };
//パラメータの数値
constexpr float PARAMVALUE_POSX_BS = 900.0f; //X座標
constexpr float PARAMVALUE_POSY_BS = 225.0f; //Y座標
constexpr float PARAMVALUE_INTERVAL_BS = 130.0f; //配置間隔
//パラメータランク
constexpr float PARAMRANK_POSX_BS = 855.0f; //X座標
constexpr float PARAMRANK_POSY_BS = 225.0f; //Y座標
constexpr float PARAMRANK_INTERVAL_BS = 130.0f; //配置間隔
//育成ランク
constexpr float RANK_POSX_BS = 900.0f; //X座標
constexpr float RANK_POSY_BS = 30.0f; //Y座標
//「育成ランク」テキスト座標
const D3DXVECTOR2 RESULTTEXT_POS_BS = { 895.0f,0.0f };
//現在の選択番号
const D3DXVECTOR2 SELECTNO_POS = { 1140.0f, 0.0f };
//育成データの最大数
const D3DXVECTOR2 NATUREDATA_MAX_POS = { 1200.0f, 0.0f };

//==============================
// バトルヒーロー選択クラス
//==============================
class CBattleHeroSelectScene
	:public CSceneBase
{
public:
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
	//----UI----
	std::unique_ptr<CUIObject> m_pParamBack;

	//----スキンメッシュ----
	//ユイ
	std::unique_ptr<CYui>	m_pYui;
	//カイト
	std::unique_ptr<CKaito> m_pKaito;

};