#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "Scene\Nurture\CNurtureScene.h"
#include "json.hpp"

//========================
// 前方宣言
//=======================
//----マネージャークラス----
// シーン
class CSceneManager;
//育成モード
class CNurtureManager;
//ヒーロー
class CHeroManager;
//UI
class CUIManager;
//--------------------------

//========================


//========================
// 定数宣言
//=======================
namespace Constant_TraningScene
{
	//----テキストの位置----
	//パラメータの種類
	const D3DXVECTOR2 PARAMTEXT_OFFSET = { 80.0f,600.0f };
	//値
	const D3DXVECTOR2 VALUETEXT_OFFSET = { 275.0f,600.0f };
	//トレーニング結果
	const D3DXVECTOR2 RESULTTEXT_OFFSET = { 500.0f,100.0f };
	//SEの再生タイミング
	const int PLAY_SE_CNT = 1;
	//-----------------------
}

//========================
//上昇したパラメータのリスト
//テキストの描画順処理に使う
//=======================
struct IncParam
{
	std::wstring ParamName;		 //パラメータの種類
	int IncValue;				 //上昇量
	std::wstring ParamChangeText;//上昇または減少のテキスト
};

//=====================================
// トレーニングシーンクラス
// 制作者:石田櫂夢
//=====================================
class CTraningScene
	:public CNurtureScene
{
public:
	CTraningScene();
	~CTraningScene();

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
	//パラメータが上昇していたら配列にテキストを追加する処理
	void AddText();
	//配列に既に追加している情報ではないかの確認
	bool AlreadyAddCheck(std::wstring paramname);
	//トレーニング結果テキストの描画
	void DrawTraningText();
	//パラメータ変化の描画処理
	void DrawParamChange(const IncParam& param);

private:

	//カメラマネージャ
	CCameraManager* m_pCamera;

	//=====================================
	// オブジェクトクラス
	//=====================================
	
	//----スタティックメッシュ----
	//スカイボックス
	std::unique_ptr<CSky> m_pSky;
	//地面
	std::unique_ptr<CGround> m_pGround;
	//----------------------------

	//----UI----
	//背景
	std::unique_ptr<CUIObject> m_pBack;
	//テキストボックス
	std::unique_ptr<CUIObject> m_pTextBox;
	//----------

	//=====================================

	//テキストの描画順処理に使う配列
	std::vector<IncParam> m_ParamInc;

	//テキスト番号※表示順制御
	int m_TextNo;

	//SE再生用カウント
	int m_SECnt;

	//----フラグ----
	//必要なテキストをすべて表示し終えた
	bool m_TextEnd;

};