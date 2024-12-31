#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json\CJson.h"
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
//キー入力
class CKeyManager;
//テキスト描画クラス
class WriteText;

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

// =======================
// 定数宣言
// =======================	
	
//----UI情報(_BS = BattleHeroSelectSceneでの仕様を表す)----
//パラメータの数値
constexpr float PARAMVALUE_POSX_BS = 425.0f; //X座標
constexpr float PARAMVALUE_POSY_BS = 430.0f; //Y座標
constexpr float PARAMVALUE_INTERVAL_BS = 150.0f; //配置間隔
//育成データの最大数
const D3DXVECTOR2 NATUREDATA_MAX_POS = { 1000.0f, 0.0f };

//=====================================
// バトルヒーロー選択クラス
//=====================================
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
	//保存されているヒーローのパラメータを表示する
	void DrawSaveParameter(const json& jsondata, int number);

private:
	//経過ターン数
	int m_BattleTurn;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//保存されている育成結果のファイルデータ
	json m_ResultData;

};