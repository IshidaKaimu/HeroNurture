#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json\CJson.h"

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

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

//=====================================
// 定数宣言
//=====================================
namespace Constant_NatureResultScene 
{
	//-----カメラ情報----
	//カメラ位置
	const D3DXVECTOR3 CAMPOS = { 0.0f, 5.0f, -4.0f };
	//カメラ注視点
	const D3DXVECTOR3 CAMLOOK = { 2.0f, 5.0f, 3.0f };
	//----育成評価描画関連----
	//最終ランクX座標
	constexpr float RANK_POSX = 900.0f;
	//最終ランクY座標
	constexpr float RANK_POSY = 30.0f;
	//パラメータランク配置開始地点X座標
	constexpr float PARAMRANK_POSX = 885.0f;
	//パラメータランク配置開始地点Y座標
	constexpr float PARAMRANK_POSY = 225.0f;
	//各パラメータランク配置間隔
	constexpr float PARAMRANK_INTERVAL = 130.0f;
	//パラメータ背景座標
	const D3DXVECTOR3 PARAMBACK_POS = { 840.0f, 205.0f, 0.0f };
	//パラメータ背景拡縮
	const D3DXVECTOR3 PARAMBACK_SCALE = { 1.1f, 1.1f , 1.1f };
	//パラメータの値X座標
	const float PARAMVALUE_POSX = 930.0f;
	//パラメータの値Y座標
	const float PARAMVALUE_POSY = 225.0f;
	//パラメータの値配置間隔
	const float PARAMVALUE_INTERVAL = 130.0f;
	//「育成ランク」テキスト座標
	const D3DXVECTOR2 RESULTTEXT_POS = { 895.0f,0.0f };
}
//=====================================
// 育成結果シーンクラス
//=====================================
class CNatureResultScene
	:public CSceneBase
{
public:
	CNatureResultScene();
	~CNatureResultScene();

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
	//育成結果の保存
	void SaveResult(const std::string& heroname);


private:
	//カメラマネージャ
	CCameraManager* m_pCamera;

	//パラメータ背景UI
	std::unique_ptr<CUIObject> m_pParamList;
	// =======================
	// json関連
	// =======================	
	//jsonクラス
	std::unique_ptr<CJson> m_pJson;
	//育成結果書き込み用
	json m_ResultWriter;
};