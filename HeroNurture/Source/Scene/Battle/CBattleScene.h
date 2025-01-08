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
//ImGui
class ImGuiManager;

//Json使用に必要な名前空間の格納
using json = nlohmann::json;


//=====================================
// バトルシーンクラス
//=====================================
class CBattleScene
	:public CSceneBase
{
public:
	CBattleScene();
	~CBattleScene();

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
	//バトルに使用するデータの読み込み
	void LoadBattleData();

private:
	//ヒーローマネージャークラス
	std::unique_ptr<CHeroManager> m_pHero;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//バトルに使用するデータ
	json m_BattleData;

	//経過ターン数
	int m_BattleTurn;
};